import gymnasium as gym
import numpy as np


from monitoring.runtime_monitor import apply_runtime

class flight_rapper(gym.Wrapper):
    def __init__(self, env):
        super().__init__(env)
        self.last_observation = None


    def step(self, action):
        '''
        Step function with runtime monitoring applied
        '''
        if self.last_observation is not None:
            monitored_action = apply_runtime(action, self.last_observation)
        else:
            monitored_action = action

        observation, reward, terminated, truncated, info = self.env.step(monitored_action)
        self.last_observation = observation

        return observation, reward, terminated, truncated, info