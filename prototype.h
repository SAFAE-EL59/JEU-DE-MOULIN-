#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

//fonctions d'affichage :
void grille(char T[15][21]);
void titre();
void affichage();


//fonctions de verifications :
int pos_est_valide();
int est_adj();
int est_moulin(char T[15][21],char pos, int joueur);
int capture_pion(char T[15][21],char pos,int joueur);
int pion_joueur(int joueur,char pos);
int pions_moulin(int joueur);
int nbr_pion(int joueur );
int position_bloquee(char T[15][21],char pos);
int positions_bloquees(int joueur);


//fcts de placement :
void placer();
void placer_pion(char T[15][21],char pos,int joueur);


//fcts pour le deplacement :
void supprimer_choix(char T[15][21],char position);
int deplacer(char T[15][21],char pos,char pos2,int joueur);


//fct pour l'annonce de la victoire :
void afficher_defaite(int joueur,char prenom1[],char prenom2[], int raison);


//fcts machine :
char capturaion_machine(char T[15][21],int niveau);
char choix_placement(int niveau);
char choix_deplacement(int niveau);
char choix_position_machine(char T[15][21],char pion, int niveau);


// fcts de placement Machine:
void joueurs(char T[15][21],int joueur,int niveau,char prenom1[],char prenom2[]);
void palcement_phase(char T[15][21],int niveau,char prenom1[],char prenom2[]);


//fct de deplacement Machine :
void deplacement_phase(char T[15][21], int niveau, char prenom1[], char prenom2[]);


// partie AI avancée :
void sauvegarder_coup(char grille[15][21], char move, int joueur);
char obtenir_coup_ia(int board[24]);
char obtenir_coup_iadql(int board[24]) ;
void traduc_grille_board();


#endif // PROTOTYPE_H_INCLUDED
