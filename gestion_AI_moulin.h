#ifndef GESTION_AI_MOULIN_H_INCLUDED
#define GESTION_AI_MOULIN_H_INCLUDED

void choix_retrait(Joueur j2,Joueur J1,Case plateau[8][3]);
Doublet priorite(Joueur j2,Joueur J1,int x, int y);
int proche_moulin(Joueur J1,int x,int y);
int moulin_bloque(Joueur J1,Joueur j2,int x,int y);
int pion_isole(Joueur J1,int x,int y);
int attention_proche_moulin(Joueur J1,int x,int y);
int est_dans_moulin(Joueur J1,int x,int y);


#endif // GESTION_AI_MOULIN_H_INCLUDED
