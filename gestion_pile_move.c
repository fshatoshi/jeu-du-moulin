#include "prototype.h"


extern Case plateau[8][3];

#include <stdio.h>
#include <stdlib.h>



void initialiser_pile(Pilequadruplet *pile, int taille_max) {
    pile->elements = (quadruplet*)malloc(taille_max * sizeof(quadruplet));  // Allocation dynamique
    if (pile->elements == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    pile->sommet = -1;
    pile->taille_max = taille_max;
}

int empiler(Pilequadruplet *pile, quadruplet q) {
    if (pile->sommet < pile->taille_max - 1) {
        pile->sommet++;
        pile->elements[pile->sommet].x_arrive = q.x_arrive;
        pile->elements[pile->sommet].x_depart = q.x_depart;
        pile->elements[pile->sommet].y_arrive = q.y_arrive;
        pile->elements[pile->sommet].y_depart = q.y_depart;
        return 1;
    } else {
        printf("Erreur : la pile est pleine\n");
        return 0;
    }
}

quadruplet depiler(Pilequadruplet *pile) {
    if (pile->sommet >= 0) {
        return pile->elements[pile->sommet--];
    } else {
        printf("Erreur : la pile est vide\n");
        quadruplet vide = {0, 0, 0, 0};
        return vide;
    }
}

void liberer_pile(Pilequadruplet *pile) {
    free(pile->elements);  // Libère la mémoire allouée
    pile->elements = NULL;  // Sécurisation
}


void afficher_pile(Pilequadruplet *pile) {
    printf("\n=============================\n");
    printf("Bienvenue dans l'affichage de la pile\n");
    printf("=============================\n");

    if (pile == NULL || pile->elements == NULL) {
        printf("Erreur : La pile n'existe pas ou n'est pas initialisée.\n");
        return;
    }

    if (pile->sommet == -1) {
        printf("La pile est vide.\n");
        return;
    }

    printf("Contenu de la pile (du sommet vers la base) :\n");

    for (int i = pile->sommet; i >= 0; i--) {
        printf("quadruplet %d : (%d, %d, %d, %d)\n",
               i, pile->elements[i].x_depart, pile->elements[i].y_depart,
               pile->elements[i].x_arrive, pile->elements[i].y_arrive);
    }

    printf("=============================\n");
}

