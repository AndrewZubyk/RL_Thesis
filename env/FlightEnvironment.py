import gymnasium as gym
from gymnasium import spaces
import numpy as np
import ctypes
import os

class FlightEnvironment(gym.Env):

    def __init__(self, dll_path=r'./Thesis_C___grt_rtw/flight_model.so'):
        super(FlightEnvironment, self).__init__()

        # --- CTYPES SETUP ---
        if not os.path.exists(dll_path):
            raise FileNotFoundError(f"DLL not found at {dll_path}")
        
        self.model = ctypes.CDLL(dll_path)

        # Define Argument Types
        self.model.Thesis_C___initialize.argtypes = []
        self.model.Thesis_C___initialize.restype = None

        self.model.Thesis_C___step.argtypes = []
        self.model.Thesis_C___step.restype = None

        # You MUST tell ctypes that these functions take pointers to doubles
        self.model.set_inputs.argtypes = [ctypes.POINTER(ctypes.c_double)]
        self.model.set_inputs.restype = None

        self.model.get_outputs.argtypes = [ctypes.POINTER(ctypes.c_double)]
        self.model.get_outputs.restype = None

        # ... rest of setup ...
        self.target_pos = np.array([5000.0, 5000.0, 3000.0], dtype=np.float32)
        self.max_altitude = 10000.0
        self.max_steps = 15000
        self.current_step = 0

        self.prev_dist = 0.0
        
        # ... observation/action spaces ...
        # North, East, Down, Phi, Theta, Psi, TAS, 0, -1
        # Elevator, Aileron, Rudder, Throttle

        # 1. Action Space: Always normalized (-1.0 to 1.0)
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32)

        # 2. Observation Space: [Roll, Pitch, Yaw, P, Q, R, North, East, Alt]
        # Angles = +/- Pi (3.14), Rates = +/- 10 rad/s, Position = Infinite
        high = np.array([np.pi]*3 + [10.0]*3 + [np.inf]*3, dtype=np.float32)
        
        # Define Low bounds (Symmetric, except Altitude starts at 0)
        low = -high
        low[8] = 0.0 
        
        self.observation_space = spaces.Box(low=low, high=high, dtype=np.float32)

    def _get_obs(self):
        """Helper to pull 9 observations from the C++ memory."""
        # Create a buffer for 9 doubles
        obs_buffer = (ctypes.c_double * 9)() 
        
        # Cast the array to a double pointer (LP_c_double)
        c_double_pointer = ctypes.cast(obs_buffer, ctypes.POINTER(ctypes.c_double))
        
        self.model.get_outputs(c_double_pointer)
        return np.array(obs_buffer, dtype=np.float32)
    
    def calc_reward(self, observation, action, terminated):
        '''
        Reward based on:
        1. 3D Distance to Waypoint (North, East, Alt)
        2. Heading Alignment (Facing the waypoint)
        3. Stability/Action Penalties
        '''
        
        # EXTRACT VARIABLES
        north = observation[0]
        east  = observation[1]
        alt   = observation[2]
        roll  = observation[3]
        pitch = observation[4]
        yaw   = observation[5]
        
        # CALCULATE DISTANCE
        # Current 3D position
        current_pos = np.array([north, east, alt])
        dist_3d = np.linalg.norm(self.target_pos - current_pos)

        # CALCULATE PROGRESS (The "Distance Reward")
        delta_dist = self.prev_dist - dist_3d
        
        # SAFETY CLIP: Limit the reward to +/- 10.0 per step.
        reward_prog = np.clip(delta_dist * 1.0, -10.0, 10.0)

        # ALIGNMENT REWARD (Heading)
        # Vector to target
        target_north = self.target_pos[0] - north
        target_east  = self.target_pos[1] - east
        
        # Desired Yaw
        desired_yaw = np.arctan2(target_east, target_north)

        # Yaw Error
        yaw_error = ((desired_yaw - yaw) + np.pi) % (2 * np.pi) - np.pi
        
        # Reward: +0.5 if facing target, -0.5 if facing away
        reward_heading = np.cos(yaw_error) * 0.5

        # SURVIVAL & PENALTIES
        reward_alive = 0.1
        
        # Action Penalty
        reward_action = -np.sum(np.square(action)) * 0.05

        # Stability Penalty
        reward_stab = 0.0
        if abs(roll) > 1.5: 
            reward_stab -= 0.1
            
        # TERMINAL REWARDS
        if terminated:
            if dist_3d < 100.0:
                return 1000.0 # Success
            else:
                return -100.0 # Crash

        self.prev_dist = dist_3d

        # TOTAL
        total_reward = reward_prog + reward_heading + reward_alive + reward_action + reward_stab
        
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
        self.current_step += 1

        scaled_action = action * np.array([30.0, 30.0, 30.0, 1.0])
    
        # Fix Throttle: Map [-1, 1] to [0, 1]
        scaled_action[3] = (action[3] + 1) / 2

        # 1. Inject actions into C++ model
        action_data = np.array(scaled_action, dtype=np.float64)
        # Cast to pointer
        action_ptr = action_data.ctypes.data_as(ctypes.POINTER(ctypes.c_double))
        self.model.set_inputs(action_ptr)

        # 2. Run physics
        self.model.Thesis_C___step()

        # 3. Pull new observations
        observation = self._get_obs()
        
        # 4. Termination logic
        terminated = False
        truncated = False

        if observation[2] < 0 or observation[2] > self.max_altitude:
            terminated = True # Crashed or too high

        if abs(observation[3]) > (np.pi / 2) or abs(observation[4]) > (np.pi / 2):
            terminated = True # Upside down check

        dist_3d = np.linalg.norm(self.target_pos - observation[:3])
        if dist_3d < 100.0:
            terminated = True
            print(f"Target Reached! Distance: {dist_3d:.1f} ft")
        
        truncated = self.current_step >= self.max_steps

        # 5. Reward Logic
        reward = self.calc_reward(observation, action, terminated)
        
        return observation, float(reward), terminated, truncated, {}
    
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        
        self.current_step = 0
        self.model.Thesis_C___initialize()
        observation = self._get_obs()

        self.prev_dist = np.linalg.norm(self.target_pos - observation[:3])

        return observation, {}