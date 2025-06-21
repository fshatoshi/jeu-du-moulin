#include <stdio.h>
#include <stdlib.h>

#include "gestion_texte.h"

void regle(){
    char c1='<',c2='>';
    printf("1. Le jeu se deroule en deux temps : la pose puis le mouvement.\n");
    printf("2. Dans un premier temps, les joueurs posent a tour de role chacun de leurs pions sur un point vide intersection \n  du plateau.\n");

    printf("\t> Le premier joueur est defini aleatoirement par la machine.\n");
    printf("\t> Lorsqu'il n'y a plus de pion a poser, les joueurs deplacent leurs pions vers une intersection voisine libre en \t  suivant un chemin prevu. L'objectif est de former des %c%c moulins %c%c ou files de trois pions alignes.\n",c1,c1,c2,c2);

    printf("\t> Lorsque l'un des joueurs forme un moulin, il peut capturer un pion adverse, a condition que celui-ci ne fasse \n\t  pas partie d'un alignement protege.\n");

    printf("3. Une fois sorti du jeu, un pion ne peut plus y rentrer.\n");
    printf("4. Le jeu s'acheve quand un joueur n'a plus que deux pions ou ne peut plus jouer, il est alors le perdant.\n");

    printf("5. Une regle optionnelle permet aux joueurs disposant de trois pions restants de se deplacer librement sur le plateau :   il peut alors se deplacer en sautant ou il veut.\n");
    system("PAUSE");
}
