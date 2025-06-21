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

extern Triplet triplet_null;
extern Case plateau[8][3];
extern Joueur joueur_vide;

int CaseVide(Case c)
{
    if (ComparerJoueurs(c.player,joueur_vide)) {
        return 1;
    }
    return 0;
}



int CasesVoisines(Case c2,Case c1)
{
        // Ligne A
    if (c1.coord1 == 'A' && c1.coord2 == 'A')
        return ((c2.coord1 == 'A' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'A'));

    if (c1.coord1 == 'A' && c1.coord2 == 'D')
        return ((c2.coord1 == 'A' && c2.coord2 == 'A') || (c2.coord1 == 'A' && c2.coord2 == 'G') || (c2.coord1 == 'B' && c2.coord2 == 'D'));

    if (c1.coord1 == 'A' && c1.coord2 == 'G')
        return ((c2.coord1 == 'A' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'G'));

    // Ligne B
    if (c1.coord1 == 'B' && c1.coord2 == 'B')
        return ((c2.coord1 == 'B' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'B'));

    if (c1.coord1 == 'B' && c1.coord2 == 'D')
        return ((c2.coord1 == 'B' && c2.coord2 == 'B') || (c2.coord1 == 'B' && c2.coord2 == 'F') || (c2.coord1 == 'A' && c2.coord2 == 'D') || (c2.coord1 == 'C' && c2.coord2 == 'D'));

    if (c1.coord1 == 'B' && c1.coord2 == 'F')
        return ((c2.coord1 == 'B' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'F'));

    // Ligne C
    if (c1.coord1 == 'C' && c1.coord2 == 'C')
        return ((c2.coord1 == 'C' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'C'));

    if (c1.coord1 == 'C' && c1.coord2 == 'D')
        return ((c2.coord1 == 'C' && c2.coord2 == 'C') || (c2.coord1 == 'C' && c2.coord2 == 'E') || (c2.coord1 == 'B' && c2.coord2 == 'D'));

    if (c1.coord1 == 'C' && c1.coord2 == 'E')
        return ((c2.coord1 == 'C' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'E'));

    // Ligne D
    if (c1.coord1 == 'D' && c1.coord2 == 'A')
        return ((c2.coord1 == 'A' && c2.coord2 == 'A') || (c2.coord1 == 'D' && c2.coord2 == 'B') || (c2.coord1 == 'G' && c2.coord2 == 'A'));

    if (c1.coord1 == 'D' && c1.coord2 == 'B')
        return ((c2.coord1 == 'B' && c2.coord2 == 'B') || (c2.coord1 == 'D' && c2.coord2 == 'A') || (c2.coord1 == 'D' && c2.coord2 == 'C') || (c2.coord1 == 'F' && c2.coord2 == 'B'));

    if (c1.coord1 == 'D' && c1.coord2 == 'C')
        return ((c2.coord1 == 'C' && c2.coord2 == 'C') || (c2.coord1 == 'D' && c2.coord2 == 'B') || (c2.coord1 == 'E' && c2.coord2 == 'C'));

    if (c1.coord1 == 'D' && c1.coord2 == 'E')
        return ((c2.coord1 == 'C' && c2.coord2 == 'E') || (c2.coord1 == 'D' && c2.coord2 == 'F') || (c2.coord1 == 'E' && c2.coord2 == 'E'));

    if (c1.coord1 == 'D' && c1.coord2 == 'F')
        return ((c2.coord1 == 'B' && c2.coord2 == 'F') || (c2.coord1 == 'D' && c2.coord2 == 'E') || (c2.coord1 == 'D' && c2.coord2 == 'G') || (c2.coord1 == 'F' && c2.coord2 == 'F'));

    if (c1.coord1 == 'D' && c1.coord2 == 'G')
        return ((c2.coord1 == 'A' && c2.coord2 == 'G') || (c2.coord1 == 'D' && c2.coord2 == 'F') || (c2.coord1 == 'G' && c2.coord2 == 'G'));

    // Ligne E
    if (c1.coord1 == 'E' && c1.coord2 == 'C')
        return ((c2.coord1 == 'E' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'C'));

    if (c1.coord1 == 'E' && c1.coord2 == 'D')
        return ((c2.coord1 == 'E' && c2.coord2 == 'C') || (c2.coord1 == 'E' && c2.coord2 == 'E') || (c2.coord1 == 'F' && c2.coord2 == 'D'));

    if (c1.coord1 == 'E' && c1.coord2 == 'E')
        return ((c2.coord1 == 'E' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'E'));

    // Ligne F
    if (c1.coord1 == 'F' && c1.coord2 == 'B')
        return ((c2.coord1 == 'F' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'B'));

    if (c1.coord1 == 'F' && c1.coord2 == 'D')
        return ((c2.coord1 == 'F' && c2.coord2 == 'B') || (c2.coord1 == 'F' && c2.coord2 == 'F') || (c2.coord1 == 'E' && c2.coord2 == 'D') || (c2.coord1 == 'G' && c2.coord2 == 'D'));

    if (c1.coord1 == 'F' && c1.coord2 == 'F')
        return ((c2.coord1 == 'F' && c2.coord2 == 'D') || (c2.coord1 == 'D' && c2.coord2 == 'F'));

    // Ligne G
    if (c1.coord1 == 'G' && c1.coord2 == 'A')
        return ((c2.coord1 == 'D' && c2.coord2 == 'A') || (c2.coord1 == 'G' && c2.coord2 == 'D'));

    if (c1.coord1 == 'G' && c1.coord2 == 'D')
        return ((c2.coord1 == 'G' && c2.coord2 == 'A') || (c2.coord1 == 'G' && c2.coord2 == 'G') || (c2.coord1 == 'F' && c2.coord2 == 'D'));

    if (c1.coord1 == 'G' && c1.coord2 == 'G')
        return ((c2.coord1 == 'D' && c2.coord2 == 'G') || (c2.coord1 == 'G' && c2.coord2 == 'D'));

    return 0; // Pas voisines
}


int ComparerCases(Case c1, Case c2)
{
    return (c1.x == c2.x && c1.y == c2.y);
}


Doublet TrouverCaseTupleHorizontal(Case c)
{
    Doublet result;

    // Vérification sur chaque ligne du tableau
    for (int i = 0; i < 8; i++) {
        if (ComparerCases(c, plateau[i][0])) {
            // Si c est dans la première case de la ligne, on renvoie les autres cases
            result.p1.x = i; result.p1.y = 1;
            result.p2.x = i; result.p2.y = 2;
            return result;
        }
        if (ComparerCases(c, plateau[i][1])) {
            // Si c est dans la deuxième case de la ligne, on renvoie les autres cases
            result.p1.x = i; result.p1.y = 0;
            result.p2.x = i; result.p2.y = 2;
            return result;
        }
        if (ComparerCases(c, plateau[i][2])) {
            // Si c est dans la troisième case de la ligne, on renvoie les autres cases
            result.p1.x = i; result.p1.y = 0;
            result.p2.x = i; result.p2.y = 1;
            return result;
        }
    }

    // Si aucune correspondance trouvée, retourner un tuple nul
    result.p1.x = -1; result.p1.y = -1;
    result.p2.x = -1; result.p2.y = -1;
    return result;
}


Doublet TrouverCaseTupleVertical(Case c)
{
    Doublet result;

    // Vérification sur la première colonne
    if (ComparerCases(c, plateau[0][0])) {
        result.p1.x = 3; result.p1.y = 0;
        result.p2.x = 7; result.p2.y = 0;
        return result;
    }
    if (ComparerCases(c, plateau[3][0])) {
        result.p1.x = 0; result.p1.y = 0;
        result.p2.x = 7; result.p2.y = 0;
        return result;
    }
    if (ComparerCases(c, plateau[7][0])) {
        result.p1.x = 0; result.p1.y = 0;
        result.p2.x = 3; result.p2.y = 0;
        return result;
    }

    // Vérification sur la deuxième colonne
    if (ComparerCases(c, plateau[1][0])) {
        result.p1.x = 3; result.p1.y = 1;
        result.p2.x = 6; result.p2.y = 0;
        return result;
    }
    if (ComparerCases(c, plateau[3][1])) {
        result.p1.x = 1; result.p1.y = 0;
        result.p2.x = 6; result.p2.y = 0;
        return result;
    }
    if (ComparerCases(c, plateau[6][0])) {
        result.p1.x = 1; result.p1.y = 0;
        result.p2.x = 3; result.p2.y = 1;
        return result;
    }

    // Vérification sur la troisième colonne
    if (ComparerCases(c, plateau[2][0])) {
        result.p1.x = 3; result.p1.y = 2;
        result.p2.x = 5; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[3][2])) {
        result.p1.x = 2; result.p1.y = 0;
        result.p2.x = 5; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[5][0])) {
        result.p1.x = 2; result.p1.y = 0;
        result.p2.x = 3; result.p2.y = 2;
        return result;
    }

    // Vérification sur la quatrième colonne
    if (ComparerCases(c, plateau[0][1])) {
        result.p1.x = 1; result.p1.y = 1;
        result.p2.x = 2; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[1][1])) {
        result.p1.x = 0; result.p1.y = 1;
        result.p2.x = 2; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[2][1])) {
        result.p1.x = 0; result.p1.y = 1;
        result.p2.x = 1; result.p2.y = 1;
        return result;
    }

    // Vérification sur la cinquième colonne
    if (ComparerCases(c, plateau[5][1])) {
        result.p1.x = 6; result.p1.y = 1;
        result.p2.x = 7; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[6][1])) {
        result.p1.x = 5; result.p1.y = 1;
        result.p2.x = 7; result.p2.y = 1;
        return result;
    }
    if (ComparerCases(c, plateau[7][1])) {
        result.p1.x = 5; result.p1.y = 1;
        result.p2.x = 6; result.p2.y = 1;
        return result;
    }

    // Vérification sur la sixième colonne
    if (ComparerCases(c, plateau[2][2])) {
        result.p1.x = 3; result.p1.y = 2;
        result.p2.x = 5; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[4][0])) {
        result.p1.x = 2; result.p1.y = 2;
        result.p2.x = 5; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[5][2])) {
        result.p1.x = 2; result.p1.y = 2;
        result.p2.x = 4; result.p2.y = 0;
        return result;
    }

    // Vérification sur la septième colonne
    if (ComparerCases(c, plateau[1][2])) {
        result.p1.x = 4; result.p1.y = 1;
        result.p2.x = 6; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[4][1])) {
        result.p1.x = 1; result.p1.y = 2;
        result.p2.x = 6; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[6][2])) {
        result.p1.x = 1; result.p1.y = 2;
        result.p2.x = 4; result.p2.y = 1;
        return result;
    }

    // Vérification sur la huitième colonne
    if (ComparerCases(c, plateau[0][2])) {
        result.p1.x = 4; result.p1.y = 2;
        result.p2.x = 7; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[4][2])) {
        result.p1.x = 0; result.p1.y = 2;
        result.p2.x = 7; result.p2.y = 2;
        return result;
    }
    if (ComparerCases(c, plateau[7][2])) {
        result.p1.x = 0; result.p1.y = 2;
        result.p2.x = 4; result.p2.y = 2;
        return result;
    }

    // Si aucune correspondance n'est trouvée
    result.p1.x = -1; result.p1.y = -1;
    result.p2.x = -1; result.p2.y = -1;
    return result;
}


Triplet TrouverCaseHorizontal(Case c)
{
    Triplet t;

    if (ComparerCases(plateau[0][0], c) || ComparerCases(plateau[0][1], c) || ComparerCases(plateau[0][2], c)) {
        t.p1.x = 0; t.p1.y = 0;
        t.p2.x = 0; t.p2.y = 1;
        t.p3.x = 0; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[1][0], c) || ComparerCases(plateau[1][1], c) || ComparerCases(plateau[1][2], c)) {
        t.p1.x = 1; t.p1.y = 0;
        t.p2.x = 1; t.p2.y = 1;
        t.p3.x = 1; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[2][0], c) || ComparerCases(plateau[2][1], c) || ComparerCases(plateau[2][2], c)) {
        t.p1.x = 2; t.p1.y = 0;
        t.p2.x = 2; t.p2.y = 1;
        t.p3.x = 2; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[3][0], c) || ComparerCases(plateau[3][1], c) || ComparerCases(plateau[3][2], c)) {
        t.p1.x = 3; t.p1.y = 0;
        t.p2.x = 3; t.p2.y = 1;
        t.p3.x = 3; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[4][0], c) || ComparerCases(plateau[4][1], c) || ComparerCases(plateau[4][2], c)) {
        t.p1.x = 4; t.p1.y = 0;
        t.p2.x = 4; t.p2.y = 1;
        t.p3.x = 4; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[5][0], c) || ComparerCases(plateau[5][1], c) || ComparerCases(plateau[5][2], c)) {
        t.p1.x = 5; t.p1.y = 0;
        t.p2.x = 5; t.p2.y = 1;
        t.p3.x = 5; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[6][0], c) || ComparerCases(plateau[6][1], c) || ComparerCases(plateau[6][2], c)) {
        t.p1.x = 6; t.p1.y = 0;
        t.p2.x = 6; t.p2.y = 1;
        t.p3.x = 6; t.p3.y = 2;
        return t;
    }
    if (ComparerCases(plateau[7][0], c) || ComparerCases(plateau[7][1], c) || ComparerCases(plateau[7][2], c)) {
        t.p1.x = 7; t.p1.y = 0;
        t.p2.x = 7; t.p2.y = 1;
        t.p3.x = 7; t.p3.y = 2;
        return t;
    }
    return triplet_null;
}


Triplet TrouverCaseVertical(Case c)
{
    Triplet t;

    if (ComparerCases(plateau[0][0], c) || ComparerCases(plateau[3][0], c) || ComparerCases(plateau[7][0], c)) {
        t.p1.x = 0; t.p1.y = 0;
        t.p2.x = 3; t.p2.y = 0;
        t.p3.x = 7; t.p3.y = 0;
        return t;
    }

    if (ComparerCases(plateau[1][0], c) || ComparerCases(plateau[3][1], c) || ComparerCases(plateau[6][0], c)) {
        t.p1.x = 1; t.p1.y = 0;
        t.p2.x = 3; t.p2.y = 1;
        t.p3.x = 6; t.p3.y = 0;
        return t;
    }

    if (ComparerCases(plateau[2][0], c) || ComparerCases(plateau[3][2], c) || ComparerCases(plateau[5][0], c)) {
        t.p1.x = 2; t.p1.y = 0;
        t.p2.x = 3; t.p2.y = 2;
        t.p3.x = 5; t.p3.y = 1;
        return t;
    }

    if (ComparerCases(plateau[0][1], c) || ComparerCases(plateau[1][1], c) || ComparerCases(plateau[2][1], c)) {
        t.p1.x = 0; t.p1.y = 1;
        t.p2.x = 1; t.p2.y = 1;
        t.p3.x = 2; t.p3.y = 1;
        return t;
    }

    if (ComparerCases(plateau[5][1], c) || ComparerCases(plateau[6][1], c) || ComparerCases(plateau[7][1], c)) {
        t.p1.x = 5; t.p1.y = 1;
        t.p2.x = 6; t.p2.y = 1;
        t.p3.x = 7; t.p3.y = 1;
        return t;
    }

    if (ComparerCases(plateau[2][2], c) || ComparerCases(plateau[4][0], c) || ComparerCases(plateau[5][2], c)) {
        t.p1.x = 2; t.p1.y = 2;
        t.p2.x = 4; t.p2.y = 0;
        t.p3.x = 5; t.p3.y = 2;
        return t;
    }

    if (ComparerCases(plateau[1][2], c) || ComparerCases(plateau[4][1], c) || ComparerCases(plateau[6][2], c)) {
        t.p1.x = 1; t.p1.y = 2;
        t.p2.x = 4; t.p2.y = 1;
        t.p3.x = 6; t.p3.y = 2;
        return t;
    }

    if (ComparerCases(plateau[0][2], c) || ComparerCases(plateau[4][2], c) || ComparerCases(plateau[7][2], c)) {
        t.p1.x = 0; t.p1.y = 2;
        t.p2.x = 4; t.p2.y = 2;
        t.p3.x = 7; t.p3.y = 2;
        return t;
    }
    return triplet_null;
}
