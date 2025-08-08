#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BG_RED "\033[41m"
#define BG_BLUE "\033[44m"
#define RESET "\033[0m"

static int  joueur;
static int count = 0;
static int  found_p1 = 0, found_p2 = 0;

static int  taille_liste=0;


typedef struct {
    char alphabet; // Caractère
    int ligne; // Ligne
    int colonne; // Colonne
} Position;


typedef struct {
    int joueur;     // 1 pour Joueur 1, 2 pour Joueur 2
    char position;   // Position choisie (ex. 'A', 'B', ...)
    int ligne;       // Ligne correspondante
    int colonne;     // Colonne correspondante
} choix;


typedef struct {
    char position;      // La lettre de la position
    char adjacents[5];  // Liste des positions adjacentes
}adjascents;


typedef struct {
    char position ;
    char moulin[2][2];
}moulins;


choix static liste[24];


Position dict[24] = {
        {'A', 0, 0},
        {'B', 0, 21 / 2},
        {'C', 0, 21 - 1},
        {'J', 15 / 2, 0},
        {'K', 15 / 2, 21 / 5 - 1},
        {'L', 15 / 2, 21 / 3 - 1},
        {'N', 15 / 2, 21 - 21 / 5},
        {'M', 15 / 2, 21 - 21 / 3},
        {'O', 15 / 2, 21 - 1},
        {'V', 15 - 1, 0},
        {'W', 15 - 1, 21 / 2},
        {'X', 14, 21 - 1},
        {'D', 15 / 5 - 1, 21 / 5 - 1},
        {'E', 15 / 5 - 1, 21 / 2},
        {'F', 15 / 5 - 1, 21 - 21 / 5},
        {'G', 15 / 3 - 1, 21 / 3 - 1},
        {'H', 15 / 3 - 1, 21 / 2},
        {'I', 15 / 3 - 1, 21 - 21 / 3},
        {'P', 15 - 15 / 3, 21 / 3 - 1},
        {'Q', 15 - 15 / 3, 21 / 2},
        {'R', 15 - 15 / 3, 21 - 21 / 3},
        {'S', 15 - 15 / 5, 21 / 5 - 1},
        {'T', 15 - 15 / 5, 21 / 2},
        {'U', 15 - 15 / 5, 21 - 21 / 5}
    };


adjascents list[24] = {
    {'A', {'B', 'J', '\0'}},
    {'B', {'A', 'C', 'E', '\0'}},
    {'C', {'B', 'O', '\0'}},
    {'D', {'E', 'K', '\0'}},
    {'E', {'B', 'D', 'F', 'H', '\0'}},
    {'F', {'E', 'N', '\0'}},
    {'G', {'H', 'L', '\0'}},
    {'H', {'E', 'G', 'I', '\0'}},
    {'I', {'H', 'M', '\0'}},
    {'J', {'A', 'K', 'V', '\0'}},
    {'K', {'D', 'J', 'L', 'S', '\0'}},
    {'L', {'G', 'K', 'P', '\0'}},
    {'M', {'I', 'N', 'R', '\0'}},
    {'N', {'F', 'M', 'O', 'U', '\0'}},
    {'O', {'C', 'N', 'X', '\0'}},
    {'P', {'L', 'Q', '\0'}},
    {'Q', {'P', 'R', 'T', '\0'}},
    {'R', {'M', 'Q', '\0'}},
    {'S', {'K', 'T', '\0'}},
    {'T', {'Q', 'S', 'U', 'W', '\0'}},
    {'U', {'N', 'T', '\0'}},
    {'V', {'J', 'W', '\0'}},
    {'W', {'T', 'V', 'X', '\0'}},
    {'X', {'O', 'W', '\0'}}
};



moulins ensemble[24]={
        {'A', {{'B', 'C'}, {'J', 'V'}}},
        {'B', {{'A', 'C'}, {'E', 'H'}}},
        {'C', {{'A', 'B'}, {'O', 'X'}}},
        {'D', {{'E', 'F'}, {'K', 'S'}}},
        {'E', {{'D', 'F'}, {'B', 'H'}}},
        {'F', {{'D', 'E'}, {'N', 'U'}}},
        {'G', {{'H', 'I'}, {'L', 'P'}}},
        {'H', {{'G', 'I'}, {'E', 'B'}}},
        {'I', {{'G', 'H'}, {'M', 'R'}}},
        {'J', {{'A', 'V'}, {'K', 'L'}}},
        {'K', {{'J', 'L'}, {'D', 'S'}}},
        {'L', {{'J', 'K'}, {'G', 'P'}}},
        {'M', {{'N', 'O'}, {'I', 'R'}}},
        {'N', {{'M', 'O'}, {'F', 'U'}}},
        {'O', {{'M', 'N'}, {'C', 'X'}}},
        {'P', {{'Q', 'R'}, {'L', 'G'}}},
        {'Q', {{'P', 'R'}, {'T', 'W'}}},
        {'R', {{'P', 'Q'}, {'M', 'I'}}},
        {'S', {{'T', 'U'}, {'K', 'D'}}},
        {'T', {{'S', 'U'}, {'Q', 'W'}}},
        {'U', {{'S', 'T'}, {'N', 'F'}}},
        {'V', {{'A', 'J'}, {'W', 'X'}}},
        {'W', {{'V', 'X'}, {'T', 'Q'}}},
        {'X', {{'V', 'W'}, {'O', 'C'}}}
    };




char grille(char T[15][21]){
    int i,j,a,b;
    for (int i = 0; i < 15; i++){
    for (int j = 0; j <21; j++){
        T[i][j] = ' ';
    }
    }
    //pour les lignes '_'
    for(j=0;j<21;j++){
        T[0][j]='_';
        T[15-1][j]='_';
    }

    for(b=21-21/3;b<21;b++){
        T[15/2][b]='_';
    }

    for(a=0;a<21/3-1;a++){
            T[15/2][a]='_';
    }

    for(j=21/3-1;j<21-21/3;j++){
        T[15/3-1][j]='_';
        T[15-15/3][j]='_';
    }

    for(j=21/5-1;j<21-21/5;j++){
        T[15/6][j]='_';
        T[15-15/6-1][j]='_';
    }
    //pour les colonnes '|'
    for(i=1;i<15;i++){
        T[i][0]='|';
        T[i][21-1]='|';
    }

     for(b=15-15/3;b<15;b++){
        T[b][21/2]='|';
    }

    for(a=1;a<15/3;a++){
            T[a][21/2]='|';
    }

    for(i=15/3;i<15-15/3;i++){
        T[i][21/3-1]='|';
        T[i][21-21/3]='|';
    }

    for(i=15/5-1;i<15-15/5+1;i++){
        T[i][21/5-1]='|';
        T[i][21-21/5]='|';
    }

T[0][0]='A';T[0][21/2]='B';T[0][21-1]='C';
T[15/2][0]='J';T[15/2][21/5-1]='K';T[15/2][21/3-1]='L';
T[15/2][21-21/5]='N';T[15/2][21-21/3]='M';T[15/2][21-1]='O';
T[15-1][0]='V';T[15-1][21/2]='W';T[14][21-1]='X';
T[15/5-1][21/5-1]='D';T[15/5-1][21/2]='E';T[15/5-1][21-21/5]='F';
T[15/3-1][21/3-1]='G';T[15/3-1][21/2]='H';T[15/3-1][21-21/3]='I';
T[15-15/3][21/3-1]='P';T[15-15/3][21/2]='Q';T[15-15/3][21-21/3]='R';
T[15-15/5][21/5-1]='S';T[15-15/5][21/2]='T';T[15-15/5][21-21/5]='U';


}


void affichage(char T[15][21]) {
    printf("\n                ");
    printf("\n                ");
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 21; j++) {
            // Vérifier si cette position correspond à une position jouée
            int colorier = 0; // Indicateur pour savoir si une position doit être colorée
            for (int k = 0; k < count; k++) {
                if (liste[k].ligne == i && liste[k].colonne == j) {
                    if (liste[k].joueur == 1) {
                        printf(BG_RED "%c " RESET, T[i][j]); // Joueur 1 en rouge
                    } else if (liste[k].joueur == 2) {
                        printf(BG_BLUE "%c " RESET, T[i][j]); // Joueur 2 en bleu
                    }
                    colorier = 1; // La position a été colorée
                    break;
                }
            }
            if (!colorier) {
                // Si la position n'est pas occupée, affichez normalement
                printf("%c ", T[i][j]);
            }
        }
        printf("\n                ");
    }
}


void placer(char T[15][21],char pos){

int ligne,colonne;


    for (int i = 0; i < 24; i++) {
        if ((dict[i].alphabet == pos)) {
            ligne = dict[i].ligne;
            colonne = dict[i].colonne;
            if (count%2 == 0){
                liste[taille_liste].joueur = 1;
                liste[taille_liste].position = pos;
                liste[taille_liste].ligne = ligne;
                liste[taille_liste].colonne = colonne;
                    count++;
                    taille_liste++;
                }
            else
            {
                liste[taille_liste].joueur = 2;
                liste[taille_liste].position = pos;
                liste[taille_liste].ligne = ligne;
                liste[taille_liste].colonne = colonne;
                    count++;
                    taille_liste++;
                }
        }

    }

        affichage(T);
}


int pos_est_valide(char T[15][21], char pos) {
    for (int i = 0; i < taille_liste; i++) { // Vérifie toutes les positions déjà enregistrées
        if (liste[i].position == pos) {
            return 1; // Position déjà occupée
        }
    }
    return 0; // Si aucune correspondance, la position est valide
}




int est_adj(char pos1, char pos2){
    // Rechercher la position `pos1` dans le tableau
    for (int i = 0; i < 24; i++) {
        if (list[i].position == pos1) {
            for (int j = 0; list[i].adjacents[j] != '\0'; j++) {
                if (list[i].adjacents[j] == pos2) {
                    return 1; // Les deux positions sont adjacentes
                }
            }
            break;
        }
    }
    return 0; // Les deux positions ne sont pas adjacentes
}





int est_moulin(char T[15][21], char pos, int joueur) {
    int moulin_count = 0;
    char posadjt[9]; // Tableau pour stocker les positions jouées par le joueur
    int a = 0;       // Compteur pour les positions jouées

    // Collecter les positions jouées par le joueur
    for (int i = 0; i < taille_liste; i++) {
        if (liste[i].joueur == joueur) {
            posadjt[a] = liste[i].position;
            a++;
        }
    }

    // Vérifier les moulins possibles pour la position
    for (int b = 0; b < 24; b++) {
        if (ensemble[b].position == pos) {
            int found_p1 = 0, found_p2 = 0;


            for (int k = 0; k < a; k++) {
                if (posadjt[k] == ensemble[b].moulin[0][0]){found_p1 = 1;}
                if (posadjt[k] == ensemble[b].moulin[0][1]){found_p2 = 1;}
                if (posadjt[k] == ensemble[b].moulin[1][0]){found_p1 = 1;}
                if (posadjt[k] == ensemble[b].moulin[1][1]){found_p2 = 1;}
            }

            // Si les deux positions adjacentes sont trouvées, un moulin est détecté
            if (found_p1 && found_p2) {
                moulin_count++;
            }
        }
    }

    return moulin_count;
}



int capture_pion(char T[15][21], char pos,int joueur ) {
    int taille = taille_liste;
    // Vérifier la validité de la position
    if (!pos_est_valide(T, pos)) {
        return -2; // Position non valide
    }

    for (int i = 0; i < taille_liste; i++) {
        if ((liste[i].position == pos)&&(liste[i].joueur != joueur)) {

                if (est_moulin( T, pos, liste[i].joueur)==1) {
                    return -1; // Pion protégé par un moulin
                }
                else {
                     return 1;// le pion est capturé
                }
            }


        }
        return -2; // pion non valide

    }




void supprimer_choix(char position) {

    for (int i = 0; i < taille_liste; i++) {
        if (liste[i].position == position) {
            // Décaler les éléments pour combler l'espace
            for (int j = i; j < taille_liste - 1; j++) {
                liste[j] = liste[j + 1];
            }


            taille_liste--;


            break;
        }
    }
}

int deplacer(char T[15][21],char pos,char pos1){
    int taille = taille_liste;
    if((!pos_est_valide(T,pos1))&&est_adj(pos,pos1)){
            supprimer_choix(pos);
            for (int i = 0; i < 24; i++) {
            if ((dict[i].alphabet == pos1)) {
                liste[taille_liste].joueur = joueur;
                liste[taille_liste].position = pos1;
                liste[taille_liste].ligne = dict[i].ligne;
                liste[taille_liste].colonne = dict[i].colonne;
                taille_liste++;


            }
            else {return 0;} // si la position n'appartient pas à A et X

    }
    }
    else {return -1;}// position n'est pas valide
}



int pions_moulin(int joueur) {
    char T[15][21];
    for (int i = 0; i < taille_liste; i++) {

        if (liste[i].joueur == joueur && est_moulin(grille(T), liste[i].position, joueur) == 0) {
            return 0;
        }
    }

    return 1;
}

// fct qui renvoie le nbr de pions restant
int nbr_pion(int joueur ) {
    int nbr=0;
    for (int i=0;i<taille_liste;i++){
        if(liste[i].joueur==joueur)
            nbr++;
    }
    return nbr;
}
// // fct dtermine si une position appartient àç un joueur
//int pion_joueur(int joueur,char pos){
//        for(int i=0;i<taille_liste;i++){
//            if(liste[i].position==pos&&liste.joueur==joueur)
//                return 1 ;
//        }
//        return 0;
//}
