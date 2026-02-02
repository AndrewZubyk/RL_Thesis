#!/bin/bash
#SBATCH --job-name=rl_flight_sac
#SBATCH --output=logs/training_output_%j.log  # All prints stats go here
#SBATCH --error=logs/training_errors_%j.log   # Any system errors go here
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=16G
#SBATCH --time=24:00:00                       # Time marked for training
#SBATCH --gres=gpu:1                          # Request 1 GPU
#SBATCH --partition=gpu                       # Specify the GPU partition

# Load the Python module
module load python/3.10

# Move to the project root
cd $SLURM_SUBMIT_DIR

# Virtual Environment Setup
if [ ! -d "venv" ]; then
    echo "Creating virtual environment and installing dependencies..."
    python -m venv venv
    source venv/bin/activate
    pip install --upgrade pip
    pip install -r requirements.txt
else
    source venv/bin/activate
fi

# Create necessary directories if they don't exist
mkdir -p logs models

# Execute Training
# Note: Ensure train_sac.py has verbose=1 and progress_bar=False
python training/train_sac.py