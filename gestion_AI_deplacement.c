#include <stdio.h>
#include <stdlib.h>

#include "gestion_algorithme_AI.h"
#include "gestion_cases.h"
#include "gestion_pions.h"
#include "gestion_joueurs.h"
#include "gestion_jeu.h"
#include "gestion_moulin.h"
#include "gestion_mouvements.h"
#include "gestion_placement.h"
#include "gestion_plateau.h"
#include "gestion_regles.h"

extern Case plateau[8][3];
extern Joueur joueur_vide;

extern Joueur IA;


void bestMove(Joueur IA, Joueur adversaire, int profondeur) {

    int meilleurScore = -10000;
    int bestX1 = -1, bestY1 = -1, bestX2 = -1, bestY2 = -1;
    // Vérifier si un moulin peut être complété immédiatement
    for (int x1 = 0; x1 < 8; x1++) {
        for (int y1 = 0; y1 < 3; y1++) {
            if (ComparerJoueurs(plateau[x1][y1].player,IA)) { // Trouver un pion IA

                // Tester tous les deplacements possibles de ce pion

                for (int x2 = 0; x2 < 8; x2++) {
                    for (int y2 = 0; y2 < 3; y2++) {
                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x1][y1], plateau[x2][y2])) { // Coup possible

                            PrendrePionIA(IA, x1, y1);
                            PoserPionIA(IA, x2, y2); // Effectuer le deplacement
                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(IA, x2, y2);
                                                                PoserPionIA(IA, x1, y1);continue;}
                            if (PionAlignesHorizontal(IA) | PionAlignesVertical(IA))
                            {
                                bestX1 = x1;
                                bestY1 = y1;
                                bestX2 = x2;
                                bestY2 = y2;
                            }
                            // Annuler le coup
                            PrendrePionIA(IA, x2, y2);
                            PoserPionIA(IA, x1, y1);
                        }
                    }
                }
            }
        }
    }
    // Vérifier si un moulin adverse peut être bloqué
    if( bestX1 == -1)
    {
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (ComparerJoueurs(plateau[x][y].player,IA))
                {
                    for (int x1 = 0; x1 < 8; x1++)
                    {
                        for (int y1 = 0; y1 < 3; y1++)
                        {
                            if (ComparerJoueurs(plateau[x1][y1].player,adversaire)) // Trouver un pion adverse
                            {
                                for (int x2 = 0; x2 < 8; x2++)
                                {
                                    for (int y2 = 0; y2 < 3; y2++)
                                    {
                                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x1][y1], plateau[x2][y2]))
                                        {
                                            PrendrePionIA(adversaire, x1, y1);
                                            PoserPionIA(adversaire, x2, y2);
                                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(adversaire, x2, y2);
                                                                                PoserPionIA(adversaire, x1, y1);continue;}
                                            if(PionAlignesHorizontal(adversaire) | PionAlignesVertical(adversaire))
                                            {
                                                if(ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x][y], plateau[x2][y2]))
                                                {
                                                    bestX1 = x;
                                                    bestY1 = y;
                                                    bestX2 = x2;
                                                    bestY2 = y2;
                                                }
                                            }
                                            // Annuler le coup
                                            PrendrePionIA(adversaire, x2, y2);
                                            PoserPionIA(adversaire, x1, y1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Déplacement stratégique pour optimiser ses chances de moulin
    if(bestX1 == -1)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            for (int y1 = 0; y1 < 3; y1++)
            {
                if (ComparerJoueurs(plateau[x1][y1].player,IA))
                {
                    for (int x2 = 0; x2 < 8; x2++)
                    {
                        for (int y2 = 0; y2 < 3; y2++)
                        {
                            if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x1][y1], plateau[x2][y2]))
                            {
                                PrendrePionIA(IA, x1, y1);
                                PoserPionIA(IA, x2, y2);
                                int score = -evaluateBoardDeplacement(adversaire, IA, profondeur, -10000, 10000);
                                if (score > meilleurScore)
                                {
                                    meilleurScore = score;
                                    bestX1 = x1;
                                    bestY1 = y1;
                                    bestX2 = x2;
                                    bestY2 = y2;
                                }
                                // Annuler le coup
                                PrendrePionIA(IA, x2, y2);
                                PoserPionIA(IA, x1, y1);
                            }
                        }
                    }
                }
            }
        }
    }
    // Déplacer définitivement
    if (bestX1 != -1 && bestY1 != -1 && bestX2 != -1 && bestY2 != -1 && CaseVide(plateau[bestX2][bestY2])) {
        RetirerPionIA(IA, bestX1, bestY1);
        PoserPionIA(IA, bestX2, bestY2);
        if(est_sur_ligne(plateau[bestX2][bestY2])) goto fin;
        if(PionAlignesHorizontal(IA) | PionAlignesVertical(IA))
        {
            capturePionDeplacement(&IA, &adversaire);
        }
        fin:
        printf("L'IA joue de (%d, %d) a (%d, %d)\n", bestX1+1, bestY1+1, bestX2+1, bestY2+1);
    }
    else
    {
        printf("L'IA ne trouve aucun coup valide !\n");
    }
    //AfficherPlateau();
}


void bestMoveLibre(Joueur IA, Joueur adversaire, int profondeur) {

    int meilleurScore = -10000;
    int bestX1 = -1, bestY1 = -1, bestX2 = -1, bestY2 = -1;
    //EffacerEcran();
    // Vérifier si un moulin peut être complété immédiatement

    for (int x1 = 0; x1 < 8; x1++) {
        for (int y1 = 0; y1 < 3; y1++) {
            if (ComparerJoueurs(plateau[x1][y1].player,IA)) { // Trouver un pion IA

                // Tester tous les deplacements possibles de ce pion

                for (int x2 = 0; x2 < 8; x2++) {
                    for (int y2 = 0; y2 < 3; y2++) {
                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide)) { // Coup possible

                            PrendrePionIA(IA, x1, y1);
                            PoserPionIA(IA, x2, y2); // Effectuer le deplacement
                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(IA, x2, y2);
                                                                PoserPionIA(IA, x1, y1);continue;}
                            if (PionAlignesHorizontal(IA) | PionAlignesVertical(IA))
                            {
                                bestX1 = x1;
                                bestY1 = y1;
                                bestX2 = x2;
                                bestY2 = y2;
                            }
                            // Annuler le coup
                            PrendrePionIA(IA, x2, y2);
                            PoserPionIA(IA, x1, y1);
                        }
                    }
                }
            }
        }
    }
    // Vérifier si un moulin adverse peut être bloqué
    if( bestX1 == -1)
    {
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (ComparerJoueurs(plateau[x][y].player,IA))
                {
                    for (int x1 = 0; x1 < 8; x1++)
                    {
                        for (int y1 = 0; y1 < 3; y1++)
                        {
                            if (ComparerJoueurs(plateau[x1][y1].player,adversaire)) // Trouver un pion adverse
                            {
                                for (int x2 = 0; x2 < 8; x2++)
                                {
                                    for (int y2 = 0; y2 < 3; y2++)
                                    {
                                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x1][y1], plateau[x2][y2]))
                                        {
                                            PrendrePionIA(adversaire, x1, y1);
                                            PoserPionIA(adversaire, x2, y2);
                                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(adversaire, x2, y2);
                                                                                PoserPionIA(adversaire, x1, y1);return;}
                                            if(PionAlignesHorizontal(adversaire) | PionAlignesVertical(adversaire))
                                            {
                                                if(ComparerJoueurs(plateau[x2][y2].player, joueur_vide))
                                                {
                                                    bestX1 = x;
                                                    bestY1 = y;
                                                    bestX2 = x2;
                                                    bestY2 = y2;
                                                }
                                            }
                                            // Annuler le coup
                                            PrendrePionIA(adversaire, x2, y2);
                                            PoserPionIA(adversaire, x1, y1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Déplacement stratégique pour optimiser ses chances de moulin
    if(bestX1 == -1)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            for (int y1 = 0; y1 < 3; y1++)
            {
                if (ComparerJoueurs(plateau[x1][y1].player,IA))
                {
                    for (int x2 = 0; x2 < 8; x2++)
                    {
                        for (int y2 = 0; y2 < 3; y2++)
                        {
                            if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide))
                            {
                                PrendrePionIA(IA, x1, y1);
                                PoserPionIA(IA, x2, y2);
                                int score = -evaluateBoardDeplacement(adversaire, IA, profondeur, -10000, 10000);
                                if (score > meilleurScore)
                                {
                                    meilleurScore = score;
                                    bestX1 = x1;
                                    bestY1 = y1;
                                    bestX2 = x2;
                                    bestY2 = y2;
                                }
                                // Annuler le coup
                                PrendrePionIA(IA, x2, y2);
                                PoserPionIA(IA, x1, y1);
                            }
                        }
                    }
                }
            }
        }
    }
    // Placer le pion sur la meilleure case
    if (bestX1 != -1 && bestY1 != -1 && bestX2 != -1 && bestY2 != -1 && CaseVide(plateau[bestX2][bestY2])) {
        RetirerPionIA(IA, bestX1, bestY1);
        PoserPionIA(IA, bestX2, bestY2);
        if(est_sur_ligne(plateau[bestX2][bestY2])) goto fin;
        if(PionAlignesHorizontal(IA) | PionAlignesVertical(IA))
        {
            capturePionDeplacement(&IA, &adversaire);
        }
        fin:
        printf("L'IA joue de (%c, %c) a (%c, %c)\n", plateau[bestX1][bestY1].coord1, plateau[bestX1][bestY1].coord2, plateau[bestX2][bestY2].coord1, plateau[bestX2][bestY2].coord2);
    }
    else
    {
        printf("L'IA ne trouve aucun coup valide !\n");
    }
    //AfficherPlateau();
}






