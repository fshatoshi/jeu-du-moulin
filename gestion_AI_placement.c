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


// Création du joueur AI
Joueur adversaire;

Joueur createAI(Joueur j)
{
    Joueur IA;

    IA.id = (j.id == 1)? 2:1;
    IA.pion = 'O';
    IA.pseudo[10] = "Mr.ROBOT";
    return IA;
}
