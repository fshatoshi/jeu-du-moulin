#ifndef GESTION_REGLES_H_INCLUDED
#define GESTION_REGLES_H_INCLUDED

#include "gestion_joueurs.h"
#include "gestion_cases.h"


int PermissionDeRetirerPion(Joueur j);
int bloque(Joueur j1, Joueur j2);
int LigneProtegee(Case c1, Case c2, Case c3);
int est_ce_protege(Case);
int est_ce_occupe_par(Joueur j,Case c);
void LeverProtection(Case *c);
int est_sur_ligne(Case c);
void AfficherProtection();

#endif // GESTION_REGLES_H_INCLUDED
