import pandas as pd
import numpy as np
import sys
import os
import math
import glob
import csv, time, psutil, threading

from stable_baselines3.common.vec_env import DummyVecEnv, VecNormalize
from stable_baselines3 import SAC
from datetime import datetime

current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment

# --- CONFIGURATION ---
# for run6 we run 9.5 million
# For run7 we use 9.75 or 6.75 million
MODEL_PATH = "./HPC_Results/Run7/models/sac_flight_model_9750000_steps.zip"
# MODEL_PATH = "./HPC_Results/Run6/models/sac_flight_model_9500000_steps.zip"
MODEL_DIR = "./HPC_Results/Run7/models"
MAX_STEPS = 1000000

stop_monitor = threading.Event()

def run_baseline_test():
    def make_env():
        return FlightEnvironment()
    
    vec_env =  DummyVecEnv([make_env])

    pkl_files = glob.glob(os.path.join(MODEL_DIR, "*.pkl"))
    if not pkl_files:
        print(f"No .pkl files found in {MODEL_DIR}. Please ensure the model is saved correctly.")
        return
    
    env = VecNormalize.load(pkl_files[0], vec_env)
    env.training = False
    env.norm_reward = False

    base_env = env.envs[0].unwrapped

    print(f"Loading baseline model from: {MODEL_PATH}")
    model = SAC.load(MODEL_PATH, env=env)

    observation = env.reset()
    done = False
    step = 0
    
    print("\n--- TEST START: WATCHING BASELINE FLIGHT PATH ---")
    print(f"{'Step':<6} | {'Alt (ft)':<10} | {'Dist (ft)':<10} | {'Roll (deg)':<10} | {'Pitch (deg)':<10} | {'Action Status'}")
    print("-" * 80)

    monitor_thread = threading.Thread(target=system_monitor, args=("system_monitor_log_noMonitor.csv", 1.0))
    monitor_thread.daemon = True
    monitor_thread.start()

    telemetry = {
        "step": [],
        "altitude": [],
        "pitch": [],
        "roll": [],
        "disturbance": []
    }

    disturbance_int = 25000
    disturbance_dur = 20
    
    try:
        while not done:
            # 0. Get the raw physical state for the current step BEFORE doing anything
            raw_obs = base_env._get_obs() 
            
            # 1. Get action from RL Agent
            agent_action, _ = model.predict(observation, deterministic=True)
            
            # 2. Check if we are currently inside a wind gust window
            in_disturbance = False
            if step > 100 and (step % disturbance_int) < disturbance_dur:
                in_disturbance = True
                
            # 3. Apply Controls
            if in_disturbance:
                # ARTIFICIAL WIND GUST: Force max roll right, slight pitch down, max throttle
                final_action = np.array([0.5, 1.0, 0.0, 1.0]) 
            else:
                # NORMAL FLIGHT: Pass the agent's action directly to the environment
                final_action = agent_action[0]

            # --- LOG TELEMETRY ---
            telemetry["step"].append(step)
            telemetry["altitude"].append(raw_obs[2])
            telemetry["pitch"].append(np.degrees(raw_obs[4]))
            telemetry["roll"].append(np.degrees(raw_obs[3]))
            telemetry["disturbance"].append(in_disturbance) 
            # ---------------------

            # 4. Execute Step
            observation, reward, done_array, info = env.step([final_action])
            done = done_array[0]
            
            # 5. LOGGING (Every 50 steps)
            if step % 50 == 0:
                alt = raw_obs[2]
                dist = np.linalg.norm(base_env.target_pos - raw_obs[:3])
                
                # Calculate angles
                roll_deg = math.degrees(raw_obs[3])
                pitch_deg = math.degrees(raw_obs[4]) # Pitch is index 4
                
                status = "GUST APPLIED" if in_disturbance else "NORMAL (BASELINE)"
                
                print(f"{step:<6d} | {alt:<10.1f} | {dist:<10.1f} | {roll_deg:<10.1f} | {pitch_deg:<10.1f} | {status}")

            step += 1

            if done:
                term_obs = info[0].get('terminal_observation')
                if term_obs is not None:
                    final_raw_obs = env.unnormalize_obs(term_obs)

    except KeyboardInterrupt:
        print("\nStopped by user.")
        
    stop_monitor.set()
    monitor_thread.join()
    
    print(f"\nTotal Steps Flown: {step}")
    
    # Safely pull the altitude from the raw, un-normalized final observation
    if 'final_raw_obs' in locals():
         print(f"Final Altitude: {final_raw_obs[2]:.1f} ft")
         if final_raw_obs[2] > 0 and step >= 1000:
             print("RESULT: SUCCESS - Plane flew stable!")
         elif final_raw_obs[2] <= 0:
             print("RESULT: CRASH - Altitude hit 0.")
         else:
             print("RESULT: CRASH/OTHER - Ended early (Likely Pitch/Roll limit).")
    else:
        # Fallback in case of manual keyboard interrupt
        print(f"Final Altitude: {raw_obs[2]:.1f} ft")
        print("RESULT: TIMEOUT/OTHER")

    print ("\n --- Saving Telemetry ---")
    df = pd.DataFrame(telemetry).head(100000)

    script_dir = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(script_dir, "flight_baseline_telemetry_noMonitor.csv")

    df.to_csv(csv_path, index=False)
    print(f"Telemetry saved to '{csv_path}'")

def system_monitor(log_file="system_monitor_log_noMonitor.txt", interval=5):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    full_dir = os.path.join(script_dir, log_file)

    with open(full_dir, "w", newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['Elapsed_time', 'CPU_percent', 'RAM_percent', 'RAM_GB'])

        psutil.cpu_percent(interval=0.1) # Initialize CPU percent calculation

        start_time = time.time()

        while not stop_monitor.is_set():
            seconds_elapsed = math.floor(time.time() - start_time)
            cpu = psutil.cpu_percent(interval=None)
            mem = psutil.virtual_memory()
            ram_gb = mem.used / (1024 ** 3)

            writer.writerow([seconds_elapsed, cpu, mem.percent, round(ram_gb, 2)])
            f.flush()

            stop_monitor.wait(interval)
        

if __name__ == "__main__":
    run_baseline_test()