#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED


void grille(char T[15][21]);
void affichage();
void placer();
int pos_est_valide();
int est_adj();
int est_moulin(char T[15][21],char pos, int joueur);
int capture_pion(char T[15][21],char pos,int joueur);
void supprimer_choix(char position);
int deplacer(char T[15][21],char pos,char pos1);
int pions_moulin(int joueur);
int nbr_pion(int joueur );
int pion_joueur(int joueur,char pos);



#endif // PROTOTYPE_H_INCLUDED
