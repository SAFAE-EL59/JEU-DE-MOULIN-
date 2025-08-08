#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PYTHON_SCRIPT "python ml_ai.py"
#define PYTHON_SCRIPTT "python mill_ai.py"




#define BG_RED "\033[41m"
#define BG_BLUE "\033[44m"
#define RESET "\033[0m"
static int chance1,chance2;
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




// Fonctions d'affichages :
void titre(){
printf("\n");
printf("\t\033[31m       _ ______ _    _   _____  ______  \033[0m  \033[34m__  __  ____  _    _ _      _____ _   _\033[0m\n");
printf("\t\033[31m      | |  ____| |  | | |  __ \\|  ____|\033[0m  \033[34m|  \\/  |/ __ \\| |  | | |    |_   _| \\ | |\033[0m\n");
printf("\t\033[31m      | | |__  | |  | | | |  | | |__    \033[0m \033[34m| \\  / | |  | | |  | | |      | | |  \\| |\033[0m\n");
printf("\t\033[31m  _   | |  __| | |  | | | |  | |  __|   \033[0m \033[34m| |\\/| | |  | | |  | | |      | | | . ` |\033[0m\n");
printf("\t\033[31m | |__| | |____| |__| | | |__| | |____  \033[0m \033[34m| |  | | |__| | |__| | |____ _| |_| |\\  |\033[0m\n");
printf("\t\033[31m  \\____/|______|\\____/  |_____/|______|\033[0m \033[34m |_|  |_|\\____/ \\____/|______|_____|_| \\_|\033[0m\n");
}


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
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 21; j++) {
            int colorier = 0; // Indicateur de couleur

            //  Vérifier si cette position est encore occupée par un joueur
            for (int k = 0; k < taille_liste; k++) {
                if (liste[k].ligne == i && liste[k].colonne == j) {
                    if (liste[k].joueur == 1) {
                        printf(BG_RED "%c " RESET, T[i][j]);
                    } else if (liste[k].joueur == 2) {
                        printf(BG_BLUE "%c " RESET, T[i][j]);
                    }
                    colorier = 1;
                    break;
                }
            }

            // Si la position n'est pas occupée, afficher normalement
            if (!colorier) {
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
    for (int i = 0; i < taille_liste; i++) {
        if (liste[i].position == pos) {
            return 1; // Position dejà occupee
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

 // fct dtermine si une position appartient à un joueur
int pion_joueur(int joueur,char pos){

        for(int i=0;i<taille_liste;i++){
            if(liste[i].position==pos&&liste[i].joueur==joueur)
                return 1 ;
        }
        return 0;
}


int est_moulin(char T[15][21], char pos, int joueur) {
    int moulin_count = 0;

    // Parcourir toutes les positions du tableau "ensemble"
    for (int b = 0; b < 24; b++) {
        if (ensemble[b].position == pos) {
            // Verifier les deux configurations de moulin
            int condition1 = pion_joueur(joueur, ensemble[b].moulin[0][0]) && pion_joueur(joueur, ensemble[b].moulin[0][1]);
            int condition2 = pion_joueur(joueur, ensemble[b].moulin[1][0]) && pion_joueur(joueur, ensemble[b].moulin[1][1]);

            // Si une configuration est complète, on a un moulin
            if (condition1 || condition2) {
                moulin_count++;
            }
        }
    }

    return moulin_count;
}


int capture_pion(char T[15][21], char pos,int joueur ) {
    int taille = taille_liste;
    // Verifier la validite de la position
    if (!pos_est_valide(T, pos)) {
        return -2; // Position non valide
    }

    for (int i = 0; i < taille_liste; i++) {
        if ((liste[i].position == pos)&&(liste[i].joueur != joueur)) {

                if (est_moulin( T, pos, liste[i].joueur)==1) {
                    return -1; // Pion protege par un moulin
                }
                else {
                     return 1;// le pion est capture
                }
            }


        }
        return -2; // pion non valide

    }


void supprimer_choix(char T[15][21], char position) {
    for (int i = 0; i < taille_liste; i++) {
        if (liste[i].position == position) {
            int ligne = liste[i].ligne;
            int colonne = liste[i].colonne;

            // Restaurer la lettre originale dans la matrice T
            for (int j = 0; j < 24; j++) {
                if (dict[j].alphabet == position) {
                    T[ligne][colonne] = dict[j].alphabet; // Remet la lettre d'origine
                    break;
                }
            }

            // Supprimer la position de la liste en decalant les elements
            for (int j = i; j < taille_liste - 1; j++) {
                liste[j] = liste[j + 1];
            }

            taille_liste--;


            return;

        }
    }

}


int deplacer(char T[15][21], char pos, char pos1, int joueur) {
    // Verifier que 'pos' appartient au joueur actuel
    if (!pion_joueur(joueur, pos)) {
        return -1; // La position de depart ne vous appartient pas
    }

    // Verifier que 'pos1' est valide et adjacente
    if (pos_est_valide(T, pos1) || !est_adj(pos, pos1)) {
        return -2; // La nouvelle position n'est pas valide ou non adjacente
    }

    // Supprimer l'ancien pion
    supprimer_choix(T, pos);

    // Ajouter le pion dans la nouvelle position
    for (int i = 0; i < 24; i++) {
        if (dict[i].alphabet == pos1) {
            liste[taille_liste].joueur = joueur;
            liste[taille_liste].position = pos1;
            liste[taille_liste].ligne = dict[i].ligne;
            liste[taille_liste].colonne = dict[i].colonne;
            taille_liste++;
            T[dict[i].ligne][dict[i].colonne] = pos1; // Mettre à jour la grille


            return 1; // Deplacement reussi
        }
    }

    return -3; // Erreur inattendue
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

//fct qui renvoie le nbr de pions restant
int nbr_pion(int joueur ) {
    int nbr=0;
    for (int i=0;i<taille_liste;i++){
        if(liste[i].joueur==joueur)
            nbr++;
    }
    return nbr;
}


void placer_pion(char T[15][21],char pos,int joueur){
    for (int i = 0; i < 24; i++) {
        if (dict[i].alphabet == pos) {
            liste[taille_liste].joueur = joueur;
            liste[taille_liste].position = pos;
            liste[taille_liste].ligne = dict[i].ligne;
            liste[taille_liste].colonne = dict[i].colonne;
            taille_liste++;
            T[dict[i].ligne][dict[i].colonne] = pos; // Mettre à jour la grille



}
    }
    }

//fct qui determine si une position est bloque
int position_bloquee(char T[15][21],char pos) {
    // Trouver la position dans la liste des adjacences
    for (int i = 0; i < 24; i++) {
        if (list[i].position == pos) {
            // Verifier si au moins une position adjacente est libre
            for (int j = 0; list[i].adjacents[j] != '\0'; j++) {
                if (!pos_est_valide(T, list[i].adjacents[j])) {
                    return 0; // Il y a au moins une case adjacente libre => pas bloque
                }
            }
            return 1; // Aucune case adjacente libre => bloque
        }
    }
    return -1; // Position non trouvee (erreur)
}

//fct qui determine si le spositions d'un joueur sont tous bloquees
int positions_bloquees(int joueur) {
    for (int i = 0; i < taille_liste; i++) {
        if (liste[i].joueur == joueur) {
            // Parcourir les positions adjacentes
            for (int j = 0; j < 24; j++) {
                if (list[j].position == liste[i].position) {
                    // Verifier si une des positions adjacentes est libre
                    for (int k = 0; list[j].adjacents[k] != '\0'; k++) {
                        if (!pos_est_valide(NULL, list[j].adjacents[k])) {
                            return 0; // Au moins une position adjacente est libre
                        }
                    }
                }
            }
        }
    }
    return 1; // Toutes les positions sont bloquees
}


void afficher_defaite(int joueur,char prenom1[],char prenom2[], int raison) {
    // Definir la couleur du joueur
    const char* couleur = (joueur == 1) ? BG_RED : BG_BLUE;
    const char* reset = RESET;
    const char* joueur_nom = (joueur == 1) ? prenom1: prenom2;

    printf("\n\n\t\t\U0001F622\U0001F622 %s%s%s a perdu la partie \U0001F622\U0001F622\n\n", couleur, joueur_nom, reset);

    if (raison == 1) {
        // Defaite a cause du nombre de pions
        printf("\t\tRaison : Vous n'avez plus assez de pions pour continuer à jouer (moins de 3) \U0001F6AB\U0001F6AB.\n");
    } else if (raison == 2) {
        // Defaite a cause du blocage
        printf("\t\tRaison : Toutes vos positions sont bloquees, vous ne pouvez plus effectuer de mouvements \U0001F6E1\U0001F6E1.\n");
    }

    printf("\n\t\t\U0001F389\U0001F389 Felicitations à %s%s%s pour sa victoire \U0001F3C6\U0001F3C6!\n\n", couleur = (joueur == 1) ? BG_BLUE : BG_RED, (joueur == 1) ? prenom2 : prenom1, RESET);
}


// ########Fonctions Machine#########
char prenom1[10], prenom2[10];

//la machine choisit un pion pour le deplecer
char choix_deplacement(int niveau){
            char pos;
            int a=0;
            char liste_pos[9];
            if(niveau==1){
            for (int i = 0; i < taille_liste; i++){
                    if(liste[i].joueur==2&&position_bloquee(NULL,liste[i].position)==0){
                            liste_pos[a]=liste[i].position;
                            a++;
                    }

            }

            pos=liste_pos[rand() %a];
            return pos;



            }
}

//la machine choisit une position valide
char choix_placement(int niveau){
            char pos;
            char liste_pos[24];
            int a=0;
            if(niveau==1){
            for(int i=0;i<24;i++){
                if(!pos_est_valide(NULL,dict[i].alphabet)){
                    liste_pos[a]=dict[i].alphabet;
                    a++;
                }
            }
            pos=liste_pos[rand() %a];
            return pos;
            }
}

//la machine choisit une position adjacente
char choix_position_machine(char T[15][21],char pion, int niveau){

            char pos;
            char liste_adj[4];
            int a=0;
            if(niveau==1){
            for(int i=0;i<24;i++){
                if(list[i].position==pion)
                {   for(int j=0;list[i].adjacents[j]!='\0';j++)
                    if(!pos_est_valide(T,list[i].adjacents[j])){
                       liste_adj[a]=list[i].adjacents[j];
                       a++;
                       }
                }
            }
            pos=liste_adj[rand() %a];

            }
}

//la machine choisit un pion du joueur adverse pour le capturer
char capturaion_machine(char T[15][21],int niveau){
    char pions_adversess[10];
    char pos1;
    int a=0;
    if(niveau==1){
        if(pions_moulin(1)){
                for (int i = 0; i < taille_liste; i++){
                if(liste[i].joueur == 1){
                    pions_adversess[a]=liste[i].position;
                    a++;
     }
    }
   }
        else{ for (int i = 0; i < taille_liste; i++){
                if(liste[i].joueur == 1&&!est_moulin(T,liste[i].position,1)){
                    pions_adversess[a]=liste[i].position;
                    a++;
     }
    }
   }
        pos1=pions_adversess[rand() % a];

        return pos1;




}
}

//affiche celui qui va jouer
void joueurs(char T[15][21],int joueur,int niveau,char prenom1[],char prenom2[]){
        char j1[10],j2[10];
        char pos;
        strcpy(j1,BG_RED);
        strcpy(j2,BG_BLUE);
        system("cls");
        affichage(T);
        if(joueur==1){
            printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom1,RESET);
            scanf(" %c",&pos);
            while ((pos_est_valide(T, pos))||(!(pos >= 'A' && pos <= 'X'))){
                    system("cls");
                    affichage(T);
                    printf("\n\n\t\tPosition invalide!!!!!\n\n \t\tRessayez SVP \U0001F600!!!!!\n");
                    printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom1,RESET);
                    scanf(" %c",&pos);
                    }
                    }
        else{

            printf("\n\t\t\U0001F916 %s%s%s est en train de jouer... \n", BG_BLUE, prenom2, RESET);
            sleep(2);
            system("cls");
            affichage(T);
            pos=choix_placement(niveau);
            printf("\n\t\t\U0001F916 %s%s%s a choisi la position : %c\n", BG_BLUE, prenom2, RESET,pos);
            sleep(2);

        }
        placer_pion(T,pos,joueur);
        system("cls");
        affichage(T);
        if(est_moulin(T,pos,1)&&pion_joueur(1,pos)){
                    printf("\n\t\tVous avez forme un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                    char pos1;
                    int result;

                    do {


                    scanf(" %c", &pos1);

                    result = capture_pion(T, pos1,1); // Appeler capture_pion une seule fois
                       system("cls");
                       affichage(T);
                        if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == -1&&!pions_moulin(2)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion capturable ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        }



                    } while (result != 1&&(result != -1||!pions_moulin(2)));  // Repeter tant que la capture n'a pas reussi

                    system("cls");
                    supprimer_choix(T,pos1);   // Supprimer le pion capture
                    affichage(T);
                    printf("\n\t\tPion capture \U0001F64C\n");
                }
                if(est_moulin(T,pos,2)&&pion_joueur(2,pos)){
                    char pos3;
                    printf("\n\t\t%sLA machine%s a  forme un moulin \U0001F3AF!!!\n\t\tcapturation du pion du joueur %sadverse%s \U0001F464 ...",j2, RESET, j1, RESET);
                    sleep(3);
                    system("cls");
                    affichage(T);
                    pos3=capturaion_machine(T,niveau);
                    supprimer_choix(T, pos3);
                    system("cls");
                    affichage(T);
                    printf("\n\t\t\U0001F916 %sLa machine%s a capturé le pion %c.\n",BG_BLUE,RESET,pos3);
                    sleep(3);


                            }


        }

// phase de placement du  éme mode 1:niveau facile 2:niveau moyen 3:niveau difficile
void palcement_phase(char T[15][21],int niveau,char prenom1[],char prenom2[]){
        if(niveau==1){
        joueur= rand() % 2;
        while(count<18){
        joueur = (joueur == 1) ? 2 : 1;
        joueurs(T,joueur,niveau,prenom1,prenom2);
        count++;

        }}
}

//phase de deplacemement
void deplacement_phase(char T[15][21], int niveau, char prenom1[], char prenom2[]) {
    printf("\n\t\t\t Phase de déplacement... ");
    sleep(3);
    joueur = (joueur == 1) ? 2 : 1;

    while ((nbr_pion(1) > 2 && nbr_pion(2) > 2) && (!positions_bloquees(1)) && (!positions_bloquees(2))) {
        system("cls");
        affichage(T);

        char pion, pos2,pion1;

        if (joueur == 1) {
      //phase de vol
                if(nbr_pion(1)==3&&chance1==0){

                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Il ne vous reste que trois pions !\u26A0",BG_RED,prenom1,RESET);
                            printf("\n\t\t\U0001F54AVous entrez en *phase de vol* !\U0001F54A");
                            printf("\n\t\tVous pouvez placer un pion à n'importe quelle position valide.");
                            printf("\n\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                           scanf(" %c",&pion1);
                            while(pos_est_valide(T, pion1)){
                                system("cls");
                                affichage(T);
                                printf("\n\t\t \U0001F464 %s%s%s \U0001F464 la position %c est occupee .Ressayez!!",BG_RED,prenom1,RESET);
                                printf("\n\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                                scanf(" %c",&pion1);
                            }
                            placer_pion(T,pion1,1);


                        chance1++;

                                    }
                    system("cls"); // Effacer l'ecran pour une meilleure lisibilite
                    affichage(T); // Afficher l'etat actuel du plateau

            printf("\n\t\t\U0001F464 %s%s%s \U0001F464 choisissez un pion à déplacer \U0001F3B2 : ", BG_RED, prenom1, RESET);
            scanf(" %c", &pion);

            while (!pion_joueur(1, pion) || position_bloquee(T, pion)) {
                system("cls");
                affichage(T);
                printf("\n\t\tPion invalide ou bloqué ! Réessayez.");
                printf("\n\t\t\U0001F464 %s%s%s \U0001F464 choisissez un pion à déplacer \U0001F3B2 : ", BG_RED, prenom1, RESET);
                scanf(" %c", &pion);
            }

            printf("\n\t\tNouvelle position pour déplacer le pion '%c' : ", pion);
            scanf(" %c", &pos2);


            while (pos_est_valide(T, pos2) || !est_adj(pion, pos2)) {
                system("cls");
                affichage(T);
                printf("\n\t\tPosition invalide ou non adjacente. Réessayez !");
                printf("\n\t\tNouvelle position pour déplacer le pion '%c' : ", pion);
                scanf(" %c", &pos2);
            }

            // Déplacer le pion
            deplacer(T, pion, pos2, 1);
            system("cls");
            affichage(T);


            if (est_moulin(T, pos2, 1)||est_moulin(T,pion1, 1) == 1) {
                printf("\n\t\tVous avez formé un moulin \U0001F3AF !!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :",BG_BLUE, RESET);
                char pos1;
                int result;
                do {
                    scanf(" %c", &pos1);
                    result = capture_pion(T, pos1, 1);
                    system("cls");
                    affichage(T);

                if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :",BG_BLUE, RESET);
                    } else if (result == -1&&!pions_moulin(2)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", BG_BLUE, RESET);
                    } else if (result == 0) {
                            printf("\n\t\tAucun pion  ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", BG_BLUE, RESET);
                    }
                } while (result != 1&&(result != -1||!pions_moulin(2)));

                system("cls");
                supprimer_choix(T, pos1);
                affichage(T);
                printf("\n\t\tPion capturé \U0001F64C\n");
            }

            // Passer au tour de la machine
            joueur = 2;
        }

        else {

                //phase de vol
                if(nbr_pion(2)==3&&chance2==0){
                    char pos;
                    printf("\n\t\t\U0001F54A%s La machine%s entre en *phase de vol* !\U0001F54A",BG_BLUE,RESET);
                    sleep(3);
                    printf("\n\n\t\t\U0001F916%s La machine%s est en train de jouer...",BG_BLUE,RESET);
                    sleep(2);
                    system("cls");
                    affichage(T);
                    pos=choix_placement(niveau);
                    placer_pion(T,pos,joueur);
                    system("cls");
                    affichage(T);
                    printf("\n\n\t\t\U0001F916 %s%s%s a choisi la position : %c\n", BG_BLUE, prenom2, RESET,pos);
                    sleep(3);
                    system("cls");
                    affichage(T);
                    printf("\n\t\t\U0001F916 %sLa machine%s est en train de jouer...",BG_BLUE,RESET);
                    chance2++;
                    sleep(3);

                    }

            char pion_machine, pos2_machine;


                pion_machine = choix_deplacement(niveau);

            // Sélectionner une position adjacente libre

            pos2_machine = choix_position_machine(T,pion_machine,niveau);
            system("cls");
            affichage(T);
            printf("\n\t\t\U0001F916 %sLa machine%s a déplacé le pion '%c' vers '%c'.",BG_BLUE,RESET, pion_machine, pos2_machine);
            sleep(2);
            deplacer(T, pion_machine, pos2_machine, 2);
            system("cls");
            affichage(T);
            printf("\n\t\t\U0001F916 %sLa machine%s a déplacé le pion '%c' vers '%c'.",BG_BLUE,RESET, pion_machine, pos2_machine);
            sleep(3);

            // Vérifier si la machine a formé un moulin
            if (est_moulin(T, pos2_machine, 2)||est_moulin(T,pion,2) == 1) {
                    char pos3;
                printf("\n\n\t\t\U0001F916 %sLa machine%s a formé un moulin ! Elle capture un pion...",BG_BLUE,RESET);
                sleep(3);
                pos3=capturaion_machine(T,niveau);
                    supprimer_choix(T, pos3);
                    system("cls");
                    affichage(T);
                    printf("\n\t\t\U0001F916 %sLa machine%s a capturé le pion %c.\n",BG_BLUE,RESET,pos3);
                    sleep(3);
            }

            // Passer au tour du joueur
            joueur = 1;
        }
    }
}

// partie AI avancee

void sauvegarder_coup(char grille[15][21], char move, int joueur) {
    char command[1024];
    sprintf(command, "python ml_ai.py %d", joueur);  // Ajouter le joueur (1 ou 2)

    // Ajouter l'état du plateau (convertir en une ligne de 24 valeurs)
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 21; j++) {
            char temp[10];
            sprintf(temp, " %d", grille[i][j]);  // Convertir chaque valeur en texte
            strcat(command, temp);
        }
    }

    // Ajouter le coup joué (lettre)
    char move_str[5];
    sprintf(move_str, " %c", move);
    strcat(command, move_str);

    // Exécuter la commande
    system(command);
}


char obtenir_coup_ia(int board[24]) {
    char command[512];
    sprintf(command, "%s", PYTHON_SCRIPT);

    for (int i = 0; i < 24; i++) {
        char temp[10];
        sprintf(temp, " %d", board[i]);
        strcat(command, temp);
    }

    FILE *fp = popen(command, "r");
    if (fp == NULL) {

        return 'X';  // Coup par défaut en cas d'erreur
    }

    char best_move;
    fscanf(fp, " %c", &best_move);
    pclose(fp);

    return best_move;
}


char obtenir_coup_iadql(int board[24]) {
    char command[512];
    sprintf(command, "%s", PYTHON_SCRIPTT);

    for (int i = 0; i < 24; i++) {
        char temp[10];
        sprintf(temp, " %d", board[i]);
        strcat(command, temp);
    }

    FILE *fp = popen(command, "r");
    if (fp == NULL) {

        return 'X';  // Coup par défaut en cas d'erreur
    }

    char best_move;
    fscanf(fp, " %c", &best_move);
    pclose(fp);

    return best_move;
}


void traduc_grille_board(){
            int board[24];
            for(int i=0;i<24;i++){
                for(int j=0;j<taille_liste;j++){
                    if(dict[i].alphabet==liste[j].position){
                        board[i]=joueur;
                    }
                    else{board[i]=0;}
                }
            }

}
