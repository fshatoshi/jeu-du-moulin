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


extern Joueur joueur_vide;
extern Case plateau[8][3];

Joueur machine;
Joueur j2;

int evaluate(Joueur machine, Joueur j2) {
    int score_machine = 0;  // Score pour la machine
    int score_humain = 0;   // Score pour le joueur humain

    // Parcours des lignes horizontales (de 0 à 7)
    for (int i = 0; i < 8; i++) {
        int machine_count = 0; // Nombre de pions de la machine dans cette ligne
        int humain_count = 0;  // Nombre de pions du joueur humain dans cette ligne
        int vide_count = 0;    // Nombre de cases vides dans cette ligne

        // Verifier chaque case dans la ligne (3 cases)
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, machine)) {
                machine_count++;
            } else if (ComparerJoueurs(plateau[i][j].player, j2)) {
                humain_count++;
            } else {
                vide_count++;
            }
        }

        // Évaluation de la ligne en fonction des pions presents
        if (machine_count == 3) {
            score_machine += 100; // Moulin complet pour la machine
        } else if (machine_count == 2 && vide_count == 1) {
            score_machine += 10; // Deux pions de la machine + une case vide
        } else if (machine_count == 1 && vide_count == 2) {
            score_machine += 1; // Un pion de la machine + deux cases vides
        }

        if (humain_count == 3) {
            score_humain += 100; // Moulin complet pour le joueur humain
        } else if (humain_count == 2 && vide_count == 1) {
            score_humain += 10; // Deux pions du joueur humain + une case vide
        } else if (humain_count == 1 && vide_count == 2) {
            score_humain += 1; // Un pion du joueur humain + deux cases vides
        }
    }

    // Parcours des colonnes verticales
    for (int j = 1; j <= 8; j++) {
        int machine_count = 0;
        int humain_count = 0;
        int vide_count = 0;

        // Verifie les colonnes specifiques definies dans les règles
        if (j == 1) { // Colonne 1 (gauche)
            if (ComparerJoueurs(plateau[0][0].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[3][0].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[7][0].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[0][0].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[3][0].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[7][0].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[0][0].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[3][0].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[7][0].player, joueur_vide)) vide_count++;
        }

        if (j == 2) { // Colonne 2 (milieu)
            if (ComparerJoueurs(plateau[1][0].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[3][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[6][0].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[1][0].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[3][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[6][0].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[1][0].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[3][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[6][0].player, joueur_vide)) vide_count++;
        }

        if (j == 3) { // Colonne 3
            if (ComparerJoueurs(plateau[2][0].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[3][2].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[5][0].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[2][0].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[3][2].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[5][0].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[2][0].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[3][2].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[5][0].player, joueur_vide)) vide_count++;
        }
        if (j == 4) { // Colonne 4
            if (ComparerJoueurs(plateau[0][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[1][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[2][1].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[0][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[1][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[2][1].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[0][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[1][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[2][1].player, joueur_vide)) vide_count++;
}
        if (j == 5) { // Colonne 5
            if (ComparerJoueurs(plateau[5][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[6][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[7][1].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[5][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[6][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[7][1].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[5][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[6][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[7][1].player, joueur_vide)) vide_count++;
}
        if (j == 6) { // Colonne 6
            if (ComparerJoueurs(plateau[2][2].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[4][0].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[5][2].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[2][2].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[4][0].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[5][2].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[2][2].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[4][0].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[5][2].player, joueur_vide)) vide_count++;
}
        if (j == 7) { // Colonne 7
            if (ComparerJoueurs(plateau[1][2].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[4][1].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[6][2].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[1][2].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[4][1].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[6][2].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[1][2].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[4][1].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[6][2].player, joueur_vide)) vide_count++;
}
        if (j == 8) { // Colonne 8
            if (ComparerJoueurs(plateau[0][2].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[4][2].player, machine)) machine_count++;
            if (ComparerJoueurs(plateau[7][2].player, machine)) machine_count++;

            if (ComparerJoueurs(plateau[0][2].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[4][2].player, j2)) humain_count++;
            if (ComparerJoueurs(plateau[7][2].player, j2)) humain_count++;

            if (ComparerJoueurs(plateau[0][2].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[4][2].player, joueur_vide)) vide_count++;
            if (ComparerJoueurs(plateau[7][2].player, joueur_vide)) vide_count++;
}



        // Appliquer l'evaluation des cases verticales
        if (machine_count == 3) {
            score_machine += 100;
        } else if (machine_count == 2 && vide_count == 1) {
            score_machine += 10;
        } else if (machine_count == 1 && vide_count == 2) {
            score_machine += 1;
        }

        if (humain_count == 3) {
            score_humain += 100;
        } else if (humain_count == 2 && vide_count == 1) {
            score_humain += 10;
        } else if (humain_count == 1 && vide_count == 2) {
            score_humain += 1;
        }
    }

    // Retourner la difference des scores (machine vs humain)
    return score_machine - score_humain;
}
