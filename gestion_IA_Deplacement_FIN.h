#ifndef GESTION_IA_DEPLACEMENT_FIN_H_INCLUDED
#define GESTION_IA_DEPLACEMENT_FIN_H_INCLUDED
int Min_deplacement_fin(Case plateau[8][3], int profondeur, int alpha, int beta);
int Max_deplacement_fin(Case plateau[8][3], int profondeur, int alpha, int beta);
int generer_quadruplets_possibles_deplacement_fin(Case plateau[8][3], quadruplet mes_quadruplets[]);
quadruplet meilleur_quadruplet_fin(Case plateau[8][3], Joueur machine, int profondeur);
void un_deplacement_normal_IA_fin(Joueur machine, Joueur j2);


#endif // GESTION_IA_DEPLACEMENT_FIN_H_INCLUDED
