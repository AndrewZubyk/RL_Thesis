#!/bin/bash
#PBS -N rl_flight_sac
#PBS -l nodes=1:ppn=192:gpus=1
#PBS -l walltime=24:00:00
#PBS -q normalq
#PBS -j oe
#PBS -o logs/trainingoutput$PBS_JOBID.log

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