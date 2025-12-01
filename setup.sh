#!/bin/bash

# 1. Create the virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    echo "Creating virtual environment..."
    python3 -m venv venv
fi

# 2. Activate the environment
echo "Activating virtual environment..."
source venv/bin/activate

# 3. Install dependencies
echo "Installing required packages..."
pip install -r requirements.txt

echo "Setup complete! Virtual environment is ready."
