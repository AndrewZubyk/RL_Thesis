import numpy as np

# Define all the constrains

max_altitude = 10000.0 # Random max alt for now

max_pitch_angle_rad = np.pi / 6  # 30 degrees in radians

max_roll_angle_rad = np.pi / 4   # 45 degrees in radians

max_control_surface_deflection = 1.05 # Checks if action is out of bounds set before


def check_violations(observation: np.ndarray, action: np.ndarray) -> bool:
    '''
    Checks for any violations in the observation (current state) and action (control inputs)

    Observation vector setup: [x, y, z, roll, pitch, yaw, vx, vy, vz] (i think for now)
    Action vector setup: [elevator, aileron, rudder, throttle]

    Altitude at index 2, roll at index 3, pitch at index 4
    '''
    
    # Check Altitude
    if observation[2] > max_altitude:
        return True  # Violation: Exceeded max altitude

    # Check roll angle
    if abs(observation[3]) > max_roll_angle_rad:
        return True  # Violation: Exceeded max roll angle

    # Check pitch angle
    if abs(observation[4]) > max_pitch_angle_rad:
        return True  # Violation: Exceeded max pitch angle

    # Check control surface deflections
    if np.any(np.abs(action) > max_control_surface_deflection):
            print("SAFETY VIOLATION: Action magnitude exceeds defined limits.")
            return True
    
    return False  # No violations detected

def apply_runtime(action: np.ndarray, observation: np.ndarray) -> np.ndarray:
    '''
    Apply runtime monitoring to the action based on if there is a violation found

    Utilizes default reset to 0 for now but will be updated
    Can be done to convert to traditional PID flight or just zero the action
    '''

    if check_violations(observation, action):
         #print("Shield: violation detected, taking corrective action.")

         safe_action = np.zeros_like(action)
         return safe_action
    return action