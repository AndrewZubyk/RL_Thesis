import gymnasium as gym
from gymnasium import spaces
import numpy as np
import socket
import struct

class FlightEnvironment(gym.Env):

    def __init__(self, host = '127.0.0.1', port = 44444): #gonna have to put the host and port into this as well ex; (selv, host = , port = )
        super(FlightEnvironment, self).__init__()

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
        self.client_socket.connect((host, port))
        self.client_socket.settimeout(5.0)
        self.is_connected = True
        print("Simulink connected successfully.")

    def _receive_data(self):
        '''
        Receives data from Simulink
        basic setup for now, fix this later to get right data
        '''

        data = self.client_socket.recv(36)
        state = struct.unpack('9f', data)
        return np.array(state, dtype=np.float32)

    def step(self, action):
        '''
        Action setup for Simulink:
        Receives new states and rewards
        '''

        if not self.is_connected:
            raise ConnectionError("Not connected to Simulink.")
        
        # send the action to simulink, in 4 bytes format
        format_send = '4f'
        action_packed = struct.pack(format_send, *action)
        self.client_socket.sendall(action_packed)

        # receive the new state from Simulink
        try:
            observation, reward, terminated = self._receive_data()
        except (ConnectionError, struct.error) as e:
            print(f"Error during step: {e}")
            observation = np.zeros(self.observation_space.shape, dtype=np.float32)
            reward = -100.0 # Penalty when the connection fails
            terminated = True

        # Implement runtime monitoring actions here, after step is made, but before the sending to the action
        info = {}

        return observation, reward, terminated, False, info
    
    def reset(self, seed=None, options=None):
        '''
        Resets environment to a new episode
        '''

        super().reset(seed=seed)

        reset_action = np.array([0.0, 0.0, 0.0, 0.0], dtype=np.float32)  # Neutral action for reset
        self.client_socket.sendall(struct.pack('4f', *reset_action))

        try:
            data_format = '<12f' # 12 floats for observation states
            data_size = struct.calcsize(data_format)
            
            data = self.client_socket.recv(data_size)
            if not data or len(data) != data_size:
                 raise ConnectionError("Lost connection or incomplete data on reset.")
            
            observation = np.array(struct.unpack(data_format, data), dtype=np.float32)
            
        except (ConnectionError, struct.error) as e:
            print(f"Error during reset: {e}")
            observation = np.zeros(self.observation_space.shape, dtype=np.float32)

        info = {}
        return observation, info
        
    def close(self):
        '''
        Closes the connection to Simulink
        '''

        self.client_socket.close()
        self.is_connected = False