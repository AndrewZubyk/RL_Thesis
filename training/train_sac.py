import os
import time
from stable_baselines3.sac import SAC
from stable_baselines3.common.callbacks import CheckpointCallback
from stable_baselines3.common.env_util import make_vec_env

from env.FlightEnvironment import FlightEnvironment
from monitoring.runtime_monitor import apply_runtime

# Configure
log_dir = "./logs/"
model_dir = "./models/"
total_timesteps = 250000 # Adjust if more or less time needed

def train_with_runtime_monitoring():
    '''
    Creates the environment, it is a single environment. Should I use VecEnv?
    '''

    # Creates the environment, it is a single environment. Should I use VecEnv?
    try:
        env = FlightEnvironment()
    except ConnectionRefusedError:
        print("Could not connect to Simulink. Ensure that Simulink is running and listening on the correct port.")
        return
    
    # Initialize the SAC model
    model = SAC(
        "MlpPolicy", # Creates connected neural network internally with this policy
        env,
        learning_rate=3e-4, # Standard learning rate for SAC, slows training but more stable
        buffer_size=1000000, # Large buffer for larger storage of the experiences
        learning_starts=10000, # Delay start to populate the replay buffer
        ent_coef='auto', # Automatic temperature (alpha) tuning for maximum entropy
        verbose=1, # Little printing to console
        tensorboard_log=log_dir # Log directory for tensorboard
    )

    print("Starting training...")

    obs, info = env.reset()
    for step in range(1, total_timesteps + 1):

        # Action selection by prediction
        action, _ = model.predict(obs, deterministic=False)

        # Attach runtime monitoring
        send_action = apply_runtime(action, obs)

        # Step the environment
        obs, reward, terminated, truncated, info = env.step(send_action)

        # Store transition and update model
        model.learn(total_timesteps=1, reset_num_timesteps=False)
        
        if terminated or truncated:
            obs, info = env.reset()
            
        if step % 50000 == 0:
            print(f"Timestep: {step}")
            model.save(f"{model_dir}/sac_flight_controller_{step}")

    # Final save
    model.save(f"{model_dir}/sac_final")
    env.close()
    print("Training completed.")

if __name__ == "__main__":
    os.makedirs(log_dir, exist_ok=True)
    os.makedirs(model_dir, exist_ok=True)
    train_with_runtime_monitoring() 