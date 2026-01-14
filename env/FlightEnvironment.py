import gymnasium as gym
from gymnasium import spaces
import numpy as np
import socket
import struct

class FlightEnvironment(gym.Env):

    def __init__(self, host = '127.0.0.1', port = 44444): #gonna have to put the host and port into this as well ex; (selv, host = , port = )
        super(FlightEnvironment, self).__init__()

        # Setup helps with reward calc
        self.target_altitude = 5000.0
        self.max_altitude = 10000.0

        self.max_steps = 2000
        self.current_step = 0

        # Define the observation space, this being the state of the flight simulator
        obs_low = np.array([-20000.0]*9)   # Example low values, change these later
        obs_high = np.array([20000.0]*9)   # Example high values, change these later
        self.observation_space = spaces.Box(low=obs_low, high=obs_high, dtype=np.float32)

        # Define the action space, control points of the aircraft, elevators, ailerons, rudder, throttle
        # Normalied actions between -1 and 1
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32)


        # Simulink connection parameters with the tcp/ip
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        print(f"Server started. Waiting for Simulink to connect on {host}:{port}...")
        self.server_socket.bind((host, port))
        self.server_socket.listen(1)
        
        # The script will PAUSE here until you hit 'Run' in Simulink
        self.conn, self.addr = self.server_socket.accept()
        self.is_connected = True
        print(f"Simulink connected from: {self.addr}")

    def _receive_data(self):
        '''
        Receives data from Simulink
        basic setup for now, fix this later to get right data
        '''

        expected_floats = 9
        expected_bytes = expected_floats * 4

        try:
            data = self.conn.recv(expected_bytes)
            if not data or len(data) != expected_bytes:
                raise ConnectionError("Incomplete Data")
            
            state = np.array(struct.unpack(f'{expected_floats}f', data), dtype=np.float32)
            
            # --- ADD THIS DEBUG PRINT FOR STATE CHECK ---
            #print(f"DEBUG OBS: {state}") 
            # ----------------------------

            return state
        except Exception as e:
            raise e

    def calc_reward(self, observation, action):
        '''
        Reward based on:
        1. 3D Distance to Waypoint (North, East, Alt)
        2. Heading Alignment (Facing the waypoint)
        3. Stability/Action Penalties
        '''
        
        north = observation[0]
        east  = observation[1]
        alt   = observation[2]
        roll  = observation[3]
        pitch = observation[4]
        yaw   = observation[5] 
        
        target_north = 5000.0
        target_east  = 5000.0 
        target_alt   = 3000.0

        # --- Error Calcs ---
        
        # Vector from plane to target
        error_n = target_north - north
        error_e = target_east - east
        error_z = target_alt - alt
        
        # 3D Straight Line Distance
        dist_3d = np.sqrt(error_n**2 + error_e**2 + error_z**2)
        
        # Desired Heading (The angle to the target)
        desired_yaw = np.arctan2(error_e, error_n)
        heading_error = np.arctan2(np.sin(desired_yaw - yaw), np.cos(desired_yaw - yaw))

        # --- Reward Components ---

        # Distance Penalty (Aggressive, and linear to negate staying still)
        reward_dist = -(dist_3d / 1000.0) 

        # Heading Reward, encourage looking at taget
        reward_heading = np.cos(heading_error) * 1.0

        # Altitude Incentive
        reward_alt = 0.0
        if alt < target_alt:
            if pitch > 0.05: 
                reward_alt = pitch * 2.0
        
        # --- Penalties ---
        penalty_action = np.sum(np.square(action)) * 0.1
        
        penalty_stability = 0.0
        
        if alt < (target_alt - 100) and pitch < -0.1:
            penalty_stability += abs(pitch) * 2.0

        if abs(roll) > 0.78: 
            penalty_stability += abs(roll) * 1.0
        
        # --- TOTAL ---
        
        # Reward only gets close to zero as plane gets very close to target
        total_reward = reward_dist + reward_heading + reward_alt - penalty_stability - penalty_action
        
        return float(total_reward)
    
    def check_termination(self, observation):
        '''
        Check if the episode should terminate
        '''

        z = observation[2]  # Altitude
        roll = observation[3] # Roll angle
        pitch = observation[4] # Pitch angle

        if z < 0 or z > self.max_altitude:
            return True  # Terminate if altitude is too far out of bounds

        if abs(roll) > (np.pi / 2) or abs(pitch) > (np.pi / 2):
            return True  # Terminate if aircraft is upside down

        return False

    def step(self, action):
        '''
        Action setup for Simulink:
        Receives new states and rewards
        '''

        self.current_step += 1

        if not self.is_connected:
            return np.zeros(9, dtype=np.float32), 0.0, True, False, {}

        try:
            action_list = action.tolist() if isinstance(action, np.ndarray) else action
            full_action = list(action_list) + [0.0]
            self.conn.sendall(struct.pack('5f', *full_action))

            observation = self._receive_data()
            
            north = observation[0]
            east  = observation[1]
            alt   = observation[2]

            target_north = 5000.0
            target_east  = 5000.0 
            target_alt   = 3000.0

            # Calculate Distance
            error_n = target_north - north
            error_e = target_east - east
            error_z = target_alt - alt
            dist_3d = np.sqrt(error_n**2 + error_e**2 + error_z**2)
            dist_3d = np.sqrt(error_n**2 + error_e**2 + error_z**2)
            
            # SUCCESS CONDITION
            if dist_3d < 50.0:
                terminated = True
                reward += 1000.0  # Big bonus for getting there
                print(f"*** TARGET REACHED at Step {self.current_step}! ***")
            else:
                reward = self.calc_reward(observation, action)

            terminated = self.check_termination(observation)
            
            if terminated and observation[2] <= 0:
                reward = -100.0

        except (ConnectionError, struct.error, OSError) as e:
            print(f"Error during step: {e}")
            observation = np.zeros(self.observation_space.shape, dtype=np.float32)
            
            reward = 0.0
            terminated = True
        
        truncated = False
        if self.current_step >= self.max_steps:
            truncated = True
        info = {}

        if np.isnan(observation).any() or np.isinf(observation).any():
            print("!!! CRITICAL: Physics instability detected. Resetting episode.")
            safe_obs = np.zeros(self.observation_space.shape, dtype=np.float32)
            return safe_obs, -100.0, True, False, {}

        return observation, reward, terminated, truncated, info
    
    def reset(self, seed=None, options=None):
        '''
        Resets environment to a new episode
        '''
        super().reset(seed=seed)

        self.current_step = 0

        # Flush buffer
        try:
            self.conn.setblocking(0)
            while True:
                data = self.conn.recv(1024)
                if not data: break
        except BlockingIOError:
            pass
        except Exception:
            pass
        finally:
            self.conn.setblocking(1)

        # [Elevator, Aileron, Rudder, Throttle, Reset Flag]
        reset_action = [0.0, 0.0, 0.0, 0.0, 1.0] 
        
        try:
            self.conn.sendall(struct.pack('4f', *reset_action))
            observation = self._receive_data()
        except Exception:
            observation = np.zeros(self.observation_space.shape, dtype=np.float32)
            
        return observation, {}
        
    def close(self):
        '''
        Closes the connection to Simulink
        '''

        self.conn.close()