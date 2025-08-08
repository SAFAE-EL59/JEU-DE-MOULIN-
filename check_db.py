import sqlite3

# Connexion à la base de données
conn = sqlite3.connect("mill_game.db")
cursor = conn.cursor()

# Récupérer les 10 dernières parties jouées
cursor.execute("SELECT * FROM games ORDER BY id DESC LIMIT 10")
games = cursor.fetchall()

conn.close()

# Afficher les résultats
print("📂 Historique des 10 derniers coups :")
for game in games:
    print(f"ID: {game[0]}, Board State: {game[1]}, Coup: {game[2]}")
