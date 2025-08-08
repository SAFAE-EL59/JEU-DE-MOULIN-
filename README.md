# JEU-DE-MOULIN-

🎮 Jeu de Moulin

📌 Présentation
Ce projet est une implémentation en langage C du Jeu de Moulin (Nine Men's Morris), un jeu de plateau stratégique dont les origines remontent à l’Antiquité.
Il permet de jouer :

🆚 Joueur vs Joueur
🆚 Joueur vs Machine (3 niveaux : Normal, Hard, Insane)
Le développement a été réalisé dans le cadre d’un projet académique à l’EHTP, sous l’encadrement de Mme Cherrabi Meryem.

🕹️ Règles du jeu
Le plateau comporte 24 positions et chaque joueur possède 9 pions.
Phase de placement : les joueurs placent leurs pions à tour de rôle.
Phase de déplacement : déplacer ses pions pour former des moulins (alignements de 3 pions).
Lorsqu’un moulin est formé, le joueur capture un pion adverse.
Victoire si l’adversaire n’a plus que 2 pions ou ne peut plus se déplacer.


⚙️ Fonctionnalités
Menu principal interactif.
Mode Joueur vs Joueur en console.
Mode Joueur vs Machine :
Normal : coups aléatoires.
Hard : IA avec base de données SQLite + réseau de neurones TensorFlow + algorithme Minimax.(au cours du développement )
Insane : IA avec Deep Q-Learning pour apprentissage par renforcement. (au cours du développement )
Détection automatique des moulins.
Phase spéciale de "vol" lorsque le joueur n’a plus que 3 pions.


🛠️ Technologies utilisées
Langage C (logique du jeu et affichage console)
Python (IA)( au cours du développement)
SQLite (stockage des coups)( au cours du développement)
TensorFlow/Keras (réseau de neurones)( au cours du développement)
Algorithme Minimax( au cours du développement)
Deep Q-Learning (IA avancée)( au cours du développement)



## ⚠️ Remarque d'exécution

Le fichier **`fonction.exe`** ne fonctionne pas encore, car il est lié à l’option **IA avancée**  
(modes *Hard* et *Insane*) dont la configuration n’a pas encore été finalisée.

Pour tester le jeu, veuillez utiliser **`play.exe`**, qui contient la version pleinement fonctionnelle avec :
- Mode **Joueur vs Joueur**
- Mode **Joueur vs Machine – Normal (facile)**

Cela permet de profiter de toutes les fonctionnalités complètes déjà implémentées,  
tout en laissant la possibilité de développer et d’intégrer ultérieurement les niveaux IA avancés.



📂 Structure du projet
