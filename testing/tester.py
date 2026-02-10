import gymnasium as gym
from stable_baselines3 import SAC
import numpy as np
import sys
import os
import math

current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment
# IMPORT THE MONITOR LOGIC DIRECTLY
from monitoring.runtime_monitor import apply_runtime 

# --- CONFIGURATION ---
MODEL_PATH = "./HPC_Results/Run2/models/sac_flight_model_1000000_steps.zip" # The "Gravity Surfer" Model
MAX_STEPS = 15000

def run_debug_test():
    env = FlightEnvironment()
    env.max_steps = MAX_STEPS 
    
    print(f"Loading model: {MODEL_PATH}")
    model = SAC.load(MODEL_PATH)
    
    # Renamed 'obs' to 'observation'
    observation, _ = env.reset()
    done = False
    step = 0
    interventions = 0
    
    print("\n--- TEST START: WATCHING FLIGHT PATH ---")
    # Added Pitch column to the header
    print(f"{'Step':<6} | {'Alt (ft)':<10} | {'Dist (ft)':<10} | {'Roll (deg)':<10} | {'Pitch (deg)':<10} | {'Action Status'}")
    print("-" * 80)
    
    try:
        while not done:
            # 1. Agent Prediction
            original_action, _ = model.predict(observation, deterministic=True)
            
            # 2. Runtime Monitor Check
            safe_action = apply_runtime(original_action, observation)
            
            # 3. Check for Intervention
            is_intervention = False
            if not np.allclose(original_action, safe_action, atol=1e-5):
                interventions += 1
                is_intervention = True

            # 4. Execute Step
            observation, reward, terminated, truncated, info = env.step(safe_action)
            
            # 5. LOGGING (Every 10 steps OR if intervention happens)
            if step % 10 == 0 or is_intervention:
                alt = observation[2]
                dist = np.linalg.norm(env.target_pos - observation[:3])
                
                # Calculate angles
                roll_deg = math.degrees(observation[3])
                pitch_deg = math.degrees(observation[4]) # Pitch is index 4
                
                status = "NORMAL"
                if is_intervention:
                    status = "!!! MONITOR TRIGGERED !!!"
                
                print(f"{step:<6d} | {alt:<10.1f} | {dist:<10.1f} | {roll_deg:<10.1f} | {pitch_deg:<10.1f} | {status}")
                
                # If triggered, show details on next line
                if is_intervention:
                    print(f"       > Agent: {np.round(original_action, 3)}")
                    print(f"       > Safe:  {np.round(safe_action, 3)}")

            done = terminated or truncated
            step += 1

    except KeyboardInterrupt:
        print("\nStopped by user.")
        
    print("-" * 80)
    print("--- RESULTS ---")
    print(f"Total Steps Flown: {step}")
    print(f"Total Safety Interventions: {interventions}")
    print(f"Final Altitude: {observation[2]:.1f} ft")
    
    if observation[2] > 0 and step >= 1000:
        print("RESULT: SUCCESS - Plane flew stable!")
    elif observation[2] <= 0:
        print("RESULT: CRASH - Altitude hit 0.")
    else:
        print("RESULT: TIMEOUT/OTHER - Ended early.")

if __name__ == "__main__":
    run_debug_test()