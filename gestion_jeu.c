#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gestion_cases.h"
#include "gestion_pions.h"
#include "gestion_joueurs.h"
#include "gestion_jeu.h"
#include "gestion_moulin.h"
#include "gestion_mouvements.h"
#include "gestion_placement.h"
#include "gestion_plateau.h"
#include "gestion_regles.h"
#include "gestion_texte.h"
#include "gestion_algorithme_AI.h"

extern Case plateau[8][3];

void menu()
{
    /* Cette fonction nous permet d'afficher le menu du jeu et le squelette */

    int choix_menu,jouer,j_vs_j,j_vs_m,regles;

    printf("************************************************************************************************************************");
    printf("************************************************ JEU DU MOULIN *********************************************************");
    printf("************************************************************************************************************************\n");
    retour_menu:
    printf("   * MENU *\n");
    printf("\t   1) JOUER\n\t   2) REGLES DU JEU\n\t   3) QUITTER LE JEU\n");
    printf("   > ");
    scanf("%d",&choix_menu);
    switch(choix_menu)
    {
    case 1:
        retour_jouer:
        printf("\t   1) Joueur vs Joueur\n\t   2) Joueur vs MACHINE\n\t   3) RETOUR\n");
        printf("   > ");
        scanf("%d",&jouer);
        switch(jouer)
        {
        case 1:
            niveau_j_vs_j:
            printf("\t   1) Reprendre le jeu\n\t   2) Nouveau jeu\n\t   3) RETOUR\n");
            printf("   > ");
            scanf("%d",&j_vs_j);
            switch(j_vs_j)
            {
            case 1:
                EffacerEcran();
                printf("_____OPTION PAS ENCORE DISPONIBLE_______");
                break;
            case 2:
                InitialiserPlateau();
                EffacerEcran();
                //AfficherPlateau();
                BoucleJeu();
                break;
            case 3:
                EffacerEcran();
                goto retour_jouer;
                break;
            default: printf("Mauvais choix, veillez reprendre !!\n"); EffacerEcran(); goto niveau_j_vs_j;
            }
            //system("PAUSE");
            break;
        case 2:
                niveau_j_vs_m:
            printf("Choisissez un niveau de jeu !\n");
            printf("\t   1) Facile\n\t   2) Moyen\n\t   3) Difficile\n\t   4) RETOUR\n");
            printf("   > ");
            scanf("%d",&j_vs_m);
            switch(j_vs_m)
            {
            case 1:
                InitialiserPlateau();
                EffacerEcran();
                //AfficherPlateau();
                BoucleJeuAI();
                break;
            case 2:
                InitialiserPlateau();
                EffacerEcran();
                AfficherPlateau();
                break;
            case 3:
                InitialiserPlateau();
                EffacerEcran();
                AfficherPlateau();
                break;
            case 4:
                EffacerEcran();
                goto retour_jouer;
            break;
            default: printf("Mauvais choix, veillez reprendre !!\n"); EffacerEcran(); goto niveau_j_vs_m;
            }
            //system("PAUSE");
            break;
        case 3:
            EffacerEcran();
            goto retour_menu;
            break;
        default: printf("Mauvais choix, veillez reprendre !!\n"); EffacerEcran(); goto retour_jouer;
        }
        break;
    case 2:
        regle();
        rule:
        printf("\t   Retour : \n\t\t   1) OUI\n\t\t   2) NON QUITTER LE JEU\n");
        printf("   > ");
        scanf("%d",&regles);
        switch(regles)
        {
        case 1:
            EffacerEcran();
            goto retour_menu;
            break;
        case 2:
            printf("Au revoir !!!\n");
            break;
        default: printf("Mauvais choix, veillez reprendre !!\n"); EffacerEcran(); goto rule;
        }
        break;
    case 3:
        printf("Au revoir !!!\n");
        //system("exit");
        break;
    default: printf("Mauvais choix, veillez reprendre !!\n"); EffacerEcran(); goto retour_menu;
    }
}


void EffacerEcran()
{
    #ifdef _WIN32
        system("cls");  // Pour Windows
    #else
        system("clear");  // Pour Linux/macOS
    #endif
}


void BoucleJeu()
{
    for(int i=0; i<8; i++)
        for(int j=0; j<3; j++)
            plateau[i][j].etat = non_protegee;

    int n;
    Joueur j1,j2;

    EffacerEcran();
    printf("Informations premier joueur :\n");
    j1 = CreatePlayer();

    EffacerEcran();
    printf("Informations deuxieme joueur :\n");
    j2 = CreatePlayer();
    EffacerEcran();

    n = random_int() ;

    // Première phase : placement

    AfficherPlateau();
    for(int i=1; i<=8; i++)
    {
        if(n == j1.id){

            TourPlacement(j1,j2);
        }
        else{

            TourPlacement(j2,j1);
        }

        n = (n == 1) ? 2:1;
    }

    // Deuxième phase : déplacement

    EffacerEcran();

    printf("_____ Fin de la premiere phase _____\n\n");
    printf("_____ Debut de la phase de deplacement _____\n");
    AfficherPlateau();

    while(CompterPion(j1) > 2 && CompterPion(j2) > 2 && !bloque(j1, j2) && !bloque(j2, j1))
    {
        if (n == j1.id)
        {
            if(CompterPion(j1) > 3)
            {
                UnDeplacementNormal(j1,j2);
            }
            else UnDeplacementLibreDe(j1,j2);

        }
        else
        {
            if(CompterPion(j2) > 3) UnDeplacementNormal(j2,j1);
            else UnDeplacementLibreDe(j2,j1);
        }

        n = (n == 1) ? 2:1;

    }
    if(GameOver(j1) || bloque(j1,j2)) printf("\n%s a perdu !!!! \n",j1.pseudo);
    else if(GameOver(j2) || bloque(j2,j1)) printf("\n%s a perdu !!!! \n",j2.pseudo);
}

void BoucleJeuAI()
 {
     for(int i=0; i<8; i++)
        for(int j=0; j<3; j++)
            plateau[i][j].etat = non_protegee;

    int n;
    Joueur humain;

    EffacerEcran();
    printf("Informations joueur humain ( pion de l'IA est 'O') :\n");
    humain = CreatePlayer();
    EffacerEcran();

    Joueur IA = {(humain.id==1)? 2:1, "Mr.ROBOT", 'O'};
    printf("Bonjour %s, vous jouez une partie contre %s !\n",humain.pseudo,IA.pseudo);
    n = random_int() ;

    // Première phase : placement


    AfficherPlateau();
    for(int i=1; i<=18; i++)
    {
        if(n == humain.id){
            TourPlacement(humain,IA);
            AfficherPlateau();
        }
        else{

            IA_jouer(plateau, 1,IA,humain);
            //if(!PermissionDeRetirerPion(humain)) choix_retrait(humain,IA,plateau);
            if(PionAlignesHorizontal(IA) | PionAlignesVertical(IA)) choix_retrait(humain,IA,plateau);
            AfficherPlateau();
        }

        n = (n == 1) ? 2:1;
    }

    // Deuxieme phase : déplacement

    printf("_____ Fin de la premiere phase _____\n\n");
    printf("_____ Debut de la phase de deplacement _____\n");
    system("PAUSE");
    EffacerEcran();
    AfficherPlateau();

    while(CompterPion(IA) > 2 && CompterPion(humain) > 2 && !bloque(IA,humain) && !bloque(humain,IA))
    {
        if (n == humain.id)
        {
            if(CompterPion(humain) > 3)
            {
                UnDeplacementLibreDe(humain,IA);
            }
            else UnDeplacementLibreDe(humain,IA);

        }
        else
        {
            if(CompterPion(IA) > 3)
            {
                bestMove(IA, humain, 1);
                AfficherPlateau();
            }
            else
            {
                bestMoveLibre(IA, humain, 1);
                AfficherPlateau();
            }
        }

        n = (n == 1) ? 2:1;
    }
    if((CompterPion(humain) == 2) || bloque(humain,IA)) {printf("\n%s a perdu !!!! \n",humain.pseudo); system("PAUSE");}
    else if((CompterPion(IA) == 2) || bloque(IA,humain)) {printf("\n%s a perdu !!!! \n",IA.pseudo); system("PAUSE");}

 }


int random_int()
{
    srand(time(NULL));
    return (rand() % 2) + 1;
}


int OrdrePassage(Joueur j1, Joueur j2)
{
    int premier = random_int();
    if (premier == 1)
        printf("%s commence la partie !!.\n", j1.pseudo);
    else
        printf("%s commence la partie !!.\n", j2.pseudo);

    return premier;
}


int GameOver(Joueur j)
{
    if(CompterPion(j) == 2){
        printf("%s a perdu !!!! ",j.pseudo);
        return 1;
    }
    return 0;
}
