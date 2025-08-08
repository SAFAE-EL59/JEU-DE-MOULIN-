import sqlite3

# Connexion à la base de données (ou création si elle n'existe pas)
conn = sqlite3.connect("mill_game.db")
cursor = conn.cursor()

# Création de la table pour stocker les parties jouées
cursor.execute("""
CREATE TABLE IF NOT EXISTS games (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    board_state TEXT,  -- État du plateau sous forme de texte
    move TEXT          -- Coup joué (A à X)
)
""")

conn.commit()
conn.close()

