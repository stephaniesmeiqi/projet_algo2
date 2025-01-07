#include "player.h"
#include <stdlib.h>
#include <stdio.h>

ArbreDecision* construireArbre(Plateau *plateau, int x, int y) {
    // Vérifier les limites et les conditions de terminaison
    if (x < 0 || x >= GRILLE || y < 0 || y >= GRILLE || plateau->grille[x][y].revelee) {
        return NULL;
    }

    ArbreDecision *noeud = (ArbreDecision *)malloc(sizeof(ArbreDecision));
    noeud->x = x;
    noeud->y = y;

    // Une case est sûre si elle n'est pas une mine et qu'elle n'est pas marquée
    noeud->estSure = !plateau->grille[x][y].estMine && !plateau->grille[x][y].drapeau;

    noeud->gauche = NULL;
    noeud->droite = NULL;

    // Si la case n'a pas de mines adjacentes, explorer les voisins
    if (plateau->grille[x][y].minesAdjacentes == 0 && !plateau->grille[x][y].revelee) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    ArbreDecision *nouveauNoeud = construireArbre(plateau, x + i, y + j);
                    if (noeud->gauche == NULL) {
                        noeud->gauche = nouveauNoeud;
                    } else if (noeud->droite == NULL) {
                        noeud->droite = nouveauNoeud;
                    }
                }
            }
        }
    }

    return noeud;
}


void afficherRecommandations(ArbreDecision *arbre) {
    if (arbre == NULL) {
        return;
    }

    if (arbre->estSure) {
        printf("Case (%d, %d) est sûre.\n", arbre->x, arbre->y);
    }

    afficherRecommandations(arbre->gauche);
    afficherRecommandations(arbre->droite);
}
