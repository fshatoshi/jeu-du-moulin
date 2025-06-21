#ifndef GESTION_MOUVEMENTS_H_INCLUDED
#define GESTION_MOUVEMENTS_H_INCLUDED

#include "gestion_joueurs.h"


Joueur PhaseDeDeplacement(Joueur, Joueur);
void PhaseDeDeplacementFin(Joueur, Joueur);
int UnDeplacementNormal(Joueur, Joueur);
void UnDeplacementLibreDe(Joueur, Joueur);
//void TourDeplacement(Joueur, Joueur);

#endif // GESTION_MOUVEMENTS_H_INCLUDED
