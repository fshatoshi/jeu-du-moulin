#ifndef GESTION_JEU_H_INCLUDED
#define GESTION_JEU_H_INCLUDED

#include "gestion_joueurs.h"

void menu();
void EffacerEcran();
void BoucleJeu();
int random_int();
int OrdrePassage(Joueur, Joueur);
int GameOver(Joueur);

#endif // GESTION_JEU_H_INCLUDED
