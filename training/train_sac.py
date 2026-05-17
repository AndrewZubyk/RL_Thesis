import os
import sys
import multiprocessing
from datetime import datetime
from stable_baselines3.sac import SAC
from stable_baselines3.common.callbacks import CheckpointCallback
from stable_baselines3.common.vec_env import SubprocVecEnv
from stable_baselines3.common.monitor import Monitor
from stable_baselines3.common.vec_env import VecNormalize

# Get the path to the parent directory (RL_Thesis) and add it to the system path
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment

# Configure
log_dir = "/scratch/zubyka/RL_Thesis"
# log_dir = "./logs"

log_dir = os.path.join(log_dir, "logs")
model_dir = os.path.join(log_dir, "models")

os.makedirs(log_dir, exist_ok=True)
os.makedirs(model_dir, exist_ok=True)

total_timesteps = 10000000 # Adjust if more or less time needed

def make_env(rank, log_dir):
    def _init():
        dll_path = os.path.abspath('./Thesis_C___grt_rtw/flight_model.so')

        if not os.path.exists(dll_path):
            raise FileNotFoundError(f"Could not find .so file at {dll_path}")
        
        print(f"--> [Worker {rank}] Attempting to load FlightEnvironment from .so file...")
        env = FlightEnvironment(dll_path=dll_path)

        print(f"--> [Worker {rank}] FlightEnvironment loaded successfully!")
        env = Monitor(env, os.path.join(log_dir, str(rank)))
        return env
    return _init

def train_with_runtime_monitoring():
    '''
    Creates the environment, it is a single environment. Should I use VecEnv?
    '''

    # Create readable name for the run log
    now = datetime.now()
    run_time = now.strftime('%b%d_%H-%M')
    print(f"--- Starting Training Run: {run_time} ---")

    # Creates the environment, it is a single environment. Should I use VecEnv?
    ''' try:
        raw_env = FlightEnvironment(dll_path='./Thesis_C___grt_rtw/flight_model.so')
    except FileNotFoundError as e:
        print(f"Error: {e}")
        print("Ensure the .so file is compiled and in the correct directory for the HPC.")
        return
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return
    '''

    run_log_dir = os.path.join(log_dir, run_time)
    os.makedirs(run_log_dir, exist_ok=True)

    num_cpu = min(multiprocessing.cpu_count(), 16) # Use 16 on HPC, but fewer on a laptop
    env = SubprocVecEnv([make_env(i, run_log_dir) for i in range(num_cpu)])

    env = VecNormalize(env, norm_obs=True, norm_reward=True, clip_obs=10.)

    # Initialize the SAC model
    model = SAC(
        "MlpPolicy", # Creates connected neural network internally with this policy
        env,
        learning_rate=3e-4, # Standard learning rate for SAC, slows training but more stable
        buffer_size=1000000, # Large buffer for larger storage of the experiences
        learning_starts=1000, # Delay start to populate the replay buffer
        ent_coef='auto', # Automatic temperature (alpha) tuning for maximum entropy
        verbose=1, # Little printing to console
        tensorboard_log=log_dir # Log directory for tensorboard
        #tb_log_name=run_time # Name for tensorboard run
    )

    # Checkpoint callback
    checkpoint_callback = CheckpointCallback(
        save_freq = 15625, # this is 250k / 16 (due to multiprocessing)
        save_path = model_dir,
        name_prefix='sac_flight_model'
    )

    print("Starting training...")

    model.learn(
        total_timesteps=total_timesteps,
        callback=checkpoint_callback,
        progress_bar=False
    )

    # Final save
    model.save(f"{model_dir}/sac_final")
    env.save(os.path.join(model_dir, f"vec_normalize_{run_time}.pkl"))
    env.close()
    print("Training completed.")

if __name__ == "__main__":
    try:
        multiprocessing.set_start_method('spawn', force=True)
    except RuntimeError:
        pass

    os.makedirs(log_dir, exist_ok=True)
    os.makedirs(model_dir, exist_ok=True)
    train_with_runtime_monitoring()