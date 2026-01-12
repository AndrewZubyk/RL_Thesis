# Windows setup

# 1. Create venv if missing
if (-not (Test-Path "venv")) {
    Write-Host "Creating virtual environment..."
    python -m venv venv
}

# 2. Activate
Write-Host "Activating virtual environment..."
.\venv\Scripts\Activate.ps1

# 3. Install
Write-Host "Installing dependencies..."
pip install -r requirements.txt

Write-Host "Setup complete!"