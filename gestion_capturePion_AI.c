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


void capturePionPlacement(Joueur *IA, Joueur *adversaire) {
    int impact = 0, max_impact = -1000;
    int x_best = -1, y_best = -1;

    // Parcourir tous les pions adverses
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 3; y++) {
            if (ComparerJoueurs(plateau[x][y].player, *adversaire)) {  // Trouvé un pion adverse
                int impact = 0;
                // Vérifier si ce pion fait partie d'un moulin → On l'évite
                if (est_ce_protege(plateau[x][y])) {
                    continue;  // Ignorer ce pion s'il fait partie d'un moulin
                }

                //Vérifier si ce pion pourrait compléter un futur moulin adverse

                RetirerPionIA(*adversaire, x, y); // Pion retiré temporairement
                if (countPossibleMoulins(*adversaire) > 0)
                {
                    impact+=50; // On veut casser une menace
                }
                PoserPionIA(*adversaire, x, y);

                // Vérifier si ce pion bloque un de nos pions

                if (!isBlockingIA(*IA, x, y))
                {
                    impact+=30;
                }

                // Vérifier s'il y a peu d’options de mouvement pour l’adversaire

                if (countBlockedPions(*adversaire) > countBlockedPions(*IA)) {
                    impact += 20; // On renforce l’enfermement de l’adversaire
                }

                //  Trouver le pion qui a le plus d’impact stratégique

                if (impact > max_impact) {
                    max_impact = impact;
                    x_best = x;
                    y_best = y;
                }
            }
        }
    }

    // Retirer le meilleur pion choisi
    if (x_best != -1 && y_best != -1) {
        RetirerPionIA(*adversaire, x_best, y_best); // Supprimer le pion adversaire
        printf("L'IA capture un pion en (%c, %c)\n", plateau[x_best][y_best].coord1, plateau[x_best][y_best].coord2);
    }
    else
    {
        printf("Aucun pion capture !\n");
    }
}

void capturePionDeplacement(Joueur *IA, Joueur *adversaire) {
    int meilleurScore = -10000;
    int x_best = -1, y_best = -1;

    // Explorer tous les pions adverses
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 3; y++) {
            if (ComparerJoueurs(plateau[x][y].player, *adversaire)) {  // Trouvé un pion adverse

                // Vérifier si ce pion est protégé (fait partie d’un moulin)
                if (PionAlignesHorizontal(plateau[x][y].player) || PionAlignesVertical(plateau[x][y].player)) {
                    continue;  // Ignorer ce pion s'il fait partie d'un moulin
                }

                // Simuler la suppression du pion adverse
                PrendrePionIA(*adversaire, x, y); // Pion retiré temporairement
                // Évaluer l'impact de cette suppression
                int score = -evaluateBoardDeplacement(*adversaire, *IA, 1, -10000, 10000);

                // Restaurer le pion après simulation
                PoserPionIA(*adversaire, x, y);

                // Choisir le meilleur coup
                if (score > meilleurScore) {
                    meilleurScore = score;
                    x_best = x;
                    y_best = y;
                }
            }
        }
    }

    // Retirer le meilleur pion choisi
    if (x_best != -1 && y_best != -1) {
        RetirerPionIA(*adversaire, x_best, y_best);  // Supprimer le pion adversaire
        printf("L'IA capture un pion en (%c, %c)\n", x_best, y_best);
    }
    else
    {
        printf("Aucun pion capture !\n");
    }
}
