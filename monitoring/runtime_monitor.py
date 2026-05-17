import numpy as np

def apply_runtime(action, observation):
    """
    Applies proportional runtime monitoring (envelope protection) to flight controls.
    Action: [Elevator, Aileron, Rudder, Throttle]
    """
    alt = observation[2]
    roll_deg = np.degrees(observation[3])
    pitch_deg = np.degrees(observation[4])
    
    safe_action = np.copy(action)
    triggered = False

    # --- EP1: GROUND AVOIDANCE ---
    soft_alt_limit = 500.0
    hard_alt_limit = 100.0
    
    if alt < soft_alt_limit:
        triggered = True
        danger_ratio = max(0.0, min(1.0, (soft_alt_limit - alt) / (soft_alt_limit - hard_alt_limit)))
        safe_action[0] = min(safe_action[0], -1.0 * danger_ratio)
        safe_action[3] = max(safe_action[3], 1.0 * danger_ratio)

    # --- EP2: PITCH LIMITER ---
    if not triggered:
        max_pitch = 35.0  # Widened to allow normal climbs
        min_pitch = -25.0 # Widened to allow normal descents
        
        if pitch_deg > max_pitch:
            triggered = True
            # Divisor is 10.0: Ramps up smoothly over 10 degrees instead of instantly
            danger_ratio = min(1.0, (pitch_deg - max_pitch) / 10.0) 
            safe_action[0] = max(safe_action[0], 1.0 * danger_ratio)
            
        elif pitch_deg < min_pitch:
            triggered = True
            danger_ratio = min(1.0, (min_pitch - pitch_deg) / 10.0)
            safe_action[0] = min(safe_action[0], -1.0 * danger_ratio)

    # --- EP3: BANK LIMITER ---
    max_bank = 45.0 # Widened significantly! 15 degrees was way too tight for RL.
    
    if abs(roll_deg) > max_bank:
        triggered = True
        # Ramps up smoothly between 45 and 55 degrees
        danger_ratio = min(1.0, (abs(roll_deg) - max_bank) / 10.0)
        
        if roll_deg > 0: 
            safe_action[1] = min(safe_action[1], -1.0 * danger_ratio)
        else: 
            safe_action[1] = max(safe_action[1], 1.0 * danger_ratio) 

    # Clean and return
    safe_action = np.clip(safe_action, -1.0, 1.0)

    if triggered:
        print(f"!!! MONITOR TRIGGERED !!!")
        print(f"   > Agent: {np.round(action, 3)}")
        print(f"   > Safe:  {np.round(safe_action, 3)}")

    return safe_action