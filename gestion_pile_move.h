#ifndef GESTION_PILE_MOVE_H_INCLUDED
#define GESTION_PILE_MOVE_H_INCLUDED
#define MAX_STACK_SIZE 100

typedef struct {
    quadruplet *elements;  // Pointeur vers le tableau dynamique
    int sommet;
    int taille_max;        // Taille maximale de la pile
} Pilequadruplet;

void initialiser_pile(Pilequadruplet *pile, int taille_max);
quadruplet depiler(Pilequadruplet *pile);
int empiler(Pilequadruplet *pile, quadruplet q);
quadruplet depiler(Pilequadruplet *pile);
void liberer_pile(Pilequadruplet *pile);
void afficher_pile(Pilequadruplet *pile);

#endif // GESTION_PILE_MOVE_H_INCLUDED
