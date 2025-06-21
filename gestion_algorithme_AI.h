#ifndef GESTION_ALGORITHME_AI_H_INCLUDED
#define GESTION_ALGORITHME_AI_H_INCLUDED

#include "gestion_joueurs.h"
#include "gestion_cases.h"

Joueur createAI(Joueur j);
void placePionIA(Joueur *IA, Joueur adversaire, int profondeur);
void capturePionPlacement(Joueur *IA, Joueur *adversaire);
void capturePionDeplacement(Joueur *IA, Joueur *adversaire);

// Gestion IA PLACEMENT

int Max(Joueur machine, Joueur j2,Case plateau[8][3], int profondeur, int alpha, int beta);
int Min(Joueur machine, Joueur j2,Case plateau[8][3], int profondeur, int alpha, int beta);
void IA_jouer(Case plateau[8][3], int profondeur,Joueur machine,Joueur j2);
void tour_placement_ia(Joueur machine,Joueur j2);
void boucle_1_machine_vs_Joueur();


int isValidMove(int x1, int y1, int x2, int y2);


int evaluate(Joueur machine, Joueur j2);
int evaluateBoardDeplacement(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta);
int evaluateBoardDeplacementLibre(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta);
int evaluateBoardPlacement(Joueur IA, Joueur adversaire, int profondeur, int alpha, int beta);
void bestMove(Joueur IA, Joueur adversaire, int profondeur);
void bestMoveLibre(Joueur IA, Joueur adversaire, int profondeur);



int countPossibleMoulins(Joueur joueur);
int countMoulins(Joueur joueur);
int countBlockedPions(Joueur joueur);
int isBlockingIA(Joueur IA, int x, int y);
int isMoulin(Case c);


Point PrendrePionIA(Joueur j, int a, int b);
Point PoserPionIA(Joueur j, int a, int b);
void RetirerPionIA(Joueur j, int a, int b);

int CasesAlignees(Case c2,Case c1, Case c3);

//Point PrendrePionLibreIA(Joueur j1, int a, int b);
//Point PoserPionLibreIA(Joueur j, Point x, int a, int b);
//void RetraitForcePionIA(Joueur j, int a, int b);


#endif // GESTION_ALGORITHME_AI_H_INCLUDED
