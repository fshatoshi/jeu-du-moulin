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

extern Case plateau[8][3];


int PionAlignesHorizontal(Joueur jr)
{
    int i = 0, j = 0, aligne = 1;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 3; j++) {
            if (!ComparerJoueurs(plateau[i][j].player, jr)) {
                aligne = 0;
                break;
            }
        }
        if (aligne && !LigneProtegee(plateau[i][0],plateau[i][1],plateau[i][2])) {
            for (j = 0; j < 3; j++) {
                plateau[i][j].etat = protegee;
            }
            return 1;
        }
        aligne = 1;
    }
    return 0;
}


int PionAlignesVertical(Joueur jr)
{
        int aligne = 0;

    if (ComparerJoueurs(plateau[0][0].player, jr) && ComparerJoueurs(plateau[3][0].player, jr) && ComparerJoueurs(plateau[7][0].player, jr) &&
        !LigneProtegee(plateau[0][0], plateau[3][0], plateau[7][0])) {
        plateau[0][0].etat = protegee;
        plateau[3][0].etat = protegee;
        plateau[7][0].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[1][0].player, jr) && ComparerJoueurs(plateau[3][1].player, jr) && ComparerJoueurs(plateau[6][0].player, jr) &&
        !LigneProtegee(plateau[1][0], plateau[3][1], plateau[6][0])) {
        plateau[1][0].etat = protegee;
        plateau[3][1].etat = protegee;
        plateau[6][0].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[2][0].player, jr) && ComparerJoueurs(plateau[3][2].player, jr) && ComparerJoueurs(plateau[5][0].player, jr) &&
        !LigneProtegee(plateau[2][0], plateau[3][2], plateau[5][0])) {
        plateau[2][0].etat = protegee;
        plateau[3][2].etat = protegee;
        plateau[5][0].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[0][1].player, jr) && ComparerJoueurs(plateau[1][1].player, jr) && ComparerJoueurs(plateau[2][1].player, jr) &&
        !LigneProtegee(plateau[0][1], plateau[1][1], plateau[2][1])) {
        plateau[0][1].etat = protegee;
        plateau[1][1].etat = protegee;
        plateau[2][1].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[5][1].player, jr) && ComparerJoueurs(plateau[6][1].player, jr) && ComparerJoueurs(plateau[7][1].player, jr) &&
        !LigneProtegee(plateau[5][1], plateau[6][1], plateau[7][1])) {
        plateau[5][1].etat = protegee;
        plateau[6][1].etat = protegee;
        plateau[7][1].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[2][2].player, jr) && ComparerJoueurs(plateau[4][0].player, jr) && ComparerJoueurs(plateau[5][2].player, jr) &&
        !LigneProtegee(plateau[2][2], plateau[4][0], plateau[5][2])) {
        plateau[2][2].etat = protegee;
        plateau[4][0].etat = protegee;
        plateau[5][2].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[1][2].player, jr) && ComparerJoueurs(plateau[4][1].player, jr) && ComparerJoueurs(plateau[6][2].player, jr) &&
        !LigneProtegee(plateau[1][2], plateau[4][1], plateau[6][2])) {
        plateau[1][2].etat = protegee;
        plateau[4][1].etat = protegee;
        plateau[6][2].etat = protegee;
        aligne++;
    }

    if (ComparerJoueurs(plateau[0][2].player, jr) && ComparerJoueurs(plateau[4][2].player, jr) && ComparerJoueurs(plateau[7][2].player, jr) &&
        !LigneProtegee(plateau[0][2], plateau[4][2], plateau[7][2])) {
        plateau[0][2].etat = protegee;
        plateau[4][2].etat = protegee;
        plateau[7][2].etat = protegee;
        aligne++;
    }

    return (aligne > 0);
}

