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


Point traduire(char a, char b)
{
    int x1=-1, y1=-1;
    if(a=='A'){
        x1=0;
        if(b=='A') y1=0;
        if(b=='D') y1=1;
        if(b=='G') y1=2;
    }
    if(a=='B'){
        x1=1;
        if(b=='B') y1=0;
        if(b=='D') y1=1;
        if(b=='F') y1=2;
    }
    if(a=='C'){
        x1=2;
        if(b=='C') y1=0;
        if(b=='D') y1=1;
        if(b=='E') y1=2;
    }
    if(a=='D' && b=='A'){x1=3;y1=0;}
    if(a=='D' && b=='B'){x1=3;y1=1;}
    if(a=='D' && b=='C'){x1=3;y1=2;}
    if(a=='D' && b=='E'){x1=4;y1=0;}
    if(a=='D' && b=='F'){x1=4;y1=1;}
    if(a=='D' && b=='G'){x1=4;y1=2;}

     if(a=='E'){
        x1=5;
        if(b=='C') y1=0;
        if(b=='D') y1=1;
        if(b=='E') y1=2;
     }
    if(a=='F'){
        x1=6;
        if(b=='B') y1=0;
        if(b=='D') y1=1;
        if(b=='F') y1=2;
    }
     if(a=='G'){
        x1=7;
        if(b=='A') y1=0;
        if(b=='D') y1=1;
        if(b=='G') y1=2;
    }

    Point t = {x1,y1};

    return t;
}

void InverseTraduire(int x, int y)
{
        if(x==0){
        if(y==0) {plateau[x][y].coord1='A'; plateau[x][y].coord2='A';}
        if(y==1) {plateau[x][y].coord1='A'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='A'; plateau[x][y].coord2='G';}
    }
    if(x==1){
        if(y==0) {plateau[x][y].coord1='B'; plateau[x][y].coord2='B';}
        if(y==1) {plateau[x][y].coord1='B'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='B'; plateau[x][y].coord2='F';}
    }
    if(x==2){
        if(y==0) {plateau[x][y].coord1='C'; plateau[x][y].coord2='C';}
        if(y==1) {plateau[x][y].coord1='C'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='C'; plateau[x][y].coord2='E';}
    }
    if(x==3){
        if(y==0) {plateau[x][y].coord1='D'; plateau[x][y].coord2='A';}
        if(y==1) {plateau[x][y].coord1='D'; plateau[x][y].coord2='B';}
        if(y==2) {plateau[x][y].coord1='D'; plateau[x][y].coord2='C';}
    }
    if(x==4){
        if(y==0) {plateau[x][y].coord1='D'; plateau[x][y].coord2='E';}
        if(y==1) {plateau[x][y].coord1='D'; plateau[x][y].coord2='F';}
        if(y==2) {plateau[x][y].coord1='D'; plateau[x][y].coord2='G';}
    }
    if(x==5){
        if(y==0) {plateau[x][y].coord1='E'; plateau[x][y].coord2='C';}
        if(y==1) {plateau[x][y].coord1='E'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='E'; plateau[x][y].coord2='E';}
    }
    if(x==6){
        if(y==0) {plateau[x][y].coord1='F'; plateau[x][y].coord2='B';}
        if(y==1) {plateau[x][y].coord1='F'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='F'; plateau[x][y].coord2='F';}
    }
    if(x==7){
        if(y==0) {plateau[x][y].coord1='G'; plateau[x][y].coord2='A';}
        if(y==1) {plateau[x][y].coord1='G'; plateau[x][y].coord2='D';}
        if(y==2) {plateau[x][y].coord1='G'; plateau[x][y].coord2='G';}
    }
}
