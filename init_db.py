import pandas as pd
import numpy as np
import tensorflow as tf
import sys
import os

MODEL_FILE = "mill_game_model.h5"
DATA_FILE = "data.csv"

import os

DATA_FILE = "data.csv"

if os.path.exists(DATA_FILE):
    print(f"✅ Le fichier {DATA_FILE} est bien présent.")
else:
    print(f"❌ Le fichier {DATA_FILE} est introuvable ! Vérifiez son emplacement.")



def charger_donnees():
    """ Charger les données d'entraînement depuis data.csv """
    if not os.path.exists(DATA_FILE):
        return None, None

    df = pd.read_csv(DATA_FILE, header=None)
    X = df.iloc[:, :-1].values  # États du plateau (24 cases)
    y = df.iloc[:, -1].values   # Coups joués
    y = np.array([ord(c) - ord('A') for c in y])  # Convertir lettres en indices 0-23
    return X, y

def entrainer_modele(X, y):
    """ Entraîner un modèle de réseau de neurones """
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(64, activation="relu", input_shape=(24,)),
        tf.keras.layers.Dense(64, activation="relu"),
        tf.keras.layers.Dense(24, activation="softmax")  # Prédiction d'une case parmi 24
    ])
    model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
    model.fit(X, y, epochs=10, verbose=1)
    model.save(MODEL_FILE)

# Charger ou entraîner le modèle
X, y = charger_donnees()
if X is not None:
    entrainer_modele(X, y)

# Lire l'état du jeu envoyé par le programme C
if len(sys.argv) > 1:
    board_state = np.array([int(x) for x in sys.argv[1:]], dtype=np.float32).reshape(1, -1)
    
    if os.path.exists(MODEL_FILE):
        model = tf.keras.models.load_model(MODEL_FILE)
        move_index = np.argmax(model.predict(board_state))
        print(chr(ord('A') + move_index))  # Convertir l'index en lettre
    else:
        print("A")  # Coup par défaut si pas de modèle
