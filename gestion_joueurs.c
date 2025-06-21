#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestion_cases.h"
#include "gestion_pions.h"
#include "gestion_joueurs.h"
#include "gestion_jeu.h"
#include "gestion_moulin.h"
#include "gestion_mouvements.h"
#include "gestion_placement.h"
#include "gestion_plateau.h"
#include "gestion_regles.h"


Joueur CreatePlayer()
{
    Joueur j;

    printf("Choisissez votre id de joueur {1|2} : ");
    scanf("%d", &j.id);
    printf("Choisissez votre pion de jeu : ");
    scanf(" %c", &j.pion);  // L'espace avant %c permet d'ignorer les caractères indésirables dans le buffer
    printf("Entrez votre pseudo : ");
    scanf(" %19[^\n]", j.pseudo);

    //j.nb_pion = 9;

    return j;
}

int ComparerJoueurs(Joueur j1, Joueur j2)
{
    return (j1.id == j2.id &&
        j1.pion == j2.pion &&
        strcmp(j1.pseudo, j2.pseudo) == 0);
}
