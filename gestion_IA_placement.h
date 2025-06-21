#ifndef GESTION_IA_PLACEMENT_H_INCLUDED
#define GESTION_IA_PLACEMENT_H_INCLUDED



int Min(Joueur machine, Joueur j2, Case plateau[8][3], int profondeur, int alpha, int beta);
int Max(Joueur machine, Joueur j2, Case plateau[8][3], int profondeur, int alpha, int beta);
void IA_jouer(Case plateau[8][3], int profondeur, Joueur machine, Joueur j2);
void tour_placement_ia(Joueur machine, Joueur j2);

Doublet priorite(Joueur j2,Joueur J1,int x, int y);
void choix_retrait(Joueur j2,Joueur J1,Case plateau[8][3]);
void boucle_1_machine_vs_Joueur();


#endif // GESTION_IA_PLACEMENT_H_INCLUDED
