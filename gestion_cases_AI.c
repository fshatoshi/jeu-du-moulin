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

int CasesAlignees(Case c2,Case c1, Case c3)
{
        // Ligne A
    if (c1.coord1 == 'A' && c1.coord2 == 'A')
        return ((c2.coord1 == 'A' && c2.coord2 == 'D' && c3.coord1 == 'A' && c3.coord2 == 'G') || (c2.coord1 == 'D' && c2.coord2 == 'A' && c3.coord1 == 'G' && c3.coord2 == 'A'));

    if (c1.coord1 == 'A' && c1.coord2 == 'D')
        return ((c2.coord1 == 'B' && c2.coord2 == 'D' && c3.coord1 == 'C' && c3.coord2 == 'D'));

    if (c1.coord1 == 'A' && c1.coord2 == 'G')
        return ((c2.coord1 == 'D' && c2.coord2 == 'G' && c3.coord1 == 'G' && c3.coord2 == 'G'));

    // Ligne B
    if (c1.coord1 == 'B' && c1.coord2 == 'B')
        return ((c2.coord1 == 'B' && c2.coord2 == 'D' && c3.coord1 == 'B' && c3.coord2 == 'F') || (c2.coord1 == 'D' && c2.coord2 == 'B' && c3.coord1 == 'F' && c3.coord2 == 'B'));


    if (c1.coord1 == 'B' && c1.coord2 == 'F')
        return ((c2.coord1 == 'D' && c2.coord2 == 'F' && c3.coord1 == 'F' && c3.coord2 == 'F'));

    // Ligne C
    if (c1.coord1 == 'C' && c1.coord2 == 'C')
        return ((c2.coord1 == 'C' && c2.coord2 == 'D' && c3.coord1 == 'C' && c3.coord2 == 'E') || (c2.coord1 == 'D' && c2.coord2 == 'C' && c3.coord1 == 'E' && c3.coord2 == 'C'));


    if (c1.coord1 == 'C' && c1.coord2 == 'E')
        return ((c2.coord1 == 'D' && c2.coord2 == 'E' && c3.coord1 == 'E' && c3.coord2 == 'E'));

    // Ligne D
    if (c1.coord1 == 'D' && c1.coord2 == 'A')
        return ((c2.coord1 == 'D' && c2.coord2 == 'B' && c3.coord1 == 'D' && c3.coord2 == 'C'));


    if (c1.coord1 == 'D' && c1.coord2 == 'E')
        return ((c2.coord1 == 'D' && c2.coord2 == 'F' && c3.coord1 == 'D' && c3.coord2 == 'G'));


    // Ligne E
    if (c1.coord1 == 'E' && c1.coord2 == 'C')
        return ((c2.coord1 == 'E' && c2.coord2 == 'D' && c3.coord1 == 'E' && c3.coord2 == 'E'));

    if (c1.coord1 == 'E' && c1.coord2 == 'D')
        return ((c2.coord1 == 'F' && c2.coord2 == 'D' && c3.coord1 == 'G' && c3.coord2 == 'D'));


    // Ligne F
    if (c1.coord1 == 'F' && c1.coord2 == 'B')
        return ((c2.coord1 == 'F' && c2.coord2 == 'D' && c3.coord1 == 'F' && c3.coord2 == 'F'));


    // Ligne G
    if (c1.coord1 == 'G' && c1.coord2 == 'A')
        return ((c2.coord1 == 'G' && c2.coord2 == 'D' && c3.coord1 == 'G' && c3.coord2 == 'G'));


    return 0; // Pas voisines
}
