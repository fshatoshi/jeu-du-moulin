#ifndef GESTION_M_H_H_INCLUDED
#define GESTION_M_H_H_INCLUDED


void machine_placer(int a, int b, Joueur machine);
Point machine_prendre_pion(int a, int b, Joueur machine);
void Joueur_placer(int a, int b, Joueur j2);
Point Joueur_prendre_pion(int a, int b, Joueur j2);
int proche_moulin(Joueur J1, int x, int y);
int moulin_bloque(Joueur J1, Joueur j2, int x, int y);
int pion_isole(Joueur J1, int x, int y);
int attention_proche_moulin(Joueur J1, int x, int y);
int est_dans_moulin(Joueur J1, int x, int y);
Doublet priorite(Joueur j2, Joueur J1, int x, int y);
void choix_retrait(Joueur j2, Joueur J1, Case plateau[8][3]);

#endif // GESTION_M_H_H_INCLUDED
