#include <stdio.h>
#include <stdlib.h>

#include "gestion_cases.h"
#include "gestion_pions.h"
#include "gestion_joueurs.h"
#include "gestion_jeu.h"
#include "gestion_moulin.h"
#include "gestion_mouvements.h"
#include "gestion_placement.h"
#include "gestion_plateau.h"
#include "gestion_regles.h"
#include "gestion_conversion.h"

Case plateau[8][3];

Triplet triplet_null = {{-1,1},{-1,-1},{-1,-1}};
Joueur joueur_vide = { 0, "", ' ', 9 };

void AfficherPlateau()
{
    printf("\n");
    printf("\n\t\t\t       A       B     C         D        E     F       G");
    printf("\n");

    for (int i = 0; i <= 15; i++) {
        if (i == 0) {
            printf("\n\t\t\t   A   %c --------------------- %c -------------------- %c",
                   plateau[0][0].player.pion, plateau[0][1].player.pion, plateau[0][2].player.pion);
        } else if (i == 8) {
            printf("\n\t\t\t   D   %c-----  %c  ---%c                  %c---  %c ----- %c",
                   plateau[3][0].player.pion, plateau[3][1].player.pion, plateau[3][2].player.pion,
                   plateau[4][0].player.pion, plateau[4][1].player.pion, plateau[4][2].player.pion);
        } else if (i == 3) {
            printf("\n\t\t\t   B   |       %c ------------- %c -------------%c       |",
                   plateau[1][0].player.pion, plateau[1][1].player.pion, plateau[1][2].player.pion);
        } else if (i == 6) {
            printf("\n\t\t\t   C   |       |      %c------- %c ------%c      |       |",
                   plateau[2][0].player.pion, plateau[2][1].player.pion, plateau[2][2].player.pion);
        } else if ((i == 1) || (i == 2) || (i == 14) || (i == 15)) {
            printf("\n\t\t\t       |                       |                      |");
        } else if ((i == 4) || (i == 5) || (i == 11) || (i == 12)) {
            printf("\n\t\t\t       |       |               |              |       |");
        } else if (i == 10) {
            printf("\n\t\t\t   E   |       |      %c------- %c ------%c      |       |",
                   plateau[5][0].player.pion, plateau[5][1].player.pion, plateau[5][2].player.pion);
        } else if (i == 13) {
            printf("\n\t\t\t   F   |       %c ------------- %c -------------%c       |",
                   plateau[6][0].player.pion, plateau[6][1].player.pion, plateau[6][2].player.pion);
        } else if ((i == 7) || (i == 9)) {
            printf("\n\t\t\t       |       |     |                  |     |       |");
        }
    }

    printf("\n\t\t\t   G   %c --------------------- %c -------------------- %c\n",
           plateau[7][0].player.pion, plateau[7][1].player.pion, plateau[7][2].player.pion);
}

void InitialiserPlateau()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            plateau[i][j].player = joueur_vide;
            InverseTraduire(i,j);
            plateau[i][j].x = j;
            plateau[i][j].y = i;
            plateau[i][j].etat = non_protegee ;
        }
    }
}
