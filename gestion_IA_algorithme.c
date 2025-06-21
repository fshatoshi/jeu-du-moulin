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

//Joueur IA = createAI();


int evaluateBoardDeplacement(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta) {
    if (profondeur == 0) {
        return evaluate(IA, adversaire);
    }

    int meilleurScore = -10000;

    // 1 Tester tous les pions de l'IA
    for (int x1 = 0; x1 < 8; x1++)
    {
        for (int y1 = 0; y1 < 3; y1++)
        {
            if (ComparerJoueurs(plateau[x1][y1].player, IA))
            { // Pion IA trouvé

                // 2 Tester tous les déplacements possibles
                for (int x2 = 0; x2 < 8; x2++)
                {
                    for (int y2 = 0; y2 < 3; y2++)
                    {
                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide) && CasesVoisines(plateau[x1][y1],plateau[x2][y2]))
                        {
                            // Jouer le coup
                            PrendrePionIA(IA, x1, y1);
                            PoserPionIA(IA, x2, y2);
                            int score = -evaluateBoardDeplacement(adversaire,IA, profondeur - 1, beta, alpha);
                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(IA, x2, y2);
                                                                PoserPionIA(IA, x1, y1);continue;}
                            // 3 Vérifier si un moulin a été formé
                            if (PionAlignesHorizontal(IA) | PionAlignesVertical(IA))   // isMoulin(plateau[x2][y2])
                            {
                                // Tester différentes captures et optimiser la meilleure
                                for (int xc = 0; xc < 8; xc++)
                                {
                                    for (int yc = 0; yc < 3; yc++)
                                    {
                                        if (ComparerJoueurs(plateau[xc][yc].player, adversaire) && plateau[xc][yc].etat == non_protegee)
                                        {
                                            // Simuler la capture
                                            RetirerPionIA(adversaire, xc, yc);
                                            int newScore = -evaluateBoardDeplacement(adversaire, IA, profondeur - 1, beta, alpha);
                                            // Annuler la capture
                                            PoserPionIA(adversaire, xc, yc);
                                            // Optimiser la capture
                                            if (newScore > score)
                                            {
                                                score = newScore;
                                            }
                                        }
                                    }
                                }
                            }
                            // Annuler le coup
                            PrendrePionIA(IA, x2, y2);
                            PoserPionIA(IA, x1, y1);
                            // Maximisation
                            if (score > meilleurScore) {
                                meilleurScore = score;
                            }

                            // Alpha-Beta Pruning
                            if (score > alpha) {
                                alpha = score;
                            }
                            if (alpha >= beta) {
                                return alpha;
                            }
                        }
                    }
                }
            }
        }
    }

    return meilleurScore;
}



int evaluateBoardDeplacementLibre(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta) {
    if (profondeur == 0) {
        return evaluate(IA, adversaire);
    }

    int meilleurScore = -10000;

    // 1 Tester tous les pions de l'IA
    for (int x1 = 0; x1 < 8; x1++)
    {
        for (int y1 = 0; y1 < 3; y1++)
        {
            if (ComparerJoueurs(plateau[x1][y1].player, IA))
            { // Pion IA trouvé

                // 2 Tester tous les déplacements possibles
                for (int x2 = 0; x2 < 8; x2++)
                {
                    for (int y2 = 0; y2 < 3; y2++)
                    {
                        if (ComparerJoueurs(plateau[x2][y2].player, joueur_vide))
                        {
                            // Jouer le coup
                            PrendrePionIA(IA, x1, y1);
                            PoserPionIA(IA, x2, y2);
                            int score = -evaluateBoardDeplacement(adversaire,IA, profondeur - 1, -beta, -alpha);
                            // 3 Vérifier si un moulin a été formé
                            if(est_sur_ligne(plateau[x2][y2])) {PrendrePionIA(IA, x2, y2);
                                                                PoserPionIA(IA, x1, y1);continue;}
                            if (PionAlignesHorizontal(IA) | PionAlignesVertical(IA))
                            {
                                // Tester différentes captures et optimiser la meilleure
                                for (int xc = 0; xc < 8; xc++)
                                {
                                    for (int yc = 0; yc < 3; yc++)
                                    {
                                        if (ComparerJoueurs(plateau[xc][yc].player, adversaire) && plateau[xc][yc].etat == non_protegee)
                                        {
                                            // Simuler la capture
                                            RetirerPionIA(adversaire, xc, yc);
                                            int newScore = -evaluateBoardDeplacement(adversaire, IA, profondeur - 1, beta, alpha);
                                            // Annuler la capture
                                            PoserPionIA(adversaire, xc, yc);
                                            // Optimiser la capture
                                            if (newScore > score)
                                            {
                                                score = newScore;
                                            }
                                        }
                                    }
                                }
                            }
                            // Annuler le coup
                            PrendrePionIA(IA, x2, y2);
                            PoserPionIA(IA, x1, y1);
                            // Maximisation
                            if (score > meilleurScore) {
                                meilleurScore = score;
                            }

                            // Alpha-Beta Pruning
                            if (score > alpha) {
                                alpha = score;
                            }
                            if (alpha >= beta) {
                                return alpha;
                            }
                        }
                    }
                }
            }
        }
    }

    return meilleurScore;
}



int evaluateBoardPlacement(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta) {
    if (profondeur == 0) {
        return evaluate(IA, adversaire);
    }

    int meilleurScore = -10000;

    // 1 Tester toutes les cases possibles
    for (int x1 = 0; x1 < 8; x1++)
    {
        for (int y1 = 0; y1 < 3; y1++)
        {
            if (ComparerJoueurs(plateau[x1][y1].player, joueur_vide))
            { // case vide trouvée

                // 2 Tester tous les placements possibles
                PoserPionIA(IA, x1, y1);
                int score = -evaluate(adversaire, IA);
                //if(est_sur_ligne(plateau[x1][y1])) goto saut;
                // 3 Vérifier si un moulin a été formé
                if (PionAlignesHorizontal(IA) || PionAlignesVertical(IA))
                {
                    // Tester différentes captures et optimiser la meilleure
                    for (int xc = 0; xc < 8; xc++)
                    {
                        for (int yc = 0; yc < 3; yc++)
                        {
                            if (ComparerJoueurs(plateau[xc][yc].player, adversaire) && plateau[xc][yc].etat == non_protegee)
                            {
                                // Simuler la capture
                                RetirerPionIA(adversaire, xc, yc);
                                int newScore = -evaluate(adversaire, IA);
                                // Annuler la capture
                                PoserPionIA(adversaire, xc, yc);
                                // Optimiser la capture
                                if (newScore > score)
                                {
                                    score = newScore;
                                }
                            }
                        }
                    }
                }// saut:
                // Annuler le coup
                RetirerPionIA(IA, x1, y1);
                // Maximisation
                if (score > meilleurScore)
                {
                    meilleurScore = score;
                    // Alpha-Beta Pruning
                    if (score > alpha)
                    {
                        alpha = score;
                    }
                    if (alpha >= beta)
                    {
                        return alpha;
                    }
                }

            }
        }
    }

    return meilleurScore;
}
