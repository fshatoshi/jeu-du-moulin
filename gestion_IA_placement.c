
#include "prototype.h"



extern Case plateau[8][3];
extern  Joueur joueur_vide;


int Min(Joueur machine, Joueur j2,Case plateau[8][3], int profondeur, int alpha, int beta);




int Max(Joueur machine, Joueur j2,Case plateau[8][3], int profondeur, int alpha, int beta) {
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau,machine, j2);
    }

    int max = -10000;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, joueur_vide)) {
                machine_placer(i, j,machine);
                int tmp = Min(machine,j2,plateau, profondeur - 1, alpha, beta);
                machine_prendre_pion(i, j,machine);

                if (tmp > max) {
                    max = tmp;
                }
                if (max >= beta) return max;
                alpha = (max > alpha) ? max : alpha;
            }
        }
    }
    return max;
}

int Min(Joueur machine, Joueur j2,Case plateau[8][3], int profondeur, int alpha, int beta) {
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau,machine, j2);
    }

    int min = 10000;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, joueur_vide)) {
                Joueur_placer(i,j,j2);
                int tmp = Max(machine,j2,plateau, profondeur - 1, alpha, beta);
                Joueur_prendre_pion(i,j,j2);

                if (tmp < min) {
                    min = tmp;
                }
                if (min <= alpha) return min;
                beta = (min < beta) ? min : beta;
            }
        }
    }
    return min;
}

void IA_jouer(Case plateau[8][3], int profondeur,Joueur machine,Joueur j2) {
    int max = -10000, alpha = -10000, beta = 10000;
    int maxi = -1, maxj = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, joueur_vide)) {
                machine_placer(i, j,machine);
                int tmp = Min(machine,j2,plateau, profondeur - 1, alpha, beta);
                machine_prendre_pion(i,j,machine);

                if (tmp > max) {
                    max = tmp;
                    maxi = i;
                    maxj = j;
                }
                alpha = (max > alpha) ? max : alpha;
            }
        }
    }

    if (maxi != -1 && maxj != -1) {
        machine_placer(maxi, maxj,machine);
    }
}


void tour_placement_ia(Joueur machine,Joueur j2){
    AfficherPlateau();
    PlacerPion(j2);
    AfficherPlateau();
    if(PionAlignesHorizontal(j2) | PionAlignesVertical(j2)){
        if(PermissionDeRetirerPion(machine) ){
           RetraitForcePion(machine);
            AfficherPlateau();
           goto saut;
           }
        if(!PermissionDeRetirerPion(machine)){
            RetirerPion(machine);
            AfficherPlateau();
        }
    }
    saut :
    AfficherProtection();
    AfficherPlateau();
    IA_jouer(plateau, 1,machine,j2);
    AfficherPlateau();
    if(PionAlignesHorizontal(machine) | PionAlignesVertical(machine)){
        if(PermissionDeRetirerPion(j2) ){
           choix_retrait(j2,machine,plateau);
           AfficherPlateau();
           goto saup1;
           }
        if(!PermissionDeRetirerPion(j2)){
            choix_retrait(j2,machine,plateau);
            AfficherPlateau();
        }
    }
    saup1 :
    AfficherProtection();
}

/*void boucle_1_machine_vs_Joueur(){
    for(int i = 0; i < 9;i++)
        tour_placement_ia(machine,j2);
}*/
