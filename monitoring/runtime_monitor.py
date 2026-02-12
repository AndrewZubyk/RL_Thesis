import numpy as np

def apply_runtime(action, observation):
    """
    PROPORTIONAL Runtime Monitor (Corrected Action Indices)
    
    Action Space:
    0: Elevator (Pitch)
    1: Aileron  (Roll)
    2: Rudder   (Yaw)
    3: Throttle (Power)
    
    Observation Space:
    [North, East, Alt, Roll, Pitch, Yaw...]
      0      1     2    3     4      5
    """
    
    # 1. Setup
    safe_action = np.array(action, copy=True)
    
    # 2. Extract State (Corrected Observation Indices)
    alt   = observation[2]  # Altitude (ft)
    roll  = observation[3]  # Radians
    pitch = observation[4]  # Radians
    
    # 3. Define Safe Limits
    ALT_SOFT = 300.0    # Start nudging up
    ALT_HARD = 50.0     # Panic floor
    
    ROLL_LIMIT = np.deg2rad(15)
    ROLL_KP = 1.5
    
    PITCH_MIN = np.deg2rad(-20) # Max dive
    PITCH_MAX = np.deg2rad(25)  # Max climb
    PITCH_KP = 2.0

    # --- LOGIC 1: GROUND AVOIDANCE ---
    if alt < ALT_SOFT:
        # Calculate Danger (0.0 to 1.0)
        if alt <= ALT_HARD:
            danger = 1.0
        else:
            danger = (ALT_SOFT - alt) / (ALT_SOFT - ALT_HARD)
        
        # A. Force Throttle Up (Index 3)
        # If danger is high, force throttle to at least 50-100%
        safe_action[3] = max(safe_action[3], -0.5 + (1.5 * danger))
        
        # B. Pull Up (Index 0 - ELEVATOR)
        # Negative Elevator = Pitch Up
        elevator_fix = -1.0 * danger
        safe_action[0] += elevator_fix

        # C. Level Wings (Index 1 - AILERON)
        # Reduce banking authority when low to prevent wing strikes
        safe_action[1] *= (1.0 - danger)

    # --- LOGIC 2: BANK LIMITER ---
    # Fixes Action Index 1 (Aileron)
    if roll > ROLL_LIMIT:
        excess = roll - ROLL_LIMIT
        # Roll Left (Negative Aileron)
        safe_action[1] -= (excess * ROLL_KP)
        
    elif roll < -ROLL_LIMIT:
        excess = roll - (-ROLL_LIMIT)
        # Roll Right (Positive Aileron)
        safe_action[1] -= (excess * ROLL_KP)

    # --- LOGIC 3: PITCH LIMITER ---
    # Fixes Action Index 0 (Elevator)
    if alt > ALT_SOFT:
        if pitch > PITCH_MAX: # Nose too high
            excess = pitch - PITCH_MAX
            # Push Down (Positive Elevator)
            safe_action[0] += (excess * PITCH_KP)
            
        elif pitch < PITCH_MIN: # Nose too low
            excess = pitch - PITCH_MIN
            # Pull Up (Negative Elevator)
            safe_action[0] += (excess * PITCH_KP)

    # --- FINAL CLEANUP ---
    safe_action = np.clip(safe_action, -1.0, 1.0)

    return safe_action