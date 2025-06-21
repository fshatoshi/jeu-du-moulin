#include "prototype.h"
#include <stdio.h>
#include <stdlib.h>
extern Joueur joueur_vide;
extern Case plateau[8][3];
const int tailles = 1000;
Pilequadruplet* mapile;
quadruplet mes_quadruplets[2000];

int generer_quadruplets_possibles_deplacement_fin(Case plateau[8][3], quadruplet mes_quadruplets[]) {
    int nb = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (!ComparerJoueurs(plateau[i][j].player, joueur_vide)) {
                for (int a = 0; a < 8; a++) {
                    for (int b = 0; b < 3; b++) {
                        if ((a != i || b != j) && ComparerJoueurs(plateau[a][b].player, joueur_vide)) {
                            mes_quadruplets[nb].x_depart = i;
                            mes_quadruplets[nb].y_depart = j;
                            mes_quadruplets[nb].x_arrive = a;
                            mes_quadruplets[nb].y_arrive = b;
                            nb++;
                        }
                    }
                }
            }
        }
    }
    return nb;
}

int Max_deplacement_fin(Case plateau[8][3], int profondeur, int alpha, int beta) {
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau, machine, j2);
    }

    int nb = generer_quadruplets_possibles_deplacement_fin(plateau, mes_quadruplets);
    int max = -10000;

    for (int i = 0; i < nb; i++) {
        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, j2) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
            Joueur_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart, j2);
            Joueur_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive, j2);
            empiler(mapile, mes_quadruplets[i]);

            int tmp = Min_deplacement_fin(plateau, profondeur - 1, alpha, beta);
            max = (tmp > max) ? tmp : max;
            alpha = (tmp > alpha) ? tmp : alpha;

            quadruplet q = depiler(mapile);
            Joueur_prendre_pion(q.x_arrive, q.y_arrive, j2);
            Joueur_placer(q.x_depart, q.y_depart, j2);

            if (alpha >= beta) break;
        }
    }
    return max;
}

int Min_deplacement_fin(Case plateau[8][3], int profondeur, int alpha, int beta) {
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau, machine, j2);
    }

    int nb = generer_quadruplets_possibles_deplacement_fin(plateau, mes_quadruplets);
    int min = 10000;

    for (int i = 0; i < nb; i++) {
        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, machine) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
            machine_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart, machine);
            machine_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive, machine);
            empiler(mapile, mes_quadruplets[i]);

            int tmp = Max_deplacement_fin(plateau, profondeur - 1, alpha, beta);
            min = (tmp < min) ? tmp : min;
            beta = (tmp < beta) ? tmp : beta;

            quadruplet q = depiler(mapile);
            machine_prendre_pion(q.x_arrive, q.y_arrive, machine);
            machine_placer(q.x_depart, q.y_depart, machine);

            if (alpha >= beta) break;
        }
    }
    return min;
}

quadruplet meilleur_quadruplet_fin(Case plateau[8][3], Joueur machine, int profondeur) {
    mapile = (Pilequadruplet*)malloc(tailles * sizeof(quadruplet));
    initialiser_pile(mapile, tailles);
    int my_score = 0;
    int alpha = -10000, beta = 10000;
    int nb_quadruplets = generer_quadruplets_possibles_deplacement_fin(plateau, mes_quadruplets);
    int meilleur_score = -10000;
    quadruplet quadruplet_choisi, q;
    quadruplet_choisi.x_depart = -1;
    quadruplet_choisi.y_depart = -1;
    quadruplet_choisi.x_arrive = -1;
    quadruplet_choisi.y_arrive = -1;

    for (int i = 0; i < nb_quadruplets; i++) {
        generer_quadruplets_possibles_deplacement_fin(plateau, mes_quadruplets);
        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, machine) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
            machine_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart, machine);
            machine_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive, machine);
            empiler(mapile, mes_quadruplets[i]);

            int score = Min_deplacement_fin(plateau, profondeur - 1, alpha, beta);

            if (score > meilleur_score) {
                meilleur_score = score;
                quadruplet mine = depiler(mapile);
                quadruplet_choisi = mine;
                empiler(mapile, mine);
            }

            q = depiler(mapile);
            my_score = score;
            machine_prendre_pion(q.x_arrive, q.y_arrive, machine);
            machine_placer(q.x_depart, q.y_depart, machine);
        }
    }
    printf("\n quadruplets = (%d, %d, %d, %d)\n", quadruplet_choisi.x_depart, quadruplet_choisi.y_depart, quadruplet_choisi.x_arrive, quadruplet_choisi.y_arrive);
    printf("\n\n Le score est : %d\n\n", my_score);
    return quadruplet_choisi;
}

void un_deplacement_normal_IA_fin(Joueur machine, Joueur j2) {
    quadruplet q = meilleur_quadruplet_fin(plateau, machine, 1);
    Point p = machine_prendre_pion(q.x_depart, q.y_depart, machine);
    if (est_dans_moulin(machine, p.x, p.y)) LeverProtection(&plateau[p.x][p.y]);
    machine_placer(q.x_arrive, q.y_arrive, machine);
    AfficherPlateau();
    liberer_pile(mapile);
}
