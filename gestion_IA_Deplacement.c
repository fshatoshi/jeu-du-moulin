#include "prototype.h"

int Min_deplacement(Case plateau[8][3], int profondeur,Joueur machine, Joueur j2);
extern Joueur joueur_vide;
extern Case plateau[8][3];
const int taille = 10000;

Pilequadruplet* mapile;




quadruplet mes_quadruplets[100];

void afficher_mes_quadruplet(int nb) {
    for (int i = 0; i < nb; i++) {
        printf("\n quadruplets %d = (%d, %d, %d, %d)\n", i + 1, mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart, mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive);
    }
}

int generer_quadruplets_possibles_deplacement(Case plateau[8][3], quadruplet mes_quadruplets[]) {
    int nb = 0;
    Doublet a, b;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (!ComparerJoueurs(plateau[i][j].player, joueur_vide)) {
                a = TrouverCaseTupleHorizontal(plateau[i][j]);
                b = TrouverCaseTupleVertical(plateau[i][j]);
                // Vérification et ajout du quadruplet pour le premier tuple de a
                if (CasesVoisines(plateau[i][j], plateau[a.p1.x][a.p1.y]) && CaseVide(plateau[a.p1.x][a.p1.y])) {
                    mes_quadruplets[nb].x_depart = i;
                    mes_quadruplets[nb].y_depart = j;
                    mes_quadruplets[nb].x_arrive = a.p1.x;
                    mes_quadruplets[nb].y_arrive = a.p1.y;
                    nb++; // Incrémentation du compteur de quadruplets
                }

                // Vérification et ajout du quadruplet pour le deuxième tuple de a
                if (CasesVoisines(plateau[i][j], plateau[a.p2.x][a.p2.y]) && CaseVide(plateau[a.p2.x][a.p2.y])) {
                    mes_quadruplets[nb].x_depart = i;
                    mes_quadruplets[nb].y_depart = j;
                    mes_quadruplets[nb].x_arrive = a.p2.x;
                    mes_quadruplets[nb].y_arrive = a.p2.y;
                    nb++;
                }

                // Vérification et ajout des quadruplets pour les tuples de b (vertical)
                if (CasesVoisines(plateau[i][j], plateau[b.p1.x][b.p1.y]) && CaseVide(plateau[b.p1.x][b.p1.y])) {
                    mes_quadruplets[nb].x_depart = i;
                    mes_quadruplets[nb].y_depart = j;
                    mes_quadruplets[nb].x_arrive = b.p1.x;
                    mes_quadruplets[nb].y_arrive = b.p1.y;
                    nb++;
                }

                if (CasesVoisines(plateau[i][j], plateau[b.p2.x][b.p2.y]) && CaseVide(plateau[b.p2.x][b.p2.y])) {
                    mes_quadruplets[nb].x_depart = i;
                    mes_quadruplets[nb].y_depart = j;
                    mes_quadruplets[nb].x_arrive = b.p2.x;
                    mes_quadruplets[nb].y_arrive = b.p2.y;
                    nb++;
                }
            }
        }
    }
    return nb;
}

int Max_deplacement(Case plateau[8][3], int profondeur,Joueur machine, Joueur j2) {
    int nb;
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau,machine,j2);  // Appel à eval_deplacement
    }

    nb = generer_quadruplets_possibles_deplacement(plateau, mes_quadruplets);
    //afficher_mes_quadruplet(nb);  // Affichage des quadruplets générés
    quadruplet q;
    int max = -10000;  // Initialisation du score maximum
    int i, tmp;

    // Parcours de toutes les Case de la matrice
    for (i = 0; i < nb; i++) {

        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, j2) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
            Joueur_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart,j2);
            Joueur_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive,j2);
            empiler(mapile,mes_quadruplets[i]);
            tmp = Min_deplacement(plateau, profondeur - 1,machine,j2);  // Évalue le score après ce quadruplet
            if (tmp > max) {  // Met à jour le meilleur score si nécessaire
                max = tmp;
            }
            q = depiler(mapile);
            Joueur_prendre_pion(q.x_arrive, q.y_arrive,j2);
            Joueur_placer(q.x_depart, q.y_depart,j2);  // Annule le quadruplet simulé
        }
    }
    return max;  // Retourne le meilleur score trouvé
}


int Min_deplacement(Case plateau[8][3], int profondeur,Joueur machine, Joueur j2) {
    int nb;
    quadruplet q;
    if (profondeur == 0 || GameOver(machine) || GameOver(j2)) {
        return evaluate(plateau,machine,j2);  // Appel à eval_deplacement
    }

    nb = generer_quadruplets_possibles_deplacement(plateau, mes_quadruplets);

    int min = 10000;  // Initialisation du score minimum
    int i, tmp;

    // Parcours de toutes les Case de la matrice
    for (i = 0; i < nb; i++) {
        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, machine) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
                // Vérifie si la case est vide
            machine_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart,machine);
            machine_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive,machine);  // Simule un quadruplet du joueur minimisant
            empiler(mapile,mes_quadruplets[i]);
            tmp = Max_deplacement(plateau, profondeur - 1,machine,j2);  // Évalue le score après ce quadruplet
            if (tmp < min) {  // Met à jour le pire score si nécessaire
                min = tmp;
            }
            q = depiler(mapile);
            machine_prendre_pion(q.x_arrive, q.y_arrive,machine);
            machine_placer(q.x_depart, q.y_depart,machine);  // Annule le quadruplet simulé
        }
    }
    return min;  // Retourne le pire score trouvé
}


quadruplet meilleur_quadruplet(Case plateau[][3], Joueur machine, int profondeur) {
    mapile = (Pilequadruplet*)malloc(taille*sizeof(quadruplet));
    initialiser_pile(mapile,taille);
    int my_score = 0;
    int nb_quadruplets = generer_quadruplets_possibles_deplacement(plateau, mes_quadruplets);  // Générer tous les quadruplets possibles
    //afficher_mes_quadruplet(nb_quadruplets);  // Affichage des quadruplets générés
    int meilleur_score = -10000;  // Initialisation du score le plus bas possible
    quadruplet quadruplet_choisi,q;
    quadruplet_choisi.x_depart = -1;
    quadruplet_choisi.y_depart = -1;
    quadruplet_choisi.x_arrive = -1;
    quadruplet_choisi.y_arrive = -1;
    afficher_mes_quadruplet(nb_quadruplets);
    // Parcours de tous les quadruplets possibles
    for (int i = 0; i < nb_quadruplets; i++) {
            generer_quadruplets_possibles_deplacement(plateau,mes_quadruplets);
        // Si la case d'arrivée est vide, simuler le quadruplet
        if (ComparerJoueurs(plateau[mes_quadruplets[i].x_depart][mes_quadruplets[i].y_depart].player, machine) &&
            ComparerJoueurs(plateau[mes_quadruplets[i].x_arrive][mes_quadruplets[i].y_arrive].player, joueur_vide)) {
            // Effectuer le quadruplet
            machine_prendre_pion(mes_quadruplets[i].x_depart, mes_quadruplets[i].y_depart,machine);
            machine_placer(mes_quadruplets[i].x_arrive, mes_quadruplets[i].y_arrive,machine);
            empiler(mapile,mes_quadruplets[i]);
            // Évaluer l'état du jeu après le quadruplet avec Minimax
            int score = Min_deplacement(plateau, profondeur - 1,machine,j2);  // Appel à Min pour le joueur minimisant (l'adversaire)

            // Si le score est meilleur, mettre à jour le meilleur quadruplet
            if (score > meilleur_score) {
                meilleur_score = score;
                quadruplet mine;
                mine = depiler(mapile);

                quadruplet_choisi = mine;  // Enregistrer le quadruplet avec le meilleur score
                empiler(mapile,mine);
            }

            q = depiler(mapile);
            my_score = score;
            // Annuler le quadruplet simulé
            machine_prendre_pion(q.x_arrive, q.y_arrive,machine);
            machine_placer(q.x_depart, q.y_depart,machine);
        }
    }
    printf("\n quadruplets = (%d, %d, %d, %d)\n",quadruplet_choisi.x_depart, quadruplet_choisi.y_depart
           ,quadruplet_choisi.x_arrive,quadruplet_choisi.y_arrive );
    printf("\n\n Le score est : %d\n\n",my_score);
    return quadruplet_choisi;  // Retourner le meilleur quadruplet trouvé
}

void un_deplacement_normal_IA(Joueur machine, Joueur j2) {
    quadruplet q;
    Point p;
    AfficherPlateau();
    //meilleur = meilleur_quadruplet(plateau, machine, 2);
    q = meilleur_quadruplet(plateau, machine, 4);

    p = machine_prendre_pion(q.x_depart, q.y_depart,machine);
    if(est_dans_moulin(machine,p.x,p.y)) LeverProtection(&plateau[p.x][p.y]);
    machine_placer(q.x_arrive, q.y_arrive,machine);
    AfficherPlateau();
    liberer_pile(mapile);
}
