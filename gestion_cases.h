#ifndef GESTION_CASES_H_INCLUDED
#define GESTION_CASES_H_INCLUDED

#include "gestion_joueurs.h"
#include "gestion_pions.h"


typedef enum Etat
{
    protegee,
    non_protegee
}Etat_case;

typedef struct st_case
{
    int x,y,coord1,coord2;
    Etat_case etat;
    Joueur player;
}Case;

int CaseVide(Case);
int CasesVoisines(Case, Case);
int ComparerCases(Case, Case);
Triplet TrouverCaseHorizontal(Case);
Triplet TrouverCaseVertical(Case);
Doublet TrouverCaseTupleHorizontal(Case);
Doublet TrouverCaseTupleVertical(Case);

#endif // GESTION_CASES_H_INCLUDED
