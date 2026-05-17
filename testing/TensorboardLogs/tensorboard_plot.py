import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def smooth_data(scalars, weight=0.8):
    """
    Replicates TensorBoard's EMA smoothing.
    Weight should be between 0 and 1. Higher = smoother.
    """
    if len(scalars) == 0:
        return []
    last = scalars[0]
    smoothed = []
    for point in scalars:
        smoothed_val = last * weight + (1 - weight) * point
        smoothed.append(smoothed_val)
        last = smoothed_val
    return smoothed

# 1. Set up the visual style for an academic paper
sns.set_theme(style="whitegrid", context="paper")
plt.rcParams.update({'font.size': 12, 'axes.labelsize': 14, 'legend.fontsize': 12})
# Create a formatter to show millions on the X-axis (e.g., 2M, 4M)
formatter = plt.FuncFormatter(lambda x, pos: f'{x*1e-6:g}M')


# ==========================================
# PLOT 1: EPISODE LENGTH
# ==========================================
script_dir = os.path.dirname(os.path.abspath(__file__))
CSV_FILE = os.path.join(script_dir, "ep_len_mean.csv")
df_len = pd.read_csv(CSV_FILE)
df_len['Smoothed'] = smooth_data(df_len['Value'].values, weight=0.8)

plt.figure(figsize=(8, 4.5))
plt.plot(df_len['Step'], df_len['Value'], color='lightsteelblue', alpha=0.5, label='Raw Data')
plt.plot(df_len['Step'], df_len['Smoothed'], color='navy', linewidth=2, label='Smoothed (EMA)')

plt.xlabel('Training Steps')
plt.ylabel('Mean Episode Length')
plt.xlim(0, df_len["Step"].max())
plt.title('Training Performance: Episode Length', fontsize=16, pad=15)
plt.gca().xaxis.set_major_formatter(formatter)
plt.legend(loc='lower right')
plt.tight_layout()

output_filename = os.path.join(script_dir, "ep_len_mean.png")
plt.savefig(output_filename, dpi=300)
print("Saved: episode_length_plot.png")
plt.close() # Close figure to prevent overlap


# ==========================================
# PLOT 2: EPISODE REWARD
# ==========================================
CSV_FILE_REW = os.path.join(script_dir, "ep_rew_mean.csv")
df_rew = pd.read_csv(CSV_FILE_REW)
df_rew['Smoothed'] = smooth_data(df_rew['Value'].values, weight=0.8)

plt.figure(figsize=(8, 4.5))
# Using a different color for the reward to distinguish it from length
plt.plot(df_rew['Step'], df_rew['Value'], color='lightcoral', alpha=0.5, label='Raw Data')
plt.plot(df_rew['Step'], df_rew['Smoothed'], color='darkred', linewidth=2, label='Smoothed (EMA)')

plt.xlabel('Training Steps')
plt.ylabel('Mean Episode Reward')
plt.xlim(0, df_rew["Step"].max())
plt.title('Training Performance: Episode Reward', fontsize=16, pad=15)
plt.gca().xaxis.set_major_formatter(formatter)
plt.legend(loc='lower right')
plt.tight_layout()

output_filename = os.path.join(script_dir, "ep_rew_mean.png")
plt.savefig(output_filename, dpi=300)
print("Saved: episode_reward_plot.png")
plt.close()