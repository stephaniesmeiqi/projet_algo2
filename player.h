#ifndef IA_H
#define IA_H

#include "jeu.h"

typedef struct ArbreDecision {
    int x, y;
    bool estSure;
    struct ArbreDecision *gauche;
    struct ArbreDecision *droite;
} ArbreDecision;

ArbreDecision* construireArbre(Plateau *plateau, int x, int y);
void afficherRecommandations(ArbreDecision *arbre);

#endif
