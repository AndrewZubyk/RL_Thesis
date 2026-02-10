import numpy as np

def apply_runtime(action, observation):
    """
    PROPORTIONAL Runtime Monitor (Envelope Protection)
    
    Instead of hard overrides, this applies 'corrective pressure' 
    proportional to how far the agent is violating safety limits.
    
    It looks at:
    - Position (Alt, Roll, Pitch)
    - Rates (Vertical Speed, Roll Rate, Pitch Rate)
    """
    
    # 1. Setup - Copy Agent's Action
    # Action structure: [Aileron, Elevator, Rudder, Throttle]
    # Range: -1.0 to 1.0
    safe_action = np.array(action, copy=True)
    
    # 2. Extract State
    # Check your environment wrapper to ensure indices match!
    # Assuming: [Roll, Pitch, Yaw, P, Q, R, North, East, Alt]
    roll = observation[0]   # Radians
    pitch = observation[1]  # Radians
    # yaw = observation[2]  # (Usually don't limit yaw)
    p = observation[3]      # Roll Rate (rad/s)
    q = observation[4]      # Pitch Rate (rad/s)
    alt = observation[8]    # Altitude (ft)

    # --- CONFIGURATION: SMOOTH LIMITS ---
    
    # A. ALTITUDE ENVELOPE (The "Soft Floor")
    # We want to start pulling up gently at 500ft, and harder as we get lower.
    ALT_SOFT = 500.0  # Start worrying here
    ALT_HARD = 100.0  # Panic here
    
    # B. BANK ENVELOPE
    ROLL_LIMIT = np.deg2rad(45) # Max desired bank
    ROLL_KP = 2.0  # Strength of correction (Proportional Gain)
    ROLL_KD = 0.5  # Strength of damping (Derivative Gain - fights fast rolls)

    # C. PITCH ENVELOPE
    PITCH_MIN = np.deg2rad(-20) # Max dive angle
    PITCH_MAX = np.deg2rad(30)  # Max climb angle (stall protection)
    PITCH_KP = 2.0
    
    # --- LOGIC 1: SMOOTH GROUND AVOIDANCE ---
    
    # Calculate "Sink Rate" estimation (approximate using Pitch & Velocity if available, 
    # but here we use simple Proportional Alt error).
    
    if alt < ALT_SOFT:
        # Calculate how deep we are in the danger zone (0.0 to 1.0)
        # 1.0 means we are at the Hard Floor. 0.0 means we are at the Soft Floor.
        danger_level = (ALT_SOFT - alt) / (ALT_SOFT - ALT_HARD)
        danger_level = np.clip(danger_level, 0.0, 1.0)
        
        # Calculate corrective "Nudge" (Up Elevator)
        # If danger is 0.1 (460ft), add -0.1 elevator (gentle pull).
        # If danger is 1.0 (100ft), add -1.0 elevator (hard pull).
        # Note: In most sims, Negative Elevator is Up/Back.
        elevator_correction = -1.0 * danger_level 
        
        # Apply the Nudge (Additive)
        safe_action[1] += elevator_correction
        
        # Also gently add throttle if we are low
        safe_action[3] += (0.5 * danger_level)

    # --- LOGIC 2: ROLL LIMITER (With Damping) ---
    
    # If banking Right (> Limit)
    if roll > ROLL_LIMIT:
        excess = roll - ROLL_LIMIT
        # Correction = (How far over) * Strength + (How fast we are rolling) * Damping
        # We subtract because positive Aileron rolls Right, we want Left.
        correction = -(excess * ROLL_KP) - (p * ROLL_KD)
        safe_action[0] += correction

    # If banking Left (< -Limit)
    elif roll < -ROLL_LIMIT:
        excess = roll - (-ROLL_LIMIT) # will be negative
        # Correction will be positive (Right Aileron)
        correction = -(excess * ROLL_KP) - (p * ROLL_KD)
        safe_action[0] += correction

    # --- LOGIC 3: PITCH LIMITER ---
    
    # Prevent Nose High (Stall)
    if pitch > PITCH_MAX:
        excess = pitch - PITCH_MAX
        # Push nose down (Positive Elevator)
        safe_action[1] += (excess * PITCH_KP)
        
    # Prevent Nose Low (Dive) - BUT combine with Altitude Logic
    elif pitch < PITCH_MIN:
        excess = pitch - PITCH_MIN # negative
        # Pull nose up (Negative Elevator)
        safe_action[1] += (excess * PITCH_KP)

    # --- FINAL CLEANUP ---
    # Since we added values, we might have exceeded the -1 to 1 bounds.
    # We clip them back to legal range.
    safe_action = np.clip(safe_action, -1.0, 1.0)

    return safe_action