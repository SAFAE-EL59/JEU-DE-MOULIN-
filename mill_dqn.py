import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam
import random
from collections import deque
from mill_game_env import MillGameEnv

class DQNAgent:
    """ Agent d'apprentissage par renforcement basé sur Deep Q-Network (DQN). """
    
    def __init__(self):
        self.env = MillGameEnv()  # Charger l'environnement
        self.state_size = 24  # 24 positions du plateau
        self.action_size = 24  # 24 coups possibles
        self.memory = deque(maxlen=2000)  # Mémoire d'expérience
        self.gamma = 0.95  # Facteur de réduction pour l’apprentissage
        self.epsilon = 1.0  # Probabilité d'exploration initiale
        self.epsilon_min = 0.01  # Exploration minimale
        self.epsilon_decay = 0.995  # Réduction progressive de l'exploration
        self.learning_rate = 0.001  # Taux d'apprentissage
        self.model = self._build_model()

    def _build_model(self):
        """ Construction du réseau de neurones DQN. """
        model = Sequential([
            Dense(128, activation="relu", input_shape=(self.state_size,)),
            Dense(128, activation="relu"),
            Dense(self.action_size, activation="linear")  # 24 sorties (scores des actions)
        ])
        model.compile(loss="mse", optimizer=Adam(learning_rate=self.learning_rate))

        return model

    def memorize(self, state, action, reward, next_state, done):
        """ Stocke une expérience en mémoire. """
        self.memory.append((state, action, reward, next_state, done))

    def act(self, state):
        """ Choisit une action avec epsilon-greedy (exploration vs exploitation). """
        if np.random.rand() <= self.epsilon:
            return random.randrange(self.action_size)  # Exploration
        q_values = self.model.predict(np.array([state]))[0]
        return np.argmax(q_values)  # Exploitation

    def replay(self, batch_size):
        """ Réentraînement du modèle DQN avec des expériences passées. """
        minibatch = random.sample(self.memory, min(len(self.memory), batch_size))
        for state, action, reward, next_state, done in minibatch:
            target = reward if done else reward + self.gamma * np.max(self.model.predict(np.array([next_state]))[0])
            target_q_values = self.model.predict(np.array([state]))[0]
            target_q_values[action] = target
            self.model.fit(np.array([state]), np.array([target_q_values]), epochs=1, verbose=0)
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay  # Réduction de l'exploration

    def train(self, episodes):
        """ Entraîne l’agent en jouant des parties. """
        for e in range(episodes):
            state = self.env.reset()
            done = False
            while not done:
                action = self.act(state)
                next_state, reward, done, _ = self.env.step(action)
                self.memorize(state, action, reward, next_state, done)
                state = next_state
            self.replay(32)
            print(f"✅ Épisode {e+1}/{episodes} terminé")
        self.model.save("mill_game_dqn.keras")

# Entraîner l'agent DQN
agent = DQNAgent()
agent.train(500)  # Entraînement sur 500 parties
