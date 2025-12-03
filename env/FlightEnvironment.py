import gymnasium as gym
from gymnasium import spaces
import numpy as np
import socket
import struct

class FlightEnvironment(gym.Env):

    def __init__(self, host = '127.0.0.1', port = 44444): #gonna have to put the host and port into this as well ex; (selv, host = , port = )
        super(FlightEnvironment, self).__init__()

        # Setup
        self.target_altitude = 500.0
        self.max_altidude = 1000.0

        # Define the observation space, this being the state of the flight simulator
        obs_low = np.array([-1000.0, -1000.0, -1000.0, -np.pi, -np.pi, -np.pi, 0.0, 0.0, 0.0])  # Example low values, change these later
        obs_high = np.array([1000.0, 1000.0, 1000.0, np.pi, np.pi, np.pi, 1000.0, 1000.0, 1000.0])  # Example high values, change these later
        self.observation_space = spaces.Box(low=obs_low, high=obs_high, dtype=np.float32)

        # Define the action space, control points of the aircraft, elevators, ailerons, rudder, throttle
        # Normalied actions between -1 and 1
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32)


        # Simulink connection parameters with the tcp/ip
        self.host = host
        self.port = port
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.is_connected = False
        
        print(f"Trying to connect to Simulink on: {host}:{port}...")
        try:
            self.client_socket.connect((host, port))
            self.client_socket.settimeout(5.0)
            self.is_connected = True
            print("Simulink connected successfully.")
        except ConnectionRefusedError:
            print("Connection Failed.")

    def _receive_data(self):
        '''
        Receives data from Simulink
        basic setup for now, fix this later to get right data
        '''

        expected_floats = 9
        expected_bytes = expected_floats * 4

        try:
            data = self.client_socket.recv(expected_bytes)
            if not data or len(data) != expected_bytes:
                raise ConnectionError("Incomplete Data")
            
            state = np.array(struct.unpack(f'{expected_floats}f', data), dtype=np.float32)
            return state
        except Exception as e:
            raise e

    def calc_reward(self, observation, action):
        '''
        Reward function calculation
        '''

        z = observation[2]  # Altitude
        roll = observation[3] # Roll angle
        pitch = observation[4] # Pitch angle

        altitude_error = abs(self.target_altitude - z)
        reward_altitude = 1.0 - (altitude_error / self.max_altidude)

        stability_penalty = abs(roll) + abs(pitch)

        penalty_action = np.sum(np.square(action)) * 0.1

        # Total Reward
        total_reward = reward_altitude - (stability_penalty * 0.5) - penalty_action
        
        return float(total_reward)
    
    def check_termination(self, observation):
        '''
        Check if the episode should terminate
        '''

        z = observation[2]  # Altitude
        roll = observation[3] # Roll angle
        pitch = observation[4] # Pitch angle

        if z < 0 or z > self.max_altidude:
            return True  # Terminate if altitude is too far out of bounds

        if abs(roll) > (np.pi / 2) or abs(pitch) > (np.pi / 2):
            return True  # Terminate if aircraft is upside down

        return False

    def step(self, action):
        '''
        Action setup for Simulink:
        Receives new states and rewards
        '''

        if not self.is_connected:
            return np.zeros(9, dtype=np.float32), 0.0, True, False, {}

        try:
            action_list = action.tolist() if isinstance(action, np.ndarray) else action
            self.client_socket.sendall(struct.pack('4f', *action_list))

            observation = self._receive_data()

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
        info = {}

        return observation, reward, terminated, truncated, info
    
    def reset(self, seed=None, options=None):
        '''
        Resets environment to a new episode
        '''

        super().reset(seed=seed)

        # Sets zeros to reset the environment
        reset_action = [0.0, 0.0, 0.0, 0.0] 
        try:
            self.client_socket.sendall(struct.pack('4f', *reset_action))
            observation = self._receive_data()
        except Exception:
            observation = np.zeros(self.observation_space.shape, dtype=np.float32)
            
        return observation, {}
        
    def close(self):
        '''
        Closes the connection to Simulink
        '''

        self.client_socket.close()