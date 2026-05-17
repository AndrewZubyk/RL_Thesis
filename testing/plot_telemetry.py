import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# --- CONFIGURATION ---
script_dir = os.path.dirname(os.path.abspath(__file__))
CSV_FILE = os.path.join(script_dir, "flight_baseline_telemetry_noMonitor.csv")
MAX_STEPS_TO_PLOT = None 

def generate_plots():
    print(f"Loading data from {CSV_FILE}...")
    try:
        df = pd.read_csv(CSV_FILE)
    except FileNotFoundError:
        print(f"Error: Could not find {CSV_FILE}. Run your test_model.py script first!")
        return

    if MAX_STEPS_TO_PLOT is not None and MAX_STEPS_TO_PLOT < len(df):
        df = df.head(MAX_STEPS_TO_PLOT)
        print(f"Plotting the first {MAX_STEPS_TO_PLOT} steps...")
    else:
        print(f"Plotting all {len(df)} steps...")

    fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
    fig.suptitle('Flight Telemetry Without Monitor Interventions', fontsize=16, fontweight='bold')

    # NEW: Helper function to plot multicolored lines instead of dots
    def plot_multicolor_line(ax, x_data, y_data, base_color, y_label):
        # 1. Plot the underlying normal flight line
        ax.plot(x_data, y_data, color=base_color, linewidth=1.0, label=f'{y_label} (Normal)')
        
        # 2. Create the red line mask. 
        # We use shift(1) to connect the intervention step to the resulting NEXT step.
        # This ensures even 1-step interventions form a visible red line segment.
        # is_interv = df["intervention"]
        # draw_red = is_interv | is_interv.shift(1).fillna(False)
        
        # # 3. Mask out the normal data (replace with NaN) and overlay the red line
        # y_red = y_data.mask(~draw_red)
        # ax.plot(x_data, y_red, color='purple', linewidth=1.25, label='Monitor Active')

    # 1. Altitude Plot
    plot_multicolor_line(axs[0], df["step"], df["altitude"], "#1bafd4", 'Altitude')
    axs[0].axhline(y=500.0, color='red', linestyle=':', alpha=0.5, label='Limits')
    axs[0].set_ylabel('Altitude (ft)')
    axs[0].set_xlim(0, df["step"].max())
    axs[0].grid(True, linestyle='--', alpha=0.6)
    handles, labels = axs[0].get_legend_handles_labels()
    axs[0].legend(handles[:3], labels[:3], loc="upper right")

    # 2. Pitch Plot
    plot_multicolor_line(axs[1], df["step"], df["pitch"], "#1bafd4", 'Pitch')
    axs[1].axhline(y=35.0, color='red', linestyle=':', alpha=0.5, label='Limits')
    axs[1].axhline(y=-25.0, color='red', linestyle=':', alpha=0.5)
    axs[1].set_ylabel('Pitch (deg)')
    axs[1].set_xlim(0, df["step"].max())
    axs[1].grid(True, linestyle='--', alpha=0.6)
    handles, labels = axs[1].get_legend_handles_labels()
    axs[1].legend(handles[:3], labels[:3], loc="upper right")

    # 3. Roll Plot
    plot_multicolor_line(axs[2], df["step"], df["roll"], "#1bafd4", 'Roll')
    axs[2].axhline(y=45.0, color='red', linestyle=':', alpha=0.5, label='Limits')
    axs[2].axhline(y=-45.0, color='red', linestyle=':', alpha=0.5)
    axs[2].set_ylabel('Roll (deg)')
    axs[2].set_xlabel('Simulation Steps')
    axs[2].set_xlim(0, df["step"].max())
    axs[2].grid(True, linestyle='--', alpha=0.6)
    handles, labels = axs[2].get_legend_handles_labels()
    axs[2].legend(handles[:3], labels[:3], loc="upper right")

    plt.tight_layout()
    
    output_filename = os.path.join(script_dir, "flight_baseline_graph_noMonitor.png")
    plt.savefig(output_filename, dpi=300)
    print(f"Success! Graph saved as '{output_filename}'")
    
    plt.show()

if __name__ == "__main__":
    generate_plots()