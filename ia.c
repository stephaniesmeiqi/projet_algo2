#include "ia.h"
#include <stdio.h>

void afficherRecommandationsIA(Noeud *racine) {
    if (racine == NULL) return;

    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            if (!courant->revelee && !courant->drapeau && courant->minesAdjacentes == 0) {
                printf("Case (%d, %d) est sûre.\n", courant->x, courant->y);
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
}
