'''import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Step 1: Data Preparation
data = pd.read_csv('AAPL.csv')  # Replace with your data source
data['Daily Returns'] = data['Adj Close'].pct_change()

# Step 2: Estimate Drift and Volatility
drift = data['Daily Returns'].mean()
volatility = data['Daily Returns'].std()

# Step 3: Monte Carlo Simulation
num_simulations = 10000
num_days = 252
dt = 1 / num_days
returns = np.exp((drift - 0.5 * volatility**2) * dt + volatility * np.sqrt(dt) * np.random.normal(0, 1, (num_days, num_simulations)))

initial_price = data['Adj Close'].iloc[-1]
simulated_prices = np.zeros_like(returns)
simulated_prices[0] = initial_price * np.exp(returns[0])
for t in range(1, num_days):
    simulated_prices[t] = simulated_prices[t - 1] * np.exp(returns[t])

# Step 4: Probability Calculation
threshold_price = 150
exceeds_threshold = (simulated_prices[-1] > threshold_price).sum()
probability = exceeds_threshold / num_simulations

# Step 5: Visualization
plt.figure(figsize=(12, 6))
plt.plot(data['Date'], data['Adj Close'], label='Historical Data', color='blue')
for i in range(10):
    plt.plot(data['Date'], simulated_prices[:, i], label=f'Simulated Path {i+1}', alpha=0.5)
plt.axhline(threshold_price, color='red', linestyle='--', label=f'Threshold Price: ${threshold_price}')
plt.xlabel('Date')
plt.ylabel('Stock Price')
plt.legend()
plt.title('Simulated Stock Price Paths and Historical Data')
plt.show()

# Print the probability
print(f'Probability of stock price exceeding ${threshold_price} within a year: {probability * 100:.2f}%')
*/'''
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Step 1: Data Preparation
data = pd.read_csv('AAPL.csv')  # Replace with your data source
data['Daily Returns'] = data['Adj Close'].pct_change()

# Step 2: Estimate Drift and Volatility
drift = data['Daily Returns'].mean()
volatility = data['Daily Returns'].std()

# Step 3: Monte Carlo Simulation
num_simulations = 10000
num_days = len(data)
dt = 1 / num_days

# Initialize the array to store simulated prices
simulated_prices = np.zeros((num_days, num_simulations))

# Set the initial stock price
initial_price = data['Adj Close'].iloc[-1]
simulated_prices[0] = initial_price

# Simulate stock price paths
for t in range(1, num_days):
    returns = np.exp((drift - 0.5 * volatility**2) * dt + volatility * np.sqrt(dt) * np.random.normal(0, 1, num_simulations))
    simulated_prices[t] = simulated_prices[t - 1] * returns

# Step 4: Probability Calculation
threshold_price = 150
exceeds_threshold = (simulated_prices[-1] > threshold_price).sum()
probability = exceeds_threshold / num_simulations

# Step 5: Visualization
plt.figure(figsize=(12, 6))
plt.plot(data['Date'], data['Adj Close'], label='Historical Data', color='blue')
for i in range(10):
    plt.plot(data['Date'], simulated_prices[:, i], label=f'Simulated Path {i+1}', alpha=0.5)
plt.axhline(threshold_price, color='red', linestyle='--', label=f'Threshold Price: ${threshold_price}')
plt.xlabel('Date')
plt.ylabel('Stock Price')
plt.legend()
plt.title('Simulated Stock Price Paths and Historical Data')
plt.show()

# Print the probability
print(f'Probability of stock price exceeding ${threshold_price} within a year: {probability * 100:.2f}%')
