import numpy as np
import gym
from gym import spaces

class MillGameEnv(gym.Env):
    """ Environnement OpenAI Gym personnalisé pour le jeu du Moulin. """
    
    def __init__(self):
        super(MillGameEnv, self).__init__()
        
        # Définition de l’état : le plateau de 24 cases (0 = vide, 1 = joueur 1, 2 = joueur 2)
        self.state = np.zeros(24, dtype=int)
        
        # Actions possibles : Placer ou déplacer un pion (24 positions)
        self.action_space = spaces.Discrete(24)

        # Observation : L'état du plateau de jeu (vecteur de 24 cases)
        self.observation_space = spaces.Box(low=0, high=2, shape=(24,), dtype=int)

        self.current_player = 1  # L'IA commence toujours
        
    def step(self, action):
        """ Exécute un coup et retourne l'état suivant, la récompense et si la partie est terminée. """
        
        # Vérifier si l'action est valide (case libre)
        if self.state[action] == 0:
            self.state[action] = self.current_player
        else:
            return self.state, -10, True, {}  # Coup invalide : pénalité et fin du tour
        
        # Vérifier si le joueur a formé un moulin
        reward = 1 if self._is_mill(action) else 0

        # Vérifier si la partie est terminée
        done = self._check_game_over()

        # Changer de joueur
        self.current_player = 3 - self.current_player  # Alterne entre 1 et 2

        return self.state, reward, done, {}

    def reset(self):
        """ Réinitialise l'environnement. """
        self.state = np.zeros(24, dtype=int)
        self.current_player = 1
        return self.state

    def _is_mill(self, action):
        """ Vérifie si l'action a formé un moulin. """
        # (À compléter avec la logique du jeu du moulin)
        return False

    def _check_game_over(self):
        """ Vérifie si la partie est terminée (moins de 3 pions pour un joueur). """
        return False  # À implémenter

