import numpy as np
import matplotlib.pyplot as plt
from random import random

class GridWorld:
    def __init__(self, grid):
        self.grid = np.array(grid)
        self.rows, self.cols = self.grid.shape
        self.start = (0, 0)
        self.goal = None
        self.obstacles = []

        # Find start, goal, and obstacles
        for i in range(self.rows):
            for j in range(self.cols):
                if self.grid[i, j] == 'S':
                    self.start = (i, j)
                elif self.grid[i, j] == 'G':
                    self.goal = (i, j)
                elif self.grid[i, j] == 'X':
                    self.obstacles.append((i, j))

        # Set rewards
        self.reward_goal = 10
        self.reward_obstacle = -10
        self.reward_step = -1

        # Initialize agent position
        self.agent_position = self.start

    def reset(self):
        self.agent_position = self.start

    def is_valid_move(self, action):
        i, j = self.agent_position
        if action == 'U':
            return i > 0 and (i - 1, j) not in self.obstacles
        elif action == 'D':
            return i < self.rows - 1 and (i + 1, j) not in self.obstacles
        elif action == 'L':
            return j > 0 and (i, j - 1) not in self.obstacles
        elif action == 'R':
            return j < self.cols - 1 and (i, j + 1) not in self.obstacles
        else:
            return False

    def take_action(self, action):
        if self.is_valid_move(action):
            i, j = self.agent_position
            if action == 'U':
                self.agent_position = (i - 1, j)
            elif action == 'D':
                self.agent_position = (i + 1, j)
            elif action == 'L':
                self.agent_position = (i, j - 1)
            elif action == 'R':
                self.agent_position = (i, j + 1)

        if self.agent_position == self.goal:
            return self.reward_goal
        elif self.agent_position in self.obstacles:
            return self.reward_obstacle
        else:
            return self.reward_step


class QLearningAgent:
    def __init__(self, actions, epsilon=0.1, alpha=0.2, gamma=0.9):
        self.actions = actions
        self.epsilon = epsilon
        self.alpha = alpha
        self.gamma = gamma
        self.q_table = {}

    def choose_action(self, state):
        if np.random.uniform(0, 1) < self.epsilon:
            return np.random.choice(self.actions)
        else:
            if state not in self.q_table:
                self.q_table[state] = {a: 0 for a in self.actions}
            return max(self.q_table[state], key=self.q_table[state].get)

    def learn(self, state, action, reward, next_state):
        if state not in self.q_table:
            self.q_table[state] = {a: 0 for a in self.actions}

        if next_state not in self.q_table:
            self.q_table[next_state] = {a: 0 for a in self.actions}

        best_next_action = max(self.q_table[next_state], key=self.q_table[next_state].get)
        self.q_table[state][action] += self.alpha * (reward + self.gamma * self.q_table[next_state][best_next_action] - self.q_table[state][action])

def train_agent(agent, env, episodes):
    rewards_per_episode = []

    for episode in range(episodes):
        state = env.start
        total_reward = 0

        while state != env.goal and state not in env.obstacles:
            action = agent.choose_action(state)
            reward = env.take_action(action)
            next_state = env.agent_position
            agent.learn(state, action, reward, next_state)
            total_reward += reward
            state = next_state

        rewards_per_episode.append(total_reward)
        env.reset()

    return rewards_per_episode


def evaluate_agent(agent, env, episodes):
    total_rewards = 0

    for _ in range(episodes):
        state = env.start

        while state != env.goal and state not in env.obstacles:
            action = agent.choose_action(state)
            total_rewards += env.take_action(action)
            state = env.agent_position

        env.reset()

    average_reward = total_rewards / episodes
    return average_reward


def visualize_path(agent, env):
    path = []
    state = env.start

    while state != env.goal and state not in env.obstacles:
        action = agent.choose_action(state)
        path.append(state)
        env.take_action(action)
        state = env.agent_position

    path.append(state)

    # Visualization code here (e.g., print the path or plot it on the grid)


# Example grid
grid = [
    ['S', '-', '-', 'X'],
    ['-', 'X', '-', '-'],
    ['-', '-', 'X', 'G'],
    ['-', '-', '-', 'X']
]

# Initialize environment and agent
environment = GridWorld(grid)
actions = ['U', 'D', 'L', 'R']
q_learning_agent = QLearningAgent(actions)

# Train the agent
episodes = 1000
rewards_per_episode = train_agent(q_learning_agent, environment, episodes)

# Plot cumulative reward per episode
plt.plot(np.cumsum(rewards_per_episode))
plt.xlabel('Episodes')
plt.ylabel('Cumulative Reward')
plt.title('Q-learning Training Progress')
plt.show()

# Evaluate the agent
evaluation_episodes = 100
average_reward = evaluate_agent(q_learning_agent, environment, evaluation_episodes)
print(f'Average Reward over {evaluation_episodes} Evaluation Episodes: {average_reward}')

# Visualize the agent's path
visualize_path(q_learning_agent, environment)

