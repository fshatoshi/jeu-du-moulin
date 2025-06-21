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
extern Joueur joueur_vide;



int LigneProtegee(Case c1, Case c2, Case c3)
{
    return (c1.etat == protegee && c2.etat == protegee && c3.etat == protegee);
}

int PermissionDeRetirerPion(Joueur jr)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (ComparerJoueurs(plateau[i][j].player, jr)) { // Vérifie si la case appartient au joueur j1
                Doublet a = TrouverCaseTupleHorizontal(plateau[i][j]);
                Doublet b = TrouverCaseTupleVertical(plateau[i][j]);

                // Vérifie si la case n'est pas dans une ligne protégée
                if (!LigneProtegee(plateau[i][j], plateau[a.p1.x][a.p1.y], plateau[a.p2.x][a.p2.y]) &&
                    !LigneProtegee(plateau[i][j], plateau[b.p1.x][b.p1.y], plateau[b.p2.x][b.p2.y])) {
                    return 0; // Une case non protégée a été trouvée
                }
            }
        }
    }
    return 1;
}


int bloque(Joueur j1, Joueur j2)
{
    Quadruplet q;
    int a, bloc = 0;

    // Compter le nombre de pions appartenant à j1
    a = CompterPion(j1);

    // Parcourir toutes les cases du plateau
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            // Vérifier si la case appartient à j1
            if (ComparerJoueurs(j1, plateau[i][j].player)) {
                // Obtenir les voisins de la case
                q = PionsVoisins(i,j);

                // Vérifier si tous les voisins valides sont occupés par j2
                if (
                    (q.p1.x == -1 || !ComparerJoueurs(plateau[q.p1.x][q.p1.y].player, joueur_vide)) &&
                    (q.p2.x == -1 || !ComparerJoueurs(plateau[q.p2.x][q.p2.y].player, joueur_vide)) &&
                    (q.p3.x == -1 || !ComparerJoueurs(plateau[q.p3.x][q.p3.y].player, joueur_vide)) &&
                    (q.p4.x == -1 || !ComparerJoueurs(plateau[q.p4.x][q.p4.y].player, joueur_vide))
                ) {
                    bloc++;
                }
            }
        }
    }

    // Retourner si tous les pions de j1 sont bloqués par j2
    return (a == bloc);
}


int est_ce_occupe_par(Joueur j,Case c)
{
    return ComparerJoueurs(j, c.player);
}


void LeverProtection(Case *c)
{
    Doublet a, b;
    a = TrouverCaseTupleHorizontal(*c);
    b = TrouverCaseTupleVertical(*c);

    // Vérification des cases horizontales
    if (!est_sur_ligne(plateau[a.p1.x][a.p1.y]) &&
        LigneProtegee(*c, plateau[a.p1.x][a.p1.y], plateau[a.p2.x][a.p2.y])) {
        if (!est_sur_ligne(plateau[a.p2.x][a.p2.y]) &&
            LigneProtegee(*c, plateau[a.p1.x][a.p1.y], plateau[a.p2.x][a.p2.y])) {
            plateau[a.p1.x][a.p1.y].etat = non_protegee;
            plateau[a.p2.x][a.p2.y].etat = non_protegee;
        } else {
            plateau[a.p1.x][a.p1.y].etat = non_protegee;
        }
    }

    // Vérification des cases verticales
    if (!est_sur_ligne(plateau[b.p1.x][b.p1.y]) &&
        LigneProtegee(*c, plateau[b.p1.x][b.p1.y], plateau[b.p2.x][b.p2.y])) {
        if (!est_sur_ligne(plateau[b.p2.x][b.p2.y]) &&
            LigneProtegee(*c, plateau[b.p1.x][b.p1.y], plateau[b.p2.x][b.p2.y])) {
            plateau[b.p1.x][b.p1.y].etat = non_protegee;
            plateau[b.p2.x][b.p2.y].etat = non_protegee;
        } else {
            plateau[b.p1.x][b.p1.y].etat = non_protegee;
        }
    }

    // Finalement, mettre à jour l'état de la case c
    c->etat = non_protegee;
}


void AfficherProtection()
{
    printf("\n");
    for(int i =0;i < 8; i++){
        for(int j = 0;j<3;j++){
            if(plateau[i][j].etat == protegee)
                printf("case de coordonnees (%c , %c) est : protegeee\n",plateau[i][j].coord1,plateau[i][j].coord2);
            /*else
                printf("case de coordonnees (%d , %d) est : pas protegeee\n",plateau[i][j].y,plateau[i][j].x); */
        }
    }
}


int est_sur_ligne(Case c)
{
    Doublet a, b;
    a = TrouverCaseTupleHorizontal(c);
    b = TrouverCaseTupleVertical(c);

    if (LigneProtegee(c, plateau[a.p1.x][a.p1.y], plateau[a.p2.x][a.p2.y]) &&
        LigneProtegee(c, plateau[b.p1.x][b.p1.y], plateau[b.p2.x][b.p2.y])) {
        return 1;
    }
    return 0;
}


int est_ce_protege(Case c)
{
    return (c.etat == protegee);
}
