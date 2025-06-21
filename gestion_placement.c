#include <stdio.h>
#include <stdlib.h>

#include "gestion_cases.h"
#include "gestion_pions.h"
#include "gestion_joueurs.h"
#include "gestion_jeu.h"
#include "gestion_moulin.h"
#include "gestion_mouvements.h"
#include "gestion_placement.h"
#include "gestion_plateau.h"
#include "gestion_regles.h"
#include "gestion_conversion.h"


extern Case plateau[8][3];

void PlacerPion(Joueur j)
{
    Point t;
    char a, b;

    while (1) {
        printf("C'est a %s de jouer : ",j.pseudo);
        scanf(" %c %c", &a, &b);
        t = traduire(a, b);
        if (t.x != -1 && t.y != -1 && CaseVide(plateau[t.x][t.y]) && !est_ce_protege(plateau[t.x][t.y])) {
            break;
        }
    }
    plateau[t.x][t.y].player = j;
    plateau[t.x][t.y].player.pion = j.pion;
    printf("Position placee : %d %d\n", t.x+1, t.y+1);
}


void TourPlacement(Joueur j1, Joueur j2)
{
    //AfficherPlateau();
    PlacerPion(j1);
    AfficherPlateau();
    if(PionAlignesHorizontal(j1) | PionAlignesVertical(j1)){
        if(PermissionDeRetirerPion(j2) ){
           RetraitForcePion(j2);
           //AfficherPlateau();
           //goto saut;
           }
        if(!PermissionDeRetirerPion(j2)){
            RetirerPion(j2);
            //AfficherPlateau();
        }
    }
    //saut :
    //AfficherProtection();
    //AfficherPlateau();
    /*PlacerPion(j2);
    AfficherPlateau();
    if(PionAlignesHorizontal(j2) | PionAlignesVertical(j2)){
        if(PermissionDeRetirerPion(j1) ){
           RetraitForcePion(j1);
           AfficherPlateau();
           goto saut1;
           }
        if(!PermissionDeRetirerPion(j1)){
            RetirerPion(j1);
            AfficherPlateau();
        }
    }
    saut1 :
    AfficherProtection(); */
}


void PhaseDePlacement(Joueur j1, Joueur j2)
{
    for (int i=0;i<6;i++){
        TourPlacement(j1,j2);
    }
}
