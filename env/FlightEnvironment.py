import gymnasium as gym
from gymnasium import spaces
import numpy as np
import ctypes
import os

class FlightEnvironment(gym.Env):

    def __init__(self, dll_path=r'C:\Users\Bridl\Documents\Thesis\Matlab\Thesis_C___grt_rtw\flight_model.dll'):
        super(FlightEnvironment, self).__init__()

        # --- CTYPES SETUP ---
        # Load the compiled library
        if not os.path.exists(dll_path):
            raise FileNotFoundError(f"DLL not found at {dll_path}")
        
        self.model = ctypes.CDLL(dll_path)

        # Define the 4 inputs (Actions) and 9 outputs (Observations) pointers
        # These names must match what you found in Thesis_C__.h
        self.model.Thesis_C___initialize.argtypes = []
        self.model.Thesis_C___step.argtypes = []

        # Setup helps with reward calc
        self.target_altitude = 3000.0
        self.max_altitude = 10000.0
        self.max_steps = 2000
        self.current_step = 0

        # Define the observation space (9 states)
        obs_low = np.array([-20000.0]*9, dtype=np.float32)
        obs_high = np.array([20000.0]*9, dtype=np.float32)
        self.observation_space = spaces.Box(low=obs_low, high=obs_high, dtype=np.float32)

        # Define the action space (4 controls)
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32)

    def _get_obs(self):
        """Helper to pull 9 observations from the C++ memory."""
        # Create a buffer for 9 doubles (or floats, check your rtwtypes.h)
        obs_buffer = (ctypes.c_double * 9)() 
        self.model.get_outputs(ctypes.byref(obs_buffer)) # You'll need to define this wrapper in C or use direct struct access
        return np.array(obs_buffer, dtype=np.float32)
    
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
        self.current_step += 1

        # 1. Inject actions into C++ model
        action_data = np.array(action, dtype=np.float64) # Use double to match Navion stability derivatives
        self.model.set_inputs(action_data.ctypes.data_as(ctypes.POINTER(ctypes.c_double)))

        # 2. Run physics for exactly one step
        self.model.Thesis_C___step()

        # 3. Pull new observations
        observation = self._get_obs()
        
        # 4. Reward Logic (Use your existing calc_reward function)
        reward = self.calc_reward(observation, action)

        # 5. Check Success/Failure
        terminated = self.check_termination(observation)
        
        # Check distance to waypoint for success bonus
        dist_3d = np.sqrt((5000-observation[0])**2 + (5000-observation[1])**2 + (3000-observation[2])**2)
        if dist_3d < 50.0:
            terminated = True
            reward += 1000.0
            print(f"Target Reached!")

        truncated = self.current_step >= self.max_steps
        
        return observation, float(reward), terminated, truncated, {}
    
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        self.current_step = 0
        
        # Call the C++ initialize function to reset physics to 1000ft
        self.model.Thesis_C___initialize()
        
        observation = self._get_obs()
        return observation, {}