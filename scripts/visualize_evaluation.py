import pandas as pd
import matplotlib.pyplot as plt

# Load evaluation log
df = pd.read_csv("./data/evaluation_log.csv")

# Create figure and axis
fig, ax1 = plt.subplots(figsize=(14, 7))

# Plot price
ax1.plot(df['Step'], df['Price'], label='Price', color='black', linewidth=2)
ax1.set_xlabel("Step", fontsize=14)
ax1.set_ylabel("Price", fontsize=14)
ax1.tick_params(axis='y', labelcolor='black')

# Overlay actions
ax1.scatter(df[df['Action']=='BUY']['Step'], df[df['Action']=='BUY']['Price'],
            color='green', label='BUY', marker='^', s=120)
ax1.scatter(df[df['Action']=='SELL']['Step'], df[df['Action']=='SELL']['Price'],
            color='red', label='SELL', marker='v', s=120)
ax1.scatter(df[df['Action']=='HOLD']['Step'], df[df['Action']=='HOLD']['Price'],
            color='blue', label='HOLD', alpha=0.3, s=50)

# Plot cumulative reward on secondary axis
ax2 = ax1.twinx()
ax2.plot(df['Step'], df['CumulativeReward'], label='Cumulative Reward', color='orange', linewidth=2, linestyle='--')
ax2.set_ylabel("Cumulative Reward", fontsize=14)
ax2.tick_params(axis='y', labelcolor='orange')

# Title, legend, grid
fig.suptitle("RL Trading Bot Evaluation", fontsize=16)
fig.legend(loc="upper left", bbox_to_anchor=(0.1,0.9))
ax1.grid(True, linestyle='--', alpha=0.5)

plt.show()
