import os
import sys
import numpy as np
from stable_baselines3 import SAC

current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment
from wrapper.flight_wrapper import flight_wrapper

# --- CONFIGURATION ---
# Path to your trained model (Adjust filename if needed)
MODEL_PATH = "./HPC_Results/Run1/models/models/sac_final.zip"
# MODEL_PATH = "./models/sac_flight_model_250000_steps.zip" # Or use a specific checkpoint

# Waypoint definition
TARGET_NORTH = 5000.0
TARGET_EAST  = 5000.0 
TARGET_ALT   = 3000.0

def run_test():
    # Same wrapper setup as training
    try:
        raw_env = FlightEnvironment()
    except ConnectionRefusedError:
        print("Error: Could not connect to Simulink. Is the simulation running?")
        sys.exit()

    env = flight_wrapper(raw_env)

    # Load the Model
    if not os.path.exists(MODEL_PATH):
        print(f"Error: Model file not found at {MODEL_PATH}")
        print("Check your folder path or filename.")
        sys.exit()

    print(f"Loading model from: {MODEL_PATH}")
    model = SAC.load(MODEL_PATH)

    # Start the Replay Loop
    print("\n--- Starting Replay (Press Ctrl+C to stop) ---")
    obs, _ = env.reset()
    
    # Run for 4000 steps (approx 40 seconds)
    for i in range(4000):
        # deterministic=True for best action
        action, _states = model.predict(obs, deterministic=True)
        
        obs, reward, terminated, truncated, info = env.step(action)
        
        # --- FEEDBACK CALCULATIONS ---
        # Extract current position (Verify these indices match your Simulink output!)
        # Assuming: [North, East, Alt, ...]
        north = obs[0]
        east  = obs[1]
        alt   = obs[2]
        
        # Calculate Distance to Target
        error_n = TARGET_NORTH - north
        error_e = TARGET_EAST - east
        error_z = TARGET_ALT - alt
        dist_3d = np.sqrt(error_n**2 + error_e**2 + error_z**2)

        # Print Status every 10 steps
        if i % 10 == 0:
            print(f"Step: {i:4d} | Alt: {alt:6.1f} ft | Dist to Target: {dist_3d:6.1f} ft | Reward: {reward:6.2f}")

        # Success Condition if within 200 ft of target
        if dist_3d < 200.0:
            print(f"\n*** SUCCESS! Target reached at Step {i} ***")
            break

        if terminated or truncated:
            print("\nEpisode Finished (Crash or Timeout). Resetting...")
            obs, _ = env.reset()
            break

    print("Test run complete.")

if __name__ == "__main__":
    run_test()