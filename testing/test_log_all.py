import gymnasium as gym
from stable_baselines3 import SAC
import numpy as np
import pandas as pd
import os
import glob
import re
import sys

# --- SETUP PATHS ---
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment

# Folder containing your .zip files
MODELS_DIR = "./HPC_Results/Run3/models"
OUTPUT_CSV = "./HPC_Results/Run3/benchmark_results.csv"

def extract_step_count(filename):
    match = re.search(r"(\d+)_steps", filename)
    if match:
        return int(match.group(1))
    return 0

def evaluate_model(model_path, env):
    try:
        model = SAC.load(model_path)
    except Exception as e:
        print(f"FAILED to load {model_path}: {e}")
        return None

    obs, _ = env.reset()
    done = False
    total_reward = 0
    steps = 0
    
    while not done:
        action, _ = model.predict(obs, deterministic=True)
        obs, reward, terminated, truncated, info = env.step(action)
        total_reward += reward
        steps += 1
        done = terminated or truncated

    # --- CRITICAL UPDATE: CAPTURE FINAL ALTITUDE ---
    final_alt = obs[2]  # Index 2 is Altitude
    final_dist = np.linalg.norm(env.target_pos - obs[:3])
    
    status = "CRASH"
    if final_alt > 0 and final_dist < 100:
        status = "SUCCESS"
    elif final_alt > 0 and steps >= env.max_steps:
        status = "TIMEOUT"
        
    return {
        "Model": os.path.basename(model_path),
        "Steps_Trained": extract_step_count(model_path),
        "Total_Reward": total_reward,
        "Steps_Flown": steps,
        "Final_Alt": final_alt,  # <--- LOGGED HERE
        "Final_Dist": final_dist,
        "Status": status
    }

def main():
    search_path = os.path.join(MODELS_DIR, "*.zip")
    model_files = glob.glob(search_path)
    
    if not model_files:
        print(f"No models found in {MODELS_DIR}!")
        return

    model_files.sort(key=extract_step_count)
    
    print(f"Found {len(model_files)} models. Starting Benchmark...\n")
    
    # Updated Header to show Final Alt
    print(f"{'Model Name':<30} | {'Reward':<10} | {'Status':<10} | {'Final Alt (ft)':<15} | {'Dist (ft)':<10}")
    print("-" * 85)

    results = []
    env = FlightEnvironment()

    for model_path in model_files:
        stats = evaluate_model(model_path, env)
        
        if stats:
            results.append(stats)
            # Updated Print to show Final Alt
            print(f"{stats['Model']:<30} | {stats['Total_Reward']:<10.1f} | {stats['Status']:<10} | {stats['Final_Alt']:<15.1f} | {stats['Final_Dist']:<10.1f}")

    df = pd.DataFrame(results)
    df.to_csv(OUTPUT_CSV, index=False)
    print("-" * 85)
    print(f"\nBenchmark Complete! Results saved to '{OUTPUT_CSV}'")

    print("\n--- TOP 5 MODELS (By Total Reward) ---")
    if not df.empty:
        top_5 = df.sort_values(by="Total_Reward", ascending=False).head(5)
        # Select specific columns to display clearly
        print(top_5[['Model', 'Total_Reward', 'Status', 'Final_Alt', 'Final_Dist']].to_string(index=False))
    else:
        print("No results to display.")

if __name__ == "__main__":
    main()