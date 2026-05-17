import gymnasium as gym
from stable_baselines3 import SAC
import numpy as np
import pandas as pd
import os
import glob
import re
import sys

from stable_baselines3.common.vec_env import DummyVecEnv, VecNormalize

# --- SETUP PATHS ---
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment

# Folder containing your .zip files
MODELS_DIR = "./HPC_Results/Run7/models"
OUTPUT_CSV = "./HPC_Results/Run7/benchmark_results.csv"

def extract_step_count(filename):
    match = re.search(r"(\d+)_steps", filename)
    if match:
        return int(match.group(1))
    return 0

def evaluate_model(model_path, env):
    try:
        model = SAC.load(model_path, env=env)
    except Exception as e:
        print(f"FAILED to load {model_path}: {e}")
        return None

    obs = env.reset()

    base_env = env.envs[0].unwrapped

    done = False
    total_reward = 0
    steps = 0

    final_alt = 0.0
    final_dist = 0.0
    
    while not done:
        action, _ = model.predict(obs, deterministic=True)
        obs, reward, done_array, info = env.step(action)

        total_reward += reward[0]
        steps += 1
        done = done_array[0]

        if done:
            term_obs = info[0].get('terminal_observation')
            if term_obs is not None:
                raw_obs = env.unnormalize_obs(term_obs)
                final_alt = raw_obs[2]
                final_dist = np.linalg.norm(base_env.target_pos - raw_obs[:3])
    
    status = "CRASH"
    if final_alt > 0 and final_dist < 100:
        status = "SUCCESS"
    elif final_alt > 0 and steps >= base_env.max_steps:
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
    # env = FlightEnvironment()

    pkl_files = glob.glob(os.path.join(MODELS_DIR, "*.pkl"))
    normalize_pkl = pkl_files[0]

    def make_env ():
        return FlightEnvironment()
    
    vec_env = DummyVecEnv([make_env])

    env = VecNormalize.load(normalize_pkl, vec_env)

    env.training = False
    env.norm_reward = False

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