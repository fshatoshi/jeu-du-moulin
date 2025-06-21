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
#include "gestion_conversion.h"

extern Case plateau[8][3];
extern Joueur joueur_vide;

//extern Joueur IA;

Point PrendrePionIA(Joueur j, int a, int b)
{
    Point t = {a,b};
    Quadruplet q;
    q = PionsVoisins(a,b);
    if(ComparerJoueurs(plateau[q.p1.x][q.p1.y].player, joueur_vide) ||
       ComparerJoueurs(plateau[q.p2.x][q.p2.y].player, joueur_vide) ||
       ComparerJoueurs(plateau[q.p3.x][q.p3.y].player, joueur_vide) ||
       ComparerJoueurs(plateau[q.p4.x][q.p4.y].player, joueur_vide))
       {
            //LeverProtection(&plateau[t.x][t.y]);
           // plateau[t.x][t.y].etat = non_protegee;
            plateau[t.x][t.y].player = joueur_vide;
            plateau[t.x][t.y].player.pion = joueur_vide.pion;
    return t;
       }
}



Point PoserPionIA(Joueur j, int a, int b)
{
    Point t = {a, b};
    if (t.x != -1 && t.y != -1 && CaseVide(plateau[t.x][t.y]) )
    {
        plateau[t.x][t.y].player = j;
        plateau[t.x][t.y].player.pion = j.pion;
        printf("Position placee : %c %c\n", plateau[t.x][t.y].coord1, plateau[t.x][t.y].coord2);
    }
    return t;
}

void RetirerPionIA(Joueur j, int a, int b)
{
    Point t = {a, b};
    if (est_ce_protege(plateau[t.x][t.y])) {printf("Cette case est protegee ! \n");return;}
    else
    {
        plateau[t.x][t.y].etat = non_protegee;
        plateau[t.x][t.y].player = joueur_vide;
        plateau[t.x][t.y].player.pion = joueur_vide.pion;
    }
}
/*
void RetraitForcePionIA(Joueur j, int a, int b)
{
    Point t = {a, b};
    if (est_ce_protege(plateau[t.x][t.y])) printf("Cette case est protege ! ");
    if (t.x != -1 && t.y != -1 && !CaseVide(plateau[t.x][t.y]) ) {
            break;
    }
    plateau[t.x][t.y].etat = non_protegee;
    plateau[t.x][t.y].player = joueur_vide;
    plateau[t.x][t.y].player.pion = joueur_vide.pion;
}*/

int isBlockingIA(Joueur IA, int x, int y)
{
    int count = 0;
    for(int x1 = 0; x1 < 8; x1++)
    {
        for(int y1 = 0; y1 < 3; y1++)
        {
            if(!CaseVide(plateau[x1][y1]) && CasesVoisines(plateau[x1][y1],plateau[x][y]))
            {
                for(int x2 = 0; x2 < 8; x2++)
                {
                    for(int y2 = 0; y2 < 3; y2++)
                    {
                        if((x2 != x1) && (y2 != y1) && !CaseVide(plateau[x2][y2]) && CasesAlignees(plateau[x1][x2], plateau[x2][y2], plateau[x][y]))
                        {
                            if(ComparerJoueurs(plateau[x1][y1].player, IA)) count+=1;
                            if(ComparerJoueurs(plateau[x2][y2].player, IA)) count+=1;
                        }
                    }
                }
            }
        }
    }
    return count;
}

