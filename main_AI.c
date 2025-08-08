#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PYTHON_SCRIPT "python ml_ai.py"
#define PYTHON_SCRIPTT "python mill_ai.py"
#include "prototype.h"

#define BG_RED "\033[41m"
#define BG_BLUE "\033[44m"
#define RESET "\033[0m"
static int  joueur;
static int taille_liste;//à revoir
int main()
{
    srand(time(NULL));
    char T[15][21], pos;
    char prenom1[50], prenom2[50];
    static char posM;
    int choix;
    static int chance1=0,chance2=0;;
    int x, l;
    char y;
    char j1[20],j2[20];
    joueur = 1;
    grille(T);
    system("chcp 65001 > nul");
    titre();
        start:

    printf("\n\033[32m");
    printf("\t\t\t\t --------------------------\n");
    printf("\t\t\t\t|         1. JOUER         |\n");
    printf("\t\t\t\t --------------------------\n");
    printf("\033[0m");

    printf("\n\033[32m");
    printf("\t\t\t\t --------------------------\n");
    printf("\t\t\t\t|     2. Regles du jeu     |\n");
    printf("\t\t\t\t --------------------------\n");
    printf("\033[0m");

    printf("\n\033[31m");
    printf("\t\t\t\t --------------------------\n");
    printf("\t\t\t\t|        3. Quitter        |\n");
    printf("\t\t\t\t --------------------------\n");
    printf("\033[0m");

    scanf("%d",&x);
    system("cls");
    switch(x){
        case 1:
            system("cls");
            titre();
            printf("\n\n\n\n\n\t\t\t\t\tLoading.");
            sleep(1);
            system("cls");
            titre();
            printf("\n\n\n\n\n\t\t\t\t\tLoading..");
            sleep(1);
            system("cls");
            titre();
            printf("\n\n\n\n\n\t\t\t\t\tLoading...");
            sleep(1);
            system("cls");
            titre();


            start1:
            printf("\n\t\t\t   \U0001F3AE\U0001F3AE  Veuillez selectionner votre mode de jeu  \U0001F3AE\U0001F3AE \n\n");

    printf("\n\033[32m");
    printf("\t\t       --------------------------------------------------------------\n");
    printf("\t\t      |              mode A Joueur contre Joueur :  \U0001F464 vs \U0001F464         |\n");
    printf("\t\t      |                                                              |\n");
    printf("\t\t       --------------------------------------------------------------\n");
    printf("\033[0m");

    printf("\n\033[31m");
    printf("\t\t       --------------------------------------------------------------\n");
    printf("\t\t      |              mode B Joueur contre Machine : \U0001F464 vs \U0001F916         |\n");
    printf("\t\t      |                                                              |\n");
    printf("\t\t       --------------------------------------------------------------\n");
    printf("\033[0m");

            scanf(" %c",&y);
            system("cls");
            switch(y){
                case 'A':
                    titre();
                    printf("\n\n\t\t\tEntrez le prenom du premier joueur  : ");
                    scanf("%s", prenom1);
                    printf("\n\t\t\tEntrez le prenom du deuxieme joueur : ");
                    scanf("%s", prenom2);
                    choix = rand() % 2;
                    do {

                    system("cls");
                    affichage(T);
                    if (choix == 0) {
                        printf("\n\t\tLe joueur qui va commencer est : %s\n", prenom1);
                    }
                    else {
                        printf("\n\t\tLe joueur qui va commencer est : %s\n", prenom2);
                    }


                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom2,RESET);
                    }

                    scanf(" %c",&pos);
                    system("cls");}while((pos_est_valide(T, pos))||(!(pos >= 'A' && pos <= 'X')));
                    placer(T, pos,joueur);
                    strcpy(j1,BG_RED);
                    strcpy(j2,BG_BLUE);

                for (int i=0;i<17;i++){
                    if(joueur == 1){
                    joueur = 2;
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom1,RESET);
                    }

                    scanf(" %c",&pos);
                    system("cls");

                while ((pos_est_valide(T, pos))||(!(pos >= 'A' && pos <= 'X'))){
                    joueur = 2;
                    system("cls");
                    affichage(T);

                    printf("\n\n\t\tPosition invalide!!!!!\n\n \t\tRessayez SVP \U0001F600!!!!!\n");
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom1,RESET);
                    }
                    scanf(" %c", &pos);
                    }

                system("cls");
                placer(T, pos);

                if (est_moulin(T, pos, joueur) == 1) {
                    printf("\n\t\tVous avez forme un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);


                    char pos1;
                    int result;

                    do {


                        scanf(" %c", &pos1);

                        result = capture_pion(T, pos1,joueur); // Appeler capture_pion une seule fois
                       system("cls");
                       affichage(T);
                        if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        } else if (result == -1&&!pions_moulin(1)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion capturable ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        }



                    } while (result != 1&&(result != -1||!pions_moulin(1)));  // Repeter tant que la capture n'a pas reussi

                    system("cls");
                    supprimer_choix(T,pos1);
                       // Supprimer le pion capture
                    affichage(T);
                    printf("\n\t\tPion capture \U0001F64C\n");

                }
                }




                else{
                    joueur = 1;
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom2,RESET);
                    }
                    scanf(" %c",&pos);
                    system("cls");
                while ((pos_est_valide(T, pos))||(!(pos >= 'A' && pos <= 'X'))){
                    system("cls");
                    affichage(T);

                    printf("\n\n\t\tPosition invalide!!!!!\n\n \t\t Ressayez SVP \U0001F600!!!!!\n");
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j1,prenom2,RESET);
                    }
                    scanf(" %c", &pos);
                    }

                    system("cls");
                    placer(T, pos);


                    if (est_moulin(T, pos, joueur) == 1) {
                    printf("\n\t\tVous avez forme un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                    char pos1;
                    int result;

                    do {

                        scanf(" %c", &pos1);
                        result = capture_pion(T, pos1,joueur); // Appeler capture_pion une seule fois
                       system("cls");
                       affichage(T);
                        if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == -1&&!pions_moulin(2)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion  ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        }



                    } while (result != 1&&(result != -1||!pions_moulin(2)));  // Repeter tant que la capture n'a pas reussi

                    system("cls");
                    supprimer_choix(T,pos1);   // Supprimer le pion capture

                    affichage(T);
                    printf("\n\t\tPion capture \U0001F64C\n");

            }
        }
    }





    // phase de deplacement
                printf("\n\t\t\t phase de deplacement ");
                while ((nbr_pion(1) > 2 && nbr_pion(2) > 2)&&(!positions_bloquees(1))&&(!positions_bloquees(2))) {
                    system("cls"); // Effacer l'ecran pour une meilleure lisibilite
                    affichage(T); // Afficher l'etat actuel du plateau
                    char pion;



                    // Changer de joueur
                    if(joueur == 1){
                    joueur = 2;
                           //phase de vol
                if(nbr_pion(joueur)==3&&chance2==0){

                        if (choix == 0) {
                            printf("\n\t\t\t\U0001F464 %s%s%s \U0001F464 Il ne vous reste que trois pions !\u26A0",j2,prenom2,RESET);
                            printf("\n\t\t\t\U0001F54AVous entrez en *phase de vol* !\U0001F54A");
                            printf("\n\t\t\tVous pouvez placer un pion à n'importe quelle position valide.");
                            printf("\n\t\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                           scanf(" %c",&pion);
                            while(pos_est_valide(T, pion)){
                                system("cls");
                                affichage(T);
                                printf("\n\t\t\t \U0001F464 %s%s%s \U0001F464 la position %c est occupee .Ressayez!!",j2,prenom2,RESET);
                                printf("\n\t\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                                scanf(" %c",&pion);
                            }
                            placer_pion(T,pion,joueur);

                        }
                        else {
                        printf("\n\t\t\t\U0001F464 %s%s%s \U0001F464 Il ne vous reste que trois pions !\u26A0",j2,prenom1,RESET);
                        printf("\n\t\t\t\U0001F54AVous entrez en *phase de vol* !\U0001F54A");
                        printf("\n\t\t\tVous pouvez placer un pion à n'importe quelle position valide.");
                        printf("\n\t\t\t\U0001F3AFVeuillez choisir une position \U0001F3AF: ");
                        scanf(" %c",&pion);
                            while(pos_est_valide(T, pion)){
                                system("cls");
                                affichage(T);
                                printf("\n\t\t\t\U0001F464 %s%s%s \U0001F464 la position %c est occupee .Ressayez!!",j2,prenom1,RESET);
                                printf("\n\t\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                                scanf(" %c",&pion);
                            }
                            placer_pion(T, pion,joueur);

                        }
                        chance2++;

                                    }
                    system("cls"); // Effacer l'ecran pour une meilleure lisibilite
                    affichage(T); // Afficher l'etat actuel du plateau
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer \U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer \U0001F3B2 : ",j2,prenom1,RESET);
                    }

                    char pos, pos2;

                    // Demander au joueur de choisir une position à deplacer
                    scanf(" %c", &pos);

                    // Verifier que la position appartient au joueur et est valide

                    while (!pion_joueur(joueur, pos)||position_bloquee(T,pos)) {
                    system("cls"); // Effacer l'ecran pour une meilleure lisibilite
                    affichage(T);  // Afficher l'etat actuel du plateau
                    if(position_bloquee(T,pos)==1&&pion_joueur(joueur, pos)){
                        printf("\n\t\tCette position est bloquee . Reessayez :");
                    }

                    else {
                    printf("\n\t\tCette position ne vous appartient pas ou est invalide. Reessayez : ");}
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer\U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    else {if(pion_joueur(1, pos)){
                        printf("\n\t\tCette position ne vous appartient pas. Reessayez : ");
                    }
                    else {
                    printf("\n\t\tCette position est invalide. Reessayez : ");}
                    }
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer\U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer\U0001F3B2 : ",j2,prenom1,RESET);
                    }

                    scanf(" %c", &pos);
                    }

                    // Demander la nouvelle position
                    printf("\n\t\tNouvelle position pour deplacer le pion '%c' : ",pos);
                    scanf(" %c",&pos2);

                    // Verifier que la nouvelle position est valide et adjacente
                    while (pos_est_valide(T, pos2) || !est_adj(pos, pos2)) {
                        system("cls");
                        affichage(T);
                        if (choix == 0) {
                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464  Cette position est invalide ou non adjacente. ",j2,prenom2,RESET);
                            printf("\n\t\tReessayez !! Nouvelle position pour deplacer le pion '%c' : ",pos);
                        }
                        else {
                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464  Cette position est invalide ou non adjacente. Reessayez : ",j2,prenom1,RESET);
                            printf("\n\t\tReessayez !! Nouvelle position pour deplacer le pion '%c' : ",pos);
                        }
                        scanf(" %c", &pos2);
                    }


                    // Deplacer le pion
                    if (deplacer(T,pos,pos2,joueur)) {
                        printf("\n\t\tLe pion a ete deplace avec succès.\n");
                    }else  {
                        printf("\n\t\tLa nouvelle position est invalide ou non adjacente. Reessayez : ");}

                    system("cls");
                    affichage(T);

                    // Verifier si un moulin a ete forme après le deplacement
                if (est_moulin(T, pos2, joueur) == 1||est_moulin(T,pion, joueur) == 1) {
                    printf("\n\t\tVous avez forme un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);


                    char pos1;
                    int result;

                    do {


                        scanf(" %c", &pos1);

                        result = capture_pion(T, pos1,joueur); // Appeler capture_pion une seule fois
                       system("cls");
                       affichage(T);
                        if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        } else if (result == -1&&!pions_moulin(1)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion capturable ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        }



                    } while (result != 1&&(result != -1||!pions_moulin(1)));  // Repeter tant que la capture n'a pas reussi

                    system("cls");
                    supprimer_choix(T,pos1);
                       // Supprimer le pion capture
                    affichage(T);
                    printf("\n\t\tPion capture \U0001F64C\n");

                }
                if(chance2==1){pion='\0';}
                }
                    else{
                    joueur = 1;
                                //phase de vol
                if(nbr_pion(joueur)==3&&chance1==0){

                        if (choix == 0) {
                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Il ne vous reste que trois pions !",j1,prenom1,RESET);
                            printf("\n\t\t\U0001F54AVous entrez en *phase de vol* !\U0001F54A");
                            printf("\n\t\tVous pouvez placer un pion à n'importe quelle position valide.");
                            printf("\n\t\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                           scanf(" %c",&pion);
                            while(pos_est_valide(T, pion)){
                                system("cls");
                                affichage(T);
                                printf("\n\t\t\U0001F464 %s%s%s \U0001F464 la position %c est occupee .Ressayez!!",j1,prenom1,RESET);
                                printf("\n\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                                scanf(" %c",&pion);
                            }
                            placer_pion(T,pion,joueur);
                        }
                        else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Il ne vous reste que trois pions !\u26A0",j1,prenom2,RESET);
                        printf("\n\t\t\U0001F54AVous entrez en *phase de vol* !\U0001F54A");
                        printf("\n\t\tVous pouvez placer un pion à n'importe quelle position valide.");
                        printf("\n\t\t\U0001F3AFVeuillez choisir une position \U0001F3AF: ");
                        scanf(" %c",&pion);
                            while(pos_est_valide(T, pion)){
                                system("cls");
                                affichage(T);
                                printf("\n\t\t\t\U0001F464 %s%s%s \U0001F464 la position %c est occupee .Ressayez!!",j1,prenom2,RESET);
                                printf("\n\t\t\t\U0001F3AFVeuillez choisir une position\U0001F3AF : ");
                                scanf(" %c",&pion);
                            }
                            placer_pion(T, pion,joueur);
                        }
                        chance1++;

                                    }
                    system("cls");
                    affichage(T);
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 veuillez choisir un pion à deplacer \U0001F3B2 : ",j1,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 veuillez choisir un pion à deplacer \U0001F3B2 : ",j1,prenom2,RESET);
                    }
                    char pos, pos2;

                    // Demander au joueur de choisir une position à deplacer
                    scanf(" %c", &pos);

                    // Verifier que la position appartient au joueur et est valide

                    while (!pion_joueur(joueur, pos)||position_bloquee(T,pos)) {
                    system("cls"); // Effacer l'ecran pour une meilleure lisibilite
                    affichage(T);  // Afficher l'etat actuel du plateau
                    if(position_bloquee(T,pos)==1&&pion_joueur(joueur, pos)){
                        printf("\n\t\tCette position est bloquee . Reessayez :");
                    }

                    else {if(pion_joueur(2, pos)){
                        printf("\n\t\tCette position ne vous appartient pas. Reessayez : ");
                    }

                    else {
                    printf("\n\t\tCette position est invalide. Reessayez : ");}
                    }
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer\U0001F3B2 : ",j1,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464  veuillez choisir un pion à deplacer\U0001F3B2 : ",j1,prenom2,RESET);
                    }

                    scanf(" %c", &pos);
                    }

                    // Demander la nouvelle position
                    printf("\n\t\tNouvelle position pour deplacer le pion '%c' :",pos);
                    scanf(" %c",&pos2);

                    // Verifier que la nouvelle position est valide et adjacente
                    while (pos_est_valide(T, pos2) || !est_adj(pos, pos2)) {
                        system("cls");
                        affichage(T);
                        if (choix == 0) {
                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464  Cette position est invalide ou non adjacente.  ",j1,prenom1,RESET);
                            printf("\n\t\tReessayez !! Nouvelle position pour deplacer le pion '%c' : ",pos);
                        }
                        else {
                            printf("\n\t\t\U0001F464 %s%s%s \U0001F464  Cette position est invalide ou non adjacente. ",j1,prenom2,RESET);
                            printf("\n\t\tReessayez !! Nouvelle position pour deplacer le pion '%c' : ",pos);
                        }
                        scanf(" %c", &pos2);
                    }
              // Deplacer le pion
                    if (deplacer(T,pos,pos2,joueur)) {
                        printf("\n\t\tLe pion a ete deplace avec succès.\n");
                    }else  {
                        printf("\n\t\tLa nouvelle position est invalide ou non adjacente. Reessayez : ");}


                    system("cls");
                    affichage(T);

                    if (est_moulin(T, pos2, joueur) == 1||est_moulin(T,pion, joueur) == 1) {
                    printf("\n\t\tVous avez forme un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);


                    char pos1;
                    int result;

                    do {

                        scanf(" %c", &pos1);
                        result = capture_pion(T, pos1,joueur); // Appeler capture_pion une seule fois
                       system("cls");
                       affichage(T);
                        if (result == -2) {
                            printf("\n\t\tLa position choisie est invalide \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == -1&&!pions_moulin(2)) {
                            printf("\n\t\tPion protege par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion  ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        }



                    } while (result != 1&&(result != -1||!pions_moulin(2)));  // Repeter tant que la capture n'a pas reussi

                    system("cls");
                    supprimer_choix(T,pos1);   // Supprimer le pion capture

                    affichage(T);
                    printf("\n\t\tPion capture \U0001F64C\n");
                }
                if(chance1==1){pion='\0';}

                }
                }
                for(int a=1;a<=2;a++){
                    if (nbr_pion(a) < 3) {
                        afficher_defaite(a,prenom1,prenom2,1);
                    }
                    if (positions_bloquees(a)) {
                        afficher_defaite(a,prenom1,prenom2,2);
                    }

                                    }

                    break;

//############################# JOUEUR VS MACHINE ###############################################//
                case 'B':


                    titre();
                    start2:
                    printf("\n\n\n\t\t\t        \U0001F3AE\U0001F3AEchoisir la difficulte\U0001F3AE\U0001F3AE ");
                        printf("\n\033[32m");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\t\t\t\t|        1. Normal\U0001F642       |\n");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\033[0m");

                        printf("\n\033[31m");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\t\t\t\t|         2. Hard\U0001F621        |\n");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\033[0m");

                        printf("\n\033[35m");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\t\t\t\t|       3. Insane\U0001F47F        |\n");
                        printf("\t\t\t\t --------------------------\n");
                        printf("\033[0m");

                    scanf("%d",&l);
                     switch(l){
                            case 1 :


                                //phase de placemeent
                            system("cls");
                            printf("\n\n\t\t\tEntrez votre prenom : ");
                            char prenom1[15],prenom2[15];
                            scanf("%s", prenom1);
                            strcpy(prenom2, "La machine");
                            palcement_phase(T,1,prenom1,prenom2);
                            deplacement_phase(T,1,prenom1,prenom2);
                            for(int a=1;a<=2;a++){
                            if (nbr_pion(a) < 3) {
                                afficher_defaite(a,prenom1,prenom2,1);
                            }
                            if (positions_bloquees(a)) {
                                afficher_defaite(a,prenom1,prenom2,2);
                            }

                                            }


                            break;




        //niveau 2
                            case 2 :
                            system("cls");
                            titre();
                            printf("\n\n\t\t\t   this version is not disponible yet, COMING SOON...");
                            goto start2;//à faire
                            break;
        //niveau 3
                            case 3 :
                            system("cls");
                            titre();
                            printf("\n\n\t\t\t   this version is not disponible yet, COMING SOON...");
                            goto start2;//à faire
                            break;

                            default:
                            system("cls");
                            printf("\n\n\\nt\t\t   veuillez respecter le MENU!!!!\n\n\t\t\t   Ressayer SVP \U0001F600!!!!!\n\n");
                            sleep(3);
                            system("cls");
                            titre();
                            goto start2;

                            break;
                            }
                        break;

                    default :
                    system("cls");
                    printf("\n\n\n\n\t\t\t  veuillez respecter le MENU!!!!\n\n\t\t\t   Ressayer SVP \U0001F600!!!!!\n\n");
                    sleep(3);
                    system("cls");

                    titre();
                    goto start1;
                    }
            break;
        case 2:
            titre();
            printf("\033[1;4m\nPour jouer au jeu du moulin, il vous faut :\033[0m\n\n-Le plateau du jeu\n-18 pions (9 pions de couleurs differentes)\n-Etre 2 joueurs (joueur && joueur /joueur && machine)\n\n");
            printf("\033[1;4mComment jouer une partie de jeu du moulin ?\033[0m\n\nLe jeu commence avec le plateau vide.  tour de rôle, chaque joueur place un de ses neuf pions  \nsur n’importe quel point libre du tableau. Pendant cette phase, il est strictement interdit de \n deplacer les pions deja places sur le tableau.\n\nUne fois que tous les pions ont ete places sur le tableau, chaque joueur à tour de role deplace \n l’un de ses pions vers un point adjacent libre, en suivant la ligne qui relie le point d’origine \n au point de destination. Si un joueur parvient à former un moulin, c’est-a-dire une rangee de \n trois pions de sa couleur alignes sur les trois points d’une même ligne, il est autorise à capturer\n un pion de son adversaire. Le pion capture est retire du tableau et ne peut plus etre joue.\n\nChaque fois qu’un moulin est complete, une prise est obligatoire, meme si le moulin a deja ete \n realise precedemment ou s’il est à nouveau forme par un pion revenant a un point qu’il occupait dans \n un moulin precedent. Le joueur effectuant la prise a la liberte de choisir parmi les pions \n de l’adversaire qui ne font pas partie d’un moulin. Si tous les pions de l’adversaire forment \n des moulins, le joueur qui effectue la prise peut choisir n’importe lequel d’entre eux.\n\nDès qu’un joueur n’a plus que trois pions sur le tableau, cela resultant de six prises subies, \n il peut deplacer ses pions librement vers n’importe quel point du plateau, sans etre restreint aux points \n adjacents uniquement.\n\n");
            printf("\033[1;4mComment gagner une partie de jeu du moulin?\033[0m\n\nDans le jeu du Moulin, la victoire est determinee par deux scenarios possibles :\n\n\033[1mVictoire par Prises :\033[0m Un joueur remporte la partie lorsqu’il a reussi à effectuer 7 prises, \n laissant ainsi son adversaire avec seulement deux pions et incapable de former de nouveaux moulins. C’est \n une strategie habile qui necessite de capturer les pièces de l’adversaire tout en maintenant \n la possibilite de former des moulins.\n\n\033[1mVictoire par Blocage :\033[0m L’autre moyen de gagner est lorsque l’adversaire se retrouve dans une \n situation où il est totalement bloque et incapable d’effectuer le moindre mouvement avec ses pieces restantes.\n Cela signifie que toutes ses pieces sont bloquees par les votres, le forçant ainsi à abandonner la partie.\nCependant, il existe des situations où la partie se termine de manière nulle. Cela se produit\n dans les cas suivants :\n\n\033[1mNulle par Stagnation :\033[0m Si les deux joueurs effectuent 50 mouvements sans reussir à realiser \n aucune prise, la partie se termine sur un match nul. Cela reflete une impasse strategique où les deux adversaires \n se neutralisent mutuellement.\n\n\033[1mNulle par Repetition :\033[0m Une autre situation de match nul survient lorsque la position des pions \n est repetee trois fois sur le tableau. Cela indique que le jeu a atteint un point de repetition strategique, où \n les memes positions se repetent sans qu’aucun joueur ne puisse obtenir l’avantage.\n");
            goto start;
            break;
        case 3:
            system("cls");
            titre();
            printf("\n\n\n\n\n\t\t\t\t\tShutting down...");
            sleep(3);
            system("exit");
            system("cls");
            break;
        default:
            printf("\n\n\n\t\t\t   veuillez respecter le MENU!!!!\n\n\t\t\t   Ressayer SVP \U0001F600\U0001F600\U0001F600!!!!!\n\n");
            sleep(3);
            system("cls");
            titre();
            goto start;

            break;

    }

}

