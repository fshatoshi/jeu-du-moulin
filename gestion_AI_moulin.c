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

int countMoulins(Joueur joueur)
{
    int moulins = 0;

    // Vérification des alignements horizontaux
    for (int i = 0; i < 8; i++) {
        if(plateau[i][0].player.id == joueur.id &&
            plateau[i][1].player.id == joueur.id &&
            plateau[i][2].player.id == joueur.id) {
            moulins++;
        }
    }

    // Vérification des alignements verticaux
    moulins += PionAlignesVertical(joueur);

    return moulins;
}

int countPossibleMoulins(Joueur joueur) {
    int possibles = 0;

    // Vérification des alignements horizontaux
    for (int i = 0; i < 8; i++) {
        int count = 0, empty = 0;
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, joueur)) count++;
            else if (ComparerJoueurs(plateau[i][j].player, joueur_vide)) empty++;
        }
        if (count == 2 && empty == 1) possibles += 1;

    }

    // Vérification des alignements verticaux

    int count1[8] = {0,0,0,0,0,0,0,0} , empty1[8] = {0,0,0,0,0,0,0,0} ;

    if(ComparerJoueurs(plateau[0][0].player, joueur)) count1[0]+=1;
    else if(ComparerJoueurs(plateau[0][0].player, joueur_vide)) empty1[0]+=1;

    if(ComparerJoueurs(plateau[3][0].player, joueur)) count1[0]+=1;
    else if(ComparerJoueurs(plateau[3][0].player, joueur_vide)) empty1[0]+=1;

    if(ComparerJoueurs(plateau[7][0].player, joueur)) count1[0]+=1;
    else if(ComparerJoueurs(plateau[7][0].player, joueur_vide)) empty1[0]+=1;


    if(ComparerJoueurs(plateau[1][0].player, joueur)) count1[1]+=1;
    else if(ComparerJoueurs(plateau[1][0].player, joueur_vide)) empty1[1]+=1;

    if(ComparerJoueurs(plateau[3][1].player, joueur)) count1[1]+=1;
    else if(ComparerJoueurs(plateau[3][1].player, joueur_vide)) empty1[1]+=1;

    if(ComparerJoueurs(plateau[6][0].player, joueur)) count1[1]+=1;
    else if(ComparerJoueurs(plateau[6][0].player, joueur_vide)) empty1[1]+=1;


    if(ComparerJoueurs(plateau[2][0].player, joueur)) count1[2]+=1;
    else if(ComparerJoueurs(plateau[2][0].player, joueur_vide)) empty1[2]+=1;

    if(ComparerJoueurs(plateau[3][2].player, joueur)) count1[2]+=1;
    else if(ComparerJoueurs(plateau[3][2].player, joueur_vide)) empty1[2]+=1;

    if(ComparerJoueurs(plateau[5][0].player, joueur)) count1[2]+=1;
    else if(ComparerJoueurs(plateau[5][0].player, joueur_vide)) empty1[2]+=1;


    if(ComparerJoueurs(plateau[0][1].player, joueur)) count1[3]+=1;
    else if(ComparerJoueurs(plateau[0][1].player, joueur_vide)) empty1[3]+=1;

    if(ComparerJoueurs(plateau[1][1].player, joueur)) count1[3]+=1;
    else if(ComparerJoueurs(plateau[1][1].player, joueur_vide)) empty1[3]+=1;

    if(ComparerJoueurs(plateau[2][1].player, joueur)) count1[3]+=1;
    else if(ComparerJoueurs(plateau[2][1].player, joueur_vide)) empty1[3]+=1;


    if(ComparerJoueurs(plateau[5][1].player, joueur)) count1[4]+=1;
    else if(ComparerJoueurs(plateau[5][1].player, joueur_vide)) empty1[4]+=1;

    if(ComparerJoueurs(plateau[6][1].player, joueur)) count1[4]+=1;
    else if(ComparerJoueurs(plateau[6][1].player, joueur_vide)) empty1[4]+=1;

    if(ComparerJoueurs(plateau[7][1].player, joueur)) count1[4]+=1;
    else if(ComparerJoueurs(plateau[7][1].player, joueur_vide)) empty1[4]+=1;


    if(ComparerJoueurs(plateau[2][2].player, joueur)) count1[5]+=1;
    else if(ComparerJoueurs(plateau[2][2].player, joueur_vide)) empty1[5]+=1;

    if(ComparerJoueurs(plateau[4][0].player, joueur)) count1[5]+=1;
    else if(ComparerJoueurs(plateau[4][0].player, joueur_vide)) empty1[5]+=1;

    if(ComparerJoueurs(plateau[5][2].player, joueur)) count1[5]+=1;
    else if(ComparerJoueurs(plateau[5][2].player, joueur_vide)) empty1[5]+=1;


    if(ComparerJoueurs(plateau[1][2].player, joueur)) count1[6]+=1;
    else if(ComparerJoueurs(plateau[1][2].player, joueur_vide)) empty1[6]+=1;

    if(ComparerJoueurs(plateau[4][1].player, joueur)) count1[6]+=1;
    else if(ComparerJoueurs(plateau[4][1].player, joueur_vide)) empty1[6]+=1;

    if(ComparerJoueurs(plateau[6][2].player, joueur)) count1[6]+=1;
    else if(ComparerJoueurs(plateau[6][2].player, joueur_vide)) empty1[6]+=1;


    if(ComparerJoueurs(plateau[0][2].player, joueur)) count1[7]+=1;
    else if(ComparerJoueurs(plateau[0][2].player, joueur_vide)) empty1[7]+=1;

    if(ComparerJoueurs(plateau[4][2].player, joueur)) count1[7]+=1;
    else if(ComparerJoueurs(plateau[4][2].player, joueur_vide)) empty1[7]+=1;

    if(ComparerJoueurs(plateau[7][2].player, joueur)) count1[7]+=1;
    else if(ComparerJoueurs(plateau[7][2].player, joueur_vide)) empty1[7]+=1;


    for (int i = 0; i < 8; i++)
    {
        if (count1[i] == 2 && empty1[i] == 1) possibles += 1;

    }

    return possibles;
}

int countBlockedPions(Joueur joueur) {
    int blocked = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 3; y++) {
            if (ComparerJoueurs(plateau[x][y].player, joueur)) { // Trouver un pion du joueur
                Quadruplet q = PionsVoisins(x,y);
                int hasMove = 0;

                // Vérifier les déplacements possibles

                if(ComparerJoueurs(plateau[q.p1.x][q.p1.y].player, joueur_vide) || ComparerJoueurs(plateau[q.p2.x][q.p2.y].player, joueur_vide) || ComparerJoueurs(plateau[q.p3.x][q.p3.y].player, joueur_vide) || ComparerJoueurs(plateau[q.p4.x][q.p4.y].player, joueur_vide))
                {
                    hasMove = 1;
                }

                if (!hasMove) blocked++;
            }
        }
    }

    return blocked;
}


int isMoulin(Case c)
{
    Doublet a = TrouverCaseTupleHorizontal(c);
    Doublet b = TrouverCaseTupleVertical(c);

    return (CasesAlignees(plateau[a.p1.x][a.p1.y], plateau[a.p2.x][a.p2.y], c) && ComparerJoueurs(plateau[a.p1.x][a.p1.y].player,c.player) && ComparerJoueurs(plateau[a.p1.x][a.p1.y].player, plateau[a.p2.x][a.p2.y].player)) ||
            (CasesAlignees(plateau[b.p1.x][b.p1.y], plateau[a.p2.x][a.p2.y], c) && ComparerJoueurs(plateau[b.p1.x][b.p1.y].player,c.player) && ComparerJoueurs(plateau[b.p1.x][b.p1.y].player, plateau[b.p2.x][b.p2.y].player));

}

int proche_moulin(Joueur J1,int x,int y){
    Doublet t,h;
    if(!ComparerJoueurs(plateau[x][y].player,J1)) return -555;
    if(ComparerJoueurs(plateau[x][y].player,joueur_vide)) return 0;
    t = TrouverCaseTupleHorizontal(plateau[x][y]);
    h = TrouverCaseTupleVertical(plateau[x][y]);
    if((est_ce_occupe_par(J1,plateau[t.p1.x][t.p1.y]) ^ est_ce_occupe_par(J1,plateau[t.p2.x][t.p2.y])) ^
       (est_ce_occupe_par(J1,plateau[h.p1.x][h.p1.y]) ^ est_ce_occupe_par(J1,plateau[h.p2.x][h.p2.y]) ))
        return 1;
    return 0;
}

int moulin_bloque(Joueur J1,Joueur j2,int x,int y){
    Doublet t,h;
    if(!ComparerJoueurs(plateau[x][y].player,J1)) return -555;
    if(ComparerJoueurs(plateau[x][y].player,joueur_vide)) return 0;
    t = TrouverCaseTupleHorizontal(plateau[x][y]);
    h = TrouverCaseTupleVertical(plateau[x][y]);
    if((est_ce_occupe_par(J1,plateau[t.p1.x][t.p1.y]) && est_ce_occupe_par(j2,plateau[t.p2.x][t.p2.y])) ^
       (est_ce_occupe_par(J1,plateau[h.p1.x][h.p1.y]) && est_ce_occupe_par(j2,plateau[h.p2.x][h.p2.y]) ) ^
       (est_ce_occupe_par(j2,plateau[t.p1.x][t.p1.y]) && est_ce_occupe_par(J1,plateau[t.p2.x][t.p2.y])) ^
       (est_ce_occupe_par(j2,plateau[h.p1.x][h.p1.y]) && est_ce_occupe_par(J1,plateau[h.p2.x][h.p2.y]) ))
        return 1;
    return 0;
}

int pion_isole(Joueur J1,int x,int y){
    Doublet h,t;
    if(!ComparerJoueurs(plateau[x][y].player,J1)) return -555;
    if(ComparerJoueurs(plateau[x][y].player,joueur_vide)) return 0;
    t = TrouverCaseTupleHorizontal(plateau[x][y]);
    h = TrouverCaseTupleVertical(plateau[x][y]);
    if(!est_ce_occupe_par(J1,plateau[t.p1.x][t.p1.y]) && !est_ce_occupe_par(J1,plateau[t.p2.x][t.p2.y]) &&
       !est_ce_occupe_par(J1,plateau[h.p1.x][h.p1.y]) && !est_ce_occupe_par(J1,plateau[h.p2.x][h.p2.y]))
        return 1;
    return 0;
}

int attention_proche_moulin(Joueur J1,int x,int y){
    Doublet t,h;
    if(!ComparerJoueurs(plateau[x][y].player,J1)) return -555;
    if(ComparerJoueurs(plateau[x][y].player,joueur_vide)) return 0;
    t = TrouverCaseTupleHorizontal(plateau[x][y]);
    h = TrouverCaseTupleVertical(plateau[x][y]);
    if((est_ce_occupe_par(J1,plateau[t.p1.x][t.p1.y]) ^ est_ce_occupe_par(J1,plateau[t.p2.x][t.p2.y])) &&
       (est_ce_occupe_par(J1,plateau[h.p1.x][h.p1.y]) ^ est_ce_occupe_par(J1,plateau[h.p2.x][h.p2.y]) ))
        return 1;
    return 0;
}

int est_dans_moulin(Joueur J1,int x,int y){
    Doublet t,h;
    if(!ComparerJoueurs(plateau[x][y].player,J1)) return -555;
    if(ComparerJoueurs(plateau[x][y].player,joueur_vide)) return 0;
    t = TrouverCaseTupleHorizontal(plateau[x][y]);
    h = TrouverCaseTupleVertical(plateau[x][y]);
    if((est_ce_occupe_par(J1,plateau[t.p1.x][t.p1.y]) && est_ce_occupe_par(J1,plateau[t.p2.x][t.p2.y])) ||
       (est_ce_occupe_par(J1,plateau[h.p1.x][h.p1.y]) && est_ce_occupe_par(J1,plateau[h.p2.x][h.p2.y]) ))
        return 1;
    return 0;
}


Doublet priorite(Joueur j2,Joueur J1,int x, int y){
    int p;
    Doublet t;
    if(proche_moulin(j2,x,y)) p = 50;
    if(attention_proche_moulin(j2,x,y)) p = 100;
    if(pion_isole(j2,x,y)) p = 0;
    if(moulin_bloque(j2,J1,x,y)) p = 80;
    if(est_dans_moulin(j2,x,y)) p = -110;
    t.p1.x = x;
    t.p1.y = y;
    t.p2.x = p;
    t.p2.y = p;
    return t;
}

void choix_retrait(Joueur j2,Joueur J1,Case plateau[8][3]){
    Doublet t,prioritaire;
    prioritaire = priorite(j2,J1,0,0);
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 3;j++){
            if(ComparerJoueurs(plateau[i][j].player,j2)){
                t = priorite(j2,J1,i,j);
                if(t.p2.x > prioritaire.p2.x){
                    prioritaire.p1.x = i;
                    prioritaire.p1.y = j;
                    prioritaire.p2.x = t.p2.x;
                    prioritaire.p2.y = t.p2.y;
                    //prioritaire = t;
                }
            }
        }
    }
    printf("\n___ La Case prioritaire est (%d , %d) de priorite %d_____\n",prioritaire.p1.x,prioritaire.p1.y,prioritaire.p2.x);
    if(ComparerJoueurs(plateau[prioritaire.p1.x][prioritaire.p1.y].player,joueur_vide)){
       printf("\n____ bizarre il s'agit du Joueur vide____\n");
       }
    RetirerPionIA(j2,prioritaire.p1.x,prioritaire.p1.y);

}
