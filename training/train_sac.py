import os
import time
import sys
from datetime import datetime
from stable_baselines3.sac import SAC
from stable_baselines3.common.callbacks import CheckpointCallback
from stable_baselines3.common.env_util import make_vec_env

# Get the path to the parent directory (RL_Thesis) and add it to the system path
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)
sys.path.append(parent_dir)

from env.FlightEnvironment import FlightEnvironment
from monitoring.runtime_monitor import apply_runtime
from wrapper.flight_wrapper import flight_wrapper

# Configure
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)

log_dir = os.path.join(parent_dir, "logs")
model_dir = os.path.join(parent_dir, "models")

total_timesteps = 100000 # Adjust if more or less time needed

def train_with_runtime_monitoring():
    '''
    Creates the environment, it is a single environment. Should I use VecEnv?
    '''

    # Create readable name for the run log
    now = datetime.now()
    run_time = now.strftime('%b%d_%H-%M')
    print(f"--- Starting Training Run: {run_time} ---")

    # Creates the environment, it is a single environment. Should I use VecEnv?
    try:
        raw_env = FlightEnvironment()
    except ConnectionRefusedError:
        print("Could not connect to Simulink. Ensure that Simulink is running and listening on the correct port.")
        return
    
    env = flight_wrapper(raw_env)

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
        save_freq = 50000,
        save_path = model_dir,
        name_prefix='sac_flight_model'
    )

    print("Starting training...")

    model.learn(
        total_timesteps=total_timesteps,
        callback=checkpoint_callback,
        progress_bar=True
    )

    # Final save
    model.save(f"{model_dir}/sac_final")
    env.close()
    print("Training completed.")

if __name__ == "__main__":
    os.makedirs(log_dir, exist_ok=True)
    os.makedirs(model_dir, exist_ok=True)
    train_with_runtime_monitoring() 