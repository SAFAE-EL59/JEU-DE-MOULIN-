import sqlite3
import numpy as np
import tensorflow as tf
import os


DB_FILE = "mill_game.db"
MODEL_FILE = "mill_game_model.keras"

import sqlite3
import numpy as np
import tensorflow as tf
import os
import sys

DB_FILE = "mill_game.db"
MODEL_FILE = "mill_game_model.keras"

def enregistrer_coup(board_state, move):
    """ Enregistre un coup joué dans la base de données """
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    board_state_str = ",".join(map(str, board_state))
    cursor.execute("INSERT INTO games (board_state, move) VALUES (?, ?)", (board_state_str, move))
    conn.commit()
    conn.close()
    print(f"✅ Coup enregistré : {board_state} → {move}")


def charger_donnees():
    """ Charger les parties jouées depuis la base de données """
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    cursor.execute("SELECT board_state, move FROM games")
    data = cursor.fetchall()
    conn.close()

    if not data:
        print("❌ Pas de données disponibles pour entraîner le modèle.")
        return None, None

    X, y = [], []
    for board_state, move in data:
        board = list(map(int, board_state.split(",")))
        move_index = ord(move) - ord('A')  # Convertir la lettre en indice (0-23)
        X.append(board)
        y.append(move_index)

    return np.array(X), np.array(y)

def entrainer_modele(X, y):
    """ Entraîne ou réentraîne un modèle avec les nouvelles données """
    model_path = MODEL_FILE
    if os.path.exists(model_path):
        print("🔄 Chargement du modèle existant...")
        model = tf.keras.models.load_model(model_path)
    else:
        print("🆕 Création d'un nouveau modèle...")
        model = tf.keras.Sequential([
            tf.keras.layers.Dense(128, activation="relu", input_shape=(24,)),
            tf.keras.layers.Dense(128, activation="relu"),
            tf.keras.layers.Dense(24, activation="softmax")  # Prédiction d'une case parmi 24
        ])
        model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])

    model.fit(X, y, epochs=25, verbose=1)  # 25 époques pour mieux apprendre
    model.save(model_path)
    print("✅ Modèle entraîné et sauvegardé !")




def appliquer_coup(board_state, move, joueur):
    """ Simule un coup et retourne le nouvel état du plateau """
    new_board = board_state[:]
    new_board[move] = joueur
    return new_board


def obtenir_coups_possibles(board_state, joueur):
    """ Retourne les coups valides pour un joueur donné """
    return [i for i in range(24) if board_state[i] == 0]  # Cases vides


def evaluer_plateau(board_state):
    """ Évalue l'état du plateau (heuristique simple) """
    score_joueur_2 = board_state.count(2)
    score_joueur_1 = board_state.count(1)
    return score_joueur_2 - score_joueur_1  # Plus l'IA a de pions, mieux c'est


def fin_de_partie(board_state):
    """ Vérifie si la partie est terminée """
    return board_state.count(1) < 3 or board_state.count(2) < 3  # Moins de 3 pions

def minimax(board_state, depth, is_maximizing):
    """ Algorithme Minimax pour évaluer le meilleur coup """
    if depth == 0 or fin_de_partie(board_state):
        return evaluer_plateau(board_state)

    if is_maximizing:
        best_score = -float("inf")
        for move in obtenir_coups_possibles(board_state, 2):
            new_board = appliquer_coup(board_state, move, 2)
            score = minimax(new_board, depth - 1, False)
            best_score = max(score, best_score)
        return best_score
    else:
        best_score = float("inf")
        for move in obtenir_coups_possibles(board_state, 1):
            new_board = appliquer_coup(board_state, move, 1)
            score = minimax(new_board, depth - 1, True)
            best_score = min(score, best_score)
        return best_score





 def predire_coup(board_state):
    """ Prédit le meilleur coup en se basant sur l'historique, le modèle IA et Minimax """
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    board_state_str = ",".join(map(str, board_state))
    # 🔹 Étape 1 : Vérifier dans la base de données
    cursor.execute("SELECT move FROM games WHERE board_state = ?", (board_state_str,))
    result = cursor.fetchall()
    conn.close()

    if result:
        coups = [r[0] for r in result]
        meilleur_coup = max(set(coups), key=coups.count)
        
        return meilleur_coup
    
    # 🔹 Étape 2 : Utiliser le modèle entraîné
    if os.path.exists(MODEL_FILE):
        model = tf.keras.models.load_model(MODEL_FILE)
        board_input = np.array([board_state], dtype=np.float32)
        predictions = model.predict(board_input)[0]

        move_index = np.argmax(predictions)
        meilleur_coup = chr(ord('A') + move_index)

        # Vérifier si l'IA ne prédit pas toujours "C"
        if meilleur_coup != "C":
            return meilleur_coup
        
    # 🔹 Étape 3 : Utilisation de Minimax
    return minimax_coup(board_state)







MODEL_FILE = "mill_game_dqn.keras"

def predire_coup(board_state):
    model = tf.keras.models.load_model(MODEL_FILE)
    q_values = model.predict(np.array([board_state]))[0]
    best_move_index = np.argmax(q_values)
    return chr(ord('A') + best_move_index)

if __name__ == "__main__":
    board_state = [int(x) for x in sys.argv[1:]]
    best_move = predire_coup(board_state)
    print(best_move)