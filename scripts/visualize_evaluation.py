import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("evaluation_log.csv")

plt.plot(df['Step'], df['Price'], label='Price', color='black')

# Overlay Buy actions in green
buy_steps = df[df['Action'] == 'BUY']
plt.scatter(buy_steps['Step'], buy_steps['Price'], color='green', label='BUY', marker='^', s=100)

# Overlay Sell actions in red
sell_steps = df[df['Action'] == 'SELL']
plt.scatter(sell_steps['Step'], sell_steps['Price'], color='red', label='SELL', marker='v', s=100)

# Overlay Hold actions in blue 
hold_steps = df[df['Action'] == 'HOLD']
plt.scatter(hold_steps['Step'], hold_steps['Price'], color='blue', label='HOLD', alpha=0.3, s=50)

# Labels, title, legend
plt.xlabel("Step")
plt.ylabel("Price")
plt.title("RL Trading Bot Evaluation")
plt.legend()
plt.grid(True)

plt.show()
