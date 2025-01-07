#ifndef IA_H
#define IA_H

#include "jeu.h"

typedef struct Decision {
    int x, y;
    char action; 
} Decision;

Decision ia_decisionnelle(Noeud *racine);

#endif
