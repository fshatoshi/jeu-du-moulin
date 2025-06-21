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

extern Joueur joueur_vide;
extern Case plateau[8][3];

void RetirerPion(Joueur j)
{
    Point t;
    char a, b;
    while (1) {
        printf("UN MOULIN OBTENU !!!\n");
        printf("Quel pion de %s voulez vous retirer ? ",j.pseudo);
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        if (est_ce_protege(plateau[t.x][t.y])) printf("Cette case est protegee ! \n");
        if (t.x != -1 && t.y != -1 && ComparerJoueurs(plateau[t.x][t.y].player, j) && !CaseVide(plateau[t.x][t.y]) && !est_ce_protege(plateau[t.x][t.y])) {
            break;
        }
    }
    plateau[t.x][t.y].etat = non_protegee;
    plateau[t.x][t.y].player = joueur_vide;
    plateau[t.x][t.y].player.pion = joueur_vide.pion;
}


void RetraitForcePion(Joueur j)
{
    Point t;
    char a, b;
    while (1) {
        printf("UN MOULIN OBTENU !!!\n");
        redo:
        printf("%s a obtenu un moulin !!\nQuel pion voulez vous retirer ? ",j.pseudo);
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        //if (est_ce_protege(plateau[t.x][t.y])) printf("Cette case est protege ! ");
        if (t.x != -1 && t.y != -1 && !CaseVide(plateau[t.x][t.y]) ) {
            break;
        }else goto redo;
    }
    plateau[t.x][t.y].etat = non_protegee;
    plateau[t.x][t.y].player = joueur_vide;
    plateau[t.x][t.y].player.pion = joueur_vide.pion;
}


Point PrendrePion(Joueur j1)
{
    Point t;
    Quadruplet q;
    char a, b;
    while (1) {
        printf("Quel pion voulez vous deplacer %s ? ",j1.pseudo);
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        q = PionsVoisins(t.x,t.y);
        if (t.x != -1 && t.y != -1 && est_ce_occupe_par(j1,plateau[t.x][t.y]) && ( ComparerJoueurs(plateau[q.p1.x][q.p1.y].player, joueur_vide) ||
                                                                                    ComparerJoueurs(plateau[q.p2.x][q.p2.y].player, joueur_vide) ||
                                                                                    ComparerJoueurs(plateau[q.p3.x][q.p3.y].player, joueur_vide) ||
                                                                                    ComparerJoueurs(plateau[q.p4.x][q.p4.y].player, joueur_vide) )) {
            break;
        }
    }
    LeverProtection(&plateau[t.x][t.y]);
    plateau[t.x][t.y].etat = non_protegee;
    plateau[t.x][t.y].player = joueur_vide;
    plateau[t.x][t.y].player.pion = joueur_vide.pion;
    return t;
}

Point PrendrePionLibre(Joueur j1)
{
    Point t;
    Quadruplet q;
    char a, b;
    while (1) {
        printf("Quel pion voulez vous deplacer %s ? ",j1.pseudo);
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        q = PionsVoisins(t.x,t.y);
        if (t.x != -1 && t.y != -1 && est_ce_occupe_par(j1,plateau[t.x][t.y]) ) {
            break;
        }
    }
    LeverProtection(&plateau[t.x][t.y]);
    plateau[t.x][t.y].etat = non_protegee;
    plateau[t.x][t.y].player = joueur_vide;
    plateau[t.x][t.y].player.pion = joueur_vide.pion;
    return t;
}


Point PoserPion(Joueur j,Point x)
{
    Point t;
    char a, b;
    while (1) {
        printf("Ou voulez vous le poser ? ");
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        if(t.x==x.x && t.y==x.y) break;
        if (t.x != -1 && t.y != -1 && CaseVide(plateau[t.x][t.y]) && (CasesVoisines(plateau[t.x][t.y],plateau[x.x][x.y])
                                                                         || ComparerCases(plateau[t.x][t.y],plateau[x.x][x.y]))) {
            break;
        }
    }

    plateau[t.x][t.y].player = j;
    plateau[t.x][t.y].player.pion = j.pion;
    printf("Position placee : %c %c\n", plateau[t.x][t.y].coord1, plateau[t.x][t.y].coord2);

    return t;
}


Point PoserPionLibre(Joueur j, Point x)
{
    Point t;
    char a, b;
    while (1) {
        printf("Ou voulez vous poser le ? : ",j.pseudo);
        fflush(stdin);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        if (t.x != -1 && t.y != -1 && CaseVide(plateau[t.x][t.y]) && !ComparerCases(plateau[t.x][t.y],plateau[x.x][x.y]) ) {
            break;
        }
    }

    plateau[t.x][t.y].player = j;
    plateau[t.x][t.y].player.pion = j.pion;
    printf("Position placee : %c %c\n", plateau[t.x][t.y].coord1, plateau[t.x][t.y].coord2);

    return t;
}


Quadruplet PionsVoisins(int a,int b)
{
    Quadruplet voisins_case;

    // Initialiser tous les voisins avec -1
    voisins_case.p1.x = voisins_case.p1.y = -1;
    voisins_case.p2.x = voisins_case.p2.y = -1;
    voisins_case.p3.x = voisins_case.p3.y = -1;
    voisins_case.p4.x = voisins_case.p4.y = -1;

    // Définir les voisins en fonction des coordonnées (x, y)
    if (a == 0 && b == 0) {
        voisins_case.p1 = traduire('A', 'D');
        voisins_case.p2 = traduire('D', 'A');
    }
    if (a == 0 && b == 1) {
        voisins_case.p1 = traduire('A', 'A');
        voisins_case.p2 = traduire('A', 'G');
        voisins_case.p3 = traduire('B', 'D');
    }
    if (a == 0 && b == 2) {
        voisins_case.p1 = traduire('A', 'D');
        voisins_case.p2 = traduire('D', 'G');
    }
    if (a == 1 && b == 0) {
        voisins_case.p1 = traduire('B', 'B');
        voisins_case.p2 = traduire('D', 'B');
    }
    if (a == 1 && b == 1) {
        voisins_case.p1 = traduire('B', 'B');
        voisins_case.p2 = traduire('B', 'F');
        voisins_case.p3 = traduire('A', 'D');
        voisins_case.p4 = traduire('C', 'D');
    }
    if (a == 1 && b == 2) {
        voisins_case.p1 = traduire('B', 'D');
        voisins_case.p2 = traduire('D', 'F');
    }
    if (a == 2 && b == 0) {
        voisins_case.p1 = traduire('C', 'C');
        voisins_case.p2 = traduire('D', 'C');
    }
    if (a == 2 && b == 1) {
        voisins_case.p1 = traduire('C', 'C');
        voisins_case.p2 = traduire('C', 'E');
        voisins_case.p3 = traduire('B', 'D');
    }
    if (a == 2 && b == 2) {
        voisins_case.p1 = traduire('C', 'D');
        voisins_case.p2 = traduire('D', 'E');
    }
    if (a == 3 && b == 0) {
        voisins_case.p1 = traduire('A', 'A');
        voisins_case.p2 = traduire('D', 'B');
        voisins_case.p3 = traduire('G', 'A');
    }
    if (a == 3 && b == 1) {
        voisins_case.p1 = traduire('B', 'B');
        voisins_case.p2 = traduire('D', 'A');
        voisins_case.p3 = traduire('D', 'C');
        voisins_case.p4 = traduire('F', 'B');
    }
    if (a == 3 && b == 2) {
        voisins_case.p1 = traduire('C', 'C');
        voisins_case.p2 = traduire('D', 'B');
        voisins_case.p3 = traduire('E', 'C');
    }
    if (a == 4 && b == 0) {
        voisins_case.p1 = traduire('C', 'E');
        voisins_case.p2 = traduire('D', 'F');
        voisins_case.p3 = traduire('E', 'E');
    }
    if (a == 4 && b == 1) {
        voisins_case.p1 = traduire('B', 'F');
        voisins_case.p2 = traduire('D', 'E');
        voisins_case.p3 = traduire('D', 'G');
        voisins_case.p4 = traduire('F', 'F');
    }
    if (a == 4 && b == 2) {
        voisins_case.p1 = traduire('F', 'F');
        voisins_case.p2 = traduire('D', 'F');
    }
    if (a == 5 && b == 0) {
        voisins_case.p1 = traduire('E', 'C');
        voisins_case.p2 = traduire('D', 'C');
    }
    if (a == 5 && b == 1) {
        voisins_case.p1 = traduire('E', 'D');
        voisins_case.p2 = traduire('E', 'E');
        voisins_case.p3 = traduire('F', 'D');
    }
    if (a == 5 && b == 2) {
        voisins_case.p1 = traduire('E', 'D');
        voisins_case.p2 = traduire('D', 'E');
    }
    if (a == 6 && b == 0) {
        voisins_case.p1 = traduire('F', 'B');
        voisins_case.p2 = traduire('D', 'B');
    }
    if (a == 6 && b == 1) {
        voisins_case.p1 = traduire('F', 'D');
        voisins_case.p2 = traduire('F', 'F');
        voisins_case.p3 = traduire('E', 'D');
        voisins_case.p4 = traduire('G', 'D');
    }
    if (a == 6 && b == 2) {
        voisins_case.p1 = traduire('F', 'D');
        voisins_case.p2 = traduire('D', 'F');
    }
    if (a == 7 && b == 0) {
        voisins_case.p1 = traduire('D', 'A');
        voisins_case.p2 = traduire('G', 'D');
    }
    if (a == 7 && b == 1) {
        voisins_case.p1 = traduire('G', 'A');
        voisins_case.p2 = traduire('G', 'G');
    }
    if (a == 7 && b == 2) {
        voisins_case.p1 = traduire('D', 'G');
        voisins_case.p2 = traduire('G', 'D');
    }

    return voisins_case;
}


int CompterPion(Joueur jr)
{
    int nbr_pion = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            if(ComparerJoueurs(jr,plateau[i][j].player)) nbr_pion++;
        }
    }
    return nbr_pion ;
}
