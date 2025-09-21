# Deep Q-Learning Trading Agent

A reinforcement learning agent that learns to trade a single stock (AAPL) using **Deep Q-Learning (DQN)**.  
The agent observes market features (price, momentum, position) and chooses actions (buy, sell, hold) to maximize profit.

---

## 🚀 Motivation
This project explores how reinforcement learning can be applied to **algorithmic trading**.  
Instead of using fixed trading strategies, the agent learns **directly from data** to adapt to changing market conditions.

- Wanted to strengthen C++ skills by implementing a neural network and Deep Q-Learning from scratch.

- Aimed to understand RL internals at a deeper level, including forward/backward passes, Q-value updates, and reward shaping.

- Interested in applying AI/ML techniques to financial markets for hands-on experience in algorithmic trading.

---

## 🧠 Methodology

- **Environment**: AAPL historical prices (CSV), simulating market dynamics.
- **State**: `[price, position, momentum]`
- **Actions**: `Buy | Sell | Hold`
- **Reward**: Profit and loss (PnL) based on trades.
- **Agent**: Deep Q-Network (DQN) with:
  - 1 hidden layer (64 neurons, ReLU).
  - Q-value updates via backpropagation.
  - ε-greedy exploration.
- **Training**: 2000 episodes × 100 steps.
- **Evaluation**: Fixed policy after training.

---

## 📊 Results

- Initially the agent defaulted to always holding or always buying.  
- With tuned hyperparameters and smaller weight initialization, the agent began making **meaningful trading decisions**.  
- Example evaluation log:

Step 0 | Q-values: 12.1 11.8 11.9 | Action: HOLD | Reward: 0 | Price: 104.1 | Position: 0
Step 1 | Q-values: 12.2 12.5 12.3 | Action: BUY | Reward: 0 | Price: 105.2 | Position: 1
Step 2 | Q-values: 13.0 12.8 12.7 | Action: SELL | Reward: +1.1 | Price: 109.2 | Position: 0



