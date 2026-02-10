import gymnasium as gym
from stable_baselines3 import SAC
import numpy as np
import sys
import os

current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment
from wrapper.flight_wrapper import flight_wrapper  # Import your Runtime Monitor Wrapper

# --- CONFIGURATION ---
MODEL_PATH = "./HPC_Results/Run2/models/sac_flight_model_1250000_steps.zip"  # The "Gravity Surfer" Model
MAX_STEPS = 15000  # Give it enough time to reach the target

def run_test_with_monitor():
    # 1. Create the Base Environment
    env = FlightEnvironment()
    env.max_steps = MAX_STEPS  # Ensure time limit matches

    # 2. APPLY THE WRAPPER (This is the Runtime Monitor)
    # The wrapper intercepts actions before they hit the environment
    env = flight_wrapper(env)

    # 3. Load the Model
    print(f"Loading model from: {MODEL_PATH}")
    model = SAC.load(MODEL_PATH)

    # 4. Run the Episode
    obs, _ = env.reset()
    done = False
    step = 0
    
    # Track safety stats
    violations = 0

    print("\n--- Starting Runtime Monitor Test (Press Ctrl+C to stop) ---")
    
    try:
        while not done:
            # Predict action
            action, _ = model.predict(obs, deterministic=True)
            
            # Step the environment (Wrapper handles the safety logic internally)
            obs, reward, terminated, truncated, info = env.step(action)
            
            # Check if the Monitor triggered (Assuming your wrapper adds info)
            # If your wrapper doesn't verify this yet, we can check manually:
            alt = obs[2]
            
            # Print status every 10 steps
            if step % 10 == 0:
                dist = np.linalg.norm(env.unwrapped.target_pos - obs[:3])
                print(f"Step: {step:4d} | Alt: {alt:6.1f} ft | Dist: {dist:6.1f} ft | Reward: {reward:6.2f}")

            done = terminated or truncated
            step += 1

            # Simple logic to see if we survived past the crash point
            if step == 2570:
                print("\n*** PASSED THE CRASH POINT (Step 2570) ***")
                print(f"Current Altitude: {alt:.1f} ft (Did the monitor save us?)")

    except KeyboardInterrupt:
        print("\nTest stopped by user.")
    
    print("\nTest Run Complete.")
    print(f"Final Altitude: {obs[2]:.1f} ft")
    if obs[2] > 0:
        print("RESULT: SUCCESS - The plane survived!")
    else:
        print("RESULT: FAILURE - The plane still crashed.")

if __name__ == "__main__":
    run_test_with_monitor()