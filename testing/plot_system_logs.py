import pandas as pd
import matplotlib.pyplot as plt
import os
import math

# --- CONFIGURATION ---
script_dir = os.path.dirname(os.path.abspath(__file__))
CSV_FILE = os.path.join(script_dir, "system_monitor_log.csv")
MAX_STEPS_TO_PLOT = None 

def generate_plots():
    try:
        df = pd.read_csv(CSV_FILE)
    except FileNotFoundError:
        print(f"Error: Could not find {CSV_FILE}. Run your test_model.py script first!")
        return
    
    fig, axs = plt.subplots(2, 1, figsize=(12, 10), sharex=True)
    fig.suptitle('System Usage With Runtime Monitoring', fontsize=16, fontweight='bold')
    
    axs[0].plot(df["Elapsed_time"], df["CPU_percent"], label="CPU Usage", color="#1b3dd4")
    axs[0].plot(df["Elapsed_time"], df["RAM_percent"], label="RAM Usage", color="#d4841b")

    axs[0].set_xlim(0, df["Elapsed_time"].max())
    axs[0].set_ylim(0, 100)
    axs[0].set_ylabel("Usage (%)")
    axs[0].legend(loc="center left", bbox_to_anchor=(1.02, 0.5))    
    axs[0].grid(True, linestyle='--', alpha=0.6)

    axs[1].plot(df["Elapsed_time"], df["RAM_GB"], label="RAM Usage (GB)", color="#4fd41b")
    axs[1].set_xlim(0, df["Elapsed_time"].max())
    axs[1].set_ylim((math.floor(df["RAM_GB"].min() - 2), math.floor(df["RAM_GB"].max() + 2)))
    axs[1].set_xlabel("Time (s)")
    axs[1].set_ylabel("Usage (GB)")
    axs[1].legend(loc="center left", bbox_to_anchor=(1.02, 0.5))    
    axs[1].grid(True, linestyle='--', alpha=0.6)



    plt.tight_layout(rect=[0, 0, 0.98, 1])
    output_filename = os.path.join(script_dir, "system_monitor_graph.png")
    plt.savefig(output_filename, dpi=300)

    plt.show()

if __name__ == "__main__":
    generate_plots()