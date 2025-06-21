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

extern Case plateau[8][3];

Joueur PhaseDeDeplacement(Joueur j1, Joueur j2)
{
    printf("_____ Commencer les deplacement _____\n");
    while(CompterPion(j1) > 3 && CompterPion(j2) > 3){
        if(!UnDeplacementNormal(j1,j2)){
            printf("_____ continuons !!! _____");
            printf("PassonsS a phase finale \n");
            system("PAUSE");
            return j2;
        }
        if(!UnDeplacementNormal(j2,j1)){
            printf("_____ continuons !!! _____");
            printf("Passons a phase finale \n");
            system("PAUSE");
            return j1;
        }
    }
    return;
}


void PhaseDeDeplacementFin(Joueur j1, Joueur j2)
{
    printf("_____ Commencer les derniers deplacement _____\n");
    while(CompterPion(j1) > 2 && CompterPion(j2) > 2){
        if(CompterPion(j1)  == 3){
             UnDeplacementLibreDe(j1,j2);
             if(GameOver(j2))
             system("PAUSE");
        }
        else {
            UnDeplacementNormal(j1,j2);
            if(GameOver(j2))
            system("PAUSE");
        }
        if(CompterPion(j2)  == 3){
            UnDeplacementLibreDe(j2,j1);
            if(GameOver(j1))
            system("PAUSE");
        }
        else{
            UnDeplacementNormal(j2,j1);
            if(GameOver(j1))
            system("PAUSE");
        }
    }
    if(GameOver(j1))
            system("PAUSE");
    if(GameOver(j2))
            system("PAUSE");
}


int UnDeplacementNormal(Joueur j1,Joueur j2)
{
    Point t1,t2;
   // AfficherPlateau();
    rejouer1:
    t1 = PrendrePion(j1);
    //AfficherPlateau();
    t2 = PoserPion(j1,t1);
    if((t2.x == t1.x) && (t2.y == t1.y) ) goto rejouer1;
    if(est_sur_ligne(plateau[t2.x][t2.y])) return;

    if(!ComparerCases(plateau[t1.x][t1.y],plateau[t2.x][t2.y]) && (PionAlignesHorizontal(j1) | PionAlignesVertical(j1))) {
        if(PermissionDeRetirerPion(j2) ){
            RetraitForcePion(j2);
            AfficherPlateau();
            goto fin;
        }
        if(!PermissionDeRetirerPion(j2)){
            RetirerPion(j2);
            AfficherPlateau();
        }
    }
    fin:
    if(CompterPion(j2) == 3){AfficherProtection(); return 0;}
    AfficherPlateau();
    //AfficherProtection();

    return 1;
}


void UnDeplacementLibreDe(Joueur j1, Joueur j2)
{
    Point t1,t2;
    //AfficherPlateau();
    rejouer2:
    t1 = PrendrePionLibre(j1);
    t2 = PoserPionLibre(j1, t1);
    AfficherPlateau();
    if( (t2.x == t1.x) && (t2.y == t1.y) ) goto rejouer2;
    if(est_sur_ligne(plateau[t1.x][t1.y])) return;
    if(!ComparerCases(plateau[t1.x][t1.y],plateau[t2.x][t2.y]) && (PionAlignesHorizontal(j1) | PionAlignesVertical(j1))) {
        if(PermissionDeRetirerPion(j2) ){
            //AfficherPlateau();
            RetraitForcePion(j2);
            goto fin;
        }
        if(!PermissionDeRetirerPion(j2)){
            RetirerPion(j2);
           // AfficherPlateau();}
        }
    }
    fin:
    AfficherProtection();
      //  AfficherPlateau();
}


//void TourDeplacement(Joueur j1, Joueur j2)

