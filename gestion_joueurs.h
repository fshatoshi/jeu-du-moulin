#ifndef GESTION_JoueurS_H_INCLUDED
#define GESTION_JoueurS_H_INCLUDED

typedef struct st_Joueur
{
    int id;
    char pseudo[20];
    char pion;
}Joueur;

Joueur CreatePlayer();
int ComparerJoueurs(Joueur, Joueur);

#endif // GESTION_JoueurS_H_INCLUDED
