#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    int choix;
    int x;
    char y;
    char j1[20],j2[20];
    joueur = 1;
    grille(T);
    start:
    system("chcp 65001 > nul");
    printf("\t                     ~~~~~~~~~~ \033[1;4mJEU DE MOULIN\033[0m ~~~~~~~~~~ \n\n");
    printf("\t        \033[1;4mMENU:\033[0m\n\n");
    printf("\t        1- JOUER\n\n");
    printf("\t        2- REGLES DU JEU\n\n");
    printf("\t        3- QUITTER LE JEU\n\n");

    scanf("%d",&x);
    system("cls");
    switch(x){
        case 1:
            start1:
            printf("    \U0001F3AE\U0001F3AE  Veuillez selectionner votre mode de jeu  \U0001F3AE\U0001F3AE \n\n");
            printf("        mode A Joueur contre Joueur :  \U0001F464 vs \U0001F464\n\n");
            printf("        mode B Joueur contre Machine : \U0001F464 vs \U0001F916\n\n");
            scanf(" %c",&y);
            system("cls");
            switch(y){
                case 'A':
                    do {system("cls");
                    printf("\t\tEntrez le  prénom du premier joueur  : ");
                    scanf("%49s", prenom1);
                    printf("\t\tEntrez le  prénom du deuxième joueur : ");
                    scanf("%49s", prenom2);
                    choix = rand() % 2;

                    system("cls");
                    affichage(T);
                    if (choix == 0) {
                        printf("Le joueur qui va commencer est : %s\n", prenom1);
                    }
                    else {
                        printf("Le joueur qui va commencer est : %s\n", prenom2);
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
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",j2,prenom2,RESET);
                    }
                    scanf(" %c", &pos);
                    }

                system("cls");
                placer(T, pos);
                if (est_moulin(T, pos, joueur) == 1) {
                    printf("\n\t\tVous avez formé un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                    if(pions_moulin(1)){printf("\n\t\tTous les pions du joueur adverse sont protégés par des moulins \U0001F6E1 \U0001F6E1.\n");}
                    else {

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
                        } else if (result == -1) {
                            printf("\n\t\tPion protégé par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion capturable ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j1, RESET);
                        }



                    } while (result != 1);  // Répéter tant que la capture n'a pas réussi

                    system("cls");
                    supprimer_choix(pos1);   // Supprimer le pion capturé
                    affichage(T);
                    printf("\n\t\tPion capturé \U0001F64C\n");
                }
                }
                }




                else{
                    joueur = 1;
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom2,RESET);
                    }
                    scanf(" %c",&pos);
                    system("cls");
                while ((pos_est_valide(T, pos))||(!(pos >= 'A' && pos <= 'X'))){
                    system("cls");
                    affichage(T);

                    printf("\n\n\t\tPosition invalide!!!!!\n\n \t\t Ressayez SVP \U0001F600!!!!!\n");
                    if (choix == 0) {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom1,RESET);
                    }
                    else {
                        printf("\n\t\t\U0001F464 %s%s%s \U0001F464 Choisissez une position \U0001F3B2 : ",BG_RED,prenom2,RESET);
                    }
                    scanf(" %c", &pos);
                    }

                    system("cls");
                    placer(T, pos);


                    if (est_moulin(T, pos, joueur) == 1) {
                    printf("\n\t\tVous avez formé un moulin \U0001F3AF!!!\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                    if(pions_moulin(2)){printf("\n\t\tTous les pions du joueur adverse sont protégés par des moulins\U0001F6E1\U0001F6E1.\n");}
                    else {
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
                        } else if (result == -1) {
                            printf("\n\t\tPion protégé par un moulin \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        } else if (result == 0) {
                            printf("\n\t\tAucun pion  ici \u274C\u274C\u274C!!!\n\t\tVeuillez ressayer SVP.");
                            printf("\n\t\tVeuillez capturer un pion du joueur %sadverse%s \U0001F464 :", j2, RESET);
                        }



                    } while (result != 1);  // Répéter tant que la capture n'a pas réussi

                    system("cls");
                    supprimer_choix(pos1);   // Supprimer le pion capturé
                    affichage(T);
                    printf("\n\t\tPion capturé \U0001F64C\n");
                }
            }
        }
    }
//                                // phase de deplacement
//                while (nbr_pion(1) > 2 && nbr_pion(2) > 2) {
//                    system("cls"); // Effacer l'écran pour une meilleure lisibilité
//                    affichage(T);  // Afficher l'état actuel du plateau
//
//                    // Changer de joueur
//                    if (joueur == 1) {
//                        joueur = 2;
//                    } else {
//                        joueur = 1;
//                    }
//
//                    printf("\nJoueur %d, veuillez choisir un pion à déplacer.\n", joueur);
//
//                    char pos, pos1;
//
//                    // Demander au joueur de choisir une position à déplacer
//                    printf("Position du pion à déplacer : ");
//                    scanf(" %c", &pos);
//
//                    // Vérifier que la position appartient au joueur et est valide
//                    while (!pion_joueur(joueur, pos)) {
//                        printf("Cette position ne vous appartient pas ou est invalide. Réessayez : ");
//                        scanf(" %c", &pos);
//                    }
//
//                    // Demander la nouvelle position
//                    printf("Nouvelle position pour déplacer le pion : ");
//                    scanf(" %c", &pos1);
//
//                    // Vérifier que la nouvelle position est valide et adjacente
//                    while (pos_est_valide(T, pos1) || !est_adj(pos, pos1)) {
//                        printf("Cette position est invalide ou non adjacente. Réessayez : ");
//                        scanf(" %c", &pos1);
//                    }
//
//                    // Déplacer le pion
//                    if (deplacer(T, pos, pos1) == 0) {
//                        printf("Le pion a été déplacé avec succès.\n");
//                    } else {
//                        printf("Erreur lors du déplacement. Réessayez.\n");
//                        continue; // Recommencer le tour si le déplacement échoue
//                    }
//
//                    system("cls");
//                    affichage(T);
//
//                    // Vérifier si un moulin a été formé après le déplacement
//                    if (est_moulin(T, pos1, joueur)) {
//                        printf("\nBravo, vous avez formé un moulin ! Vous pouvez capturer un pion adverse.\n");
//
//                        char pos_capture;
//                        int result;
//
//                        // Répéter jusqu'à ce qu'un pion valide soit capturé
//                        do {
//                            printf("Choisissez une position à capturer : ");
//                            scanf(" %c", &pos_capture);
//
//                            result = capture_pion(T, pos_capture, joueur);
//
//                            if (result == -1) {
//                                printf("Ce pion est protégé par un moulin. Réessayez.\n");
//                            } else if (result == -2) {
//                                printf("Position invalide. Réessayez.\n");
//                            }
//                        } while (result != 1);
//
//                        printf("Pion capturé avec succès !\n");
//                        supprimer_choix(pos_capture); // Supprimer le pion capturé
//                        system("cls");
//                        affichage(T);
//                    }
//                }

                    break;
                case 'B':
                    affichage(T);
                    printf("\nChoisissez une position : ");
                    scanf(" %c",&pos);
                    placer(T,pos);


                    break;
                default:
                    printf("   veuillez respecter le MENU!!!!\n\n   Ressayer SVP \U0001F600!!!!!\n\n");
                    goto start1;
                    break;
                    }
            break;
        case 2:
            printf("                    ~~~~~ \033[1;4mRegles du jeu du moulin\033[0m ~~~~~ \n\n");
            printf("\033[1;4mPour jouer au jeu du moulin, il vous faut :\033[0m\n\n-Le plateau du jeu\n-18 pions (9 pions de couleurs differentes)\n-Etre 2 joueurs (joueur && joueur /joueur && machine)\n\n");
            printf("\033[1;4mComment jouer une partie de jeu du moulin ?\033[0m\n\nLe jeu commence avec le plateau vide. À tour de rôle, chaque joueur place un de ses neuf pions  \nsur n’importe quel point libre du tableau. Pendant cette phase, il est strictement interdit de \n deplacer les pions deja places sur le tableau.\n\nUne fois que tous les pions ont ete places sur le tableau, chaque joueur à tour de role deplace \n l’un de ses pions vers un point adjacent libre, en suivant la ligne qui relie le point d’origine \n au point de destination. Si un joueur parvient à former un moulin, c’est-a-dire une rangee de \n trois pions de sa couleur alignes sur les trois points d’une même ligne, il est autorise à capturer\n un pion de son adversaire. Le pion capture est retire du tableau et ne peut plus etre joue.\n\nChaque fois qu’un moulin est complete, une prise est obligatoire, meme si le moulin a deja ete \n realise precedemment ou s’il est à nouveau forme par un pion revenant a un point qu’il occupait dans \n un moulin precedent. Le joueur effectuant la prise a la liberte de choisir parmi les pions \n de l’adversaire qui ne font pas partie d’un moulin. Si tous les pions de l’adversaire forment \n des moulins, le joueur qui effectue la prise peut choisir n’importe lequel d’entre eux.\n\nDès qu’un joueur n’a plus que trois pions sur le tableau, cela resultant de six prises subies, \n il peut deplacer ses pions librement vers n’importe quel point du plateau, sans etre restreint aux points \n adjacents uniquement.\n\n");
            printf("\033[1;4mComment gagner une partie de jeu du moulin?\033[0m\n\nDans le jeu du Moulin, la victoire est determinee par deux scenarios possibles :\n\n\033[1mVictoire par Prises :\033[0m Un joueur remporte la partie lorsqu’il a reussi à effectuer 7 prises, \n laissant ainsi son adversaire avec seulement deux pions et incapable de former de nouveaux moulins. C’est \n une strategie habile qui necessite de capturer les pièces de l’adversaire tout en maintenant \n la possibilité de former des moulins.\n\n\033[1mVictoire par Blocage :\033[0m L’autre moyen de gagner est lorsque l’adversaire se retrouve dans une \n situation où il est totalement bloque et incapable d’effectuer le moindre mouvement avec ses pieces restantes.\n Cela signifie que toutes ses pieces sont bloquees par les votres, le forçant ainsi à abandonner la partie.\nCependant, il existe des situations où la partie se termine de manière nulle. Cela se produit\n dans les cas suivants :\n\n\033[1mNulle par Stagnation :\033[0m Si les deux joueurs effectuent 50 mouvements sans reussir à realiser \n aucune prise, la partie se termine sur un match nul. Cela reflete une impasse strategique où les deux adversaires \n se neutralisent mutuellement.\n\n\033[1mNulle par Repetition :\033[0m Une autre situation de match nul survient lorsque la position des pions \n est repetee trois fois sur le tableau. Cela indique que le jeu a atteint un point de repetition strategique, où \n les memes positions se repetent sans qu’aucun joueur ne puisse obtenir l’avantage.\n");
            goto start;
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("   veuillez respecter le MENU!!!!\n\n   Ressayer SVP \U0001F600\U0001F600\U0001F600!!!!!\n\n");
            goto start;
            break;

    }

}

