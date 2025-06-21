#ifndef GESTION_PIONS_H_INCLUDED
#define GESTION_PIONS_H_INCLUDED

#include "gestion_joueurs.h"

typedef struct
{
    int x;
    int y;
}Point;

typedef struct
{
    Point p1;
    Point p2;
}Doublet;

typedef struct
{
    Point p1;
    Point p2;
    Point p3;
}Triplet;

typedef struct
{
    Point p1;
    Point p2;
    Point p3;
    Point p4;
}Quadruplet;


void RetirerPion(Joueur);
void RetraitForcePion(Joueur);

Point PrendrePion(Joueur);
Point PrendrePionLibre(Joueur);
Point PoserPion(Joueur, Point);
Point PoserPionLibre(Joueur, Point);

Quadruplet PionsVoisins(int, int);

int CompterPion(Joueur);

#endif // GESTION_PIONS_H_INCLUDED
