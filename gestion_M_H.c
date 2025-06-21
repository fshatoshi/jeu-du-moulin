#include "prototype.h"

extern Case plateau[8][3];
extern Joueur joueur_vide;

void machine_placer( int a, int b,Joueur machine) {

    Point p = {a, b};

    while (1) {
        if (p.x != -1 && p.y != -1 && CaseVide(plateau[p.x][p.y])) {
            break;
        }
        printf("\n___ il y'a un probleme_placer_machine_placer _____\n");
        system("PAUSE");
    }
    plateau[p.x][p.y].player = machine;
    plateau[p.x][p.y].player.pion = machine.pion;

}

Point machine_prendre_pion( int a, int b,Joueur machine) {
    Point p = {a, b};

    while (1) {
        if (p.x != -1 && p.y != -1 && est_ce_occupe_par(machine, plateau[p.x][p.y])) {
            break;
        }
        if(!est_ce_occupe_par(machine, plateau[p.x][p.y])) printf("\nNOPE\n");
        printf("\n___ il y'a un probleme_machine_prendre _____\n");
        system("PAUSE");
    }

    plateau[p.x][p.y].player = joueur_vide;
    plateau[p.x][p.y].player.pion = joueur_vide.pion;
    return p;
}

void Joueur_placer( int a, int b,Joueur j2) {
    Point p = {a, b};

    while (1) {
        if (p.x != -1 && p.y != -1 && CaseVide(plateau[p.x][p.y])) {
            break;
        }
        printf("\n___ il y'a un probleme8JOUEUR8PLACER _____\n");
        system("PAUSE");
    }
    plateau[p.x][p.y].player = j2;
    plateau[p.x][p.y].player.pion = j2.pion;
}

Point Joueur_prendre_pion( int a, int b,Joueur j2) {
    Point p = {a, b};

    while (1) {
        if (p.x != -1 && p.y != -1 && est_ce_occupe_par(j2, plateau[p.x][p.y])) {
            break;
        }
        printf("\n___ il y'a un probleme8JOUEUR8PRENDRE _____\n");
        system("PAUSE");
    }

    plateau[p.x][p.y].player = joueur_vide;
    plateau[p.x][p.y].player.pion = joueur_vide.pion;
    return p;
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
    Joueur_prendre_pion(prioritaire.p1.x,prioritaire.p1.y,j2);

}

