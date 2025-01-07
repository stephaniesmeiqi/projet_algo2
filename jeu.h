#ifndef JEU_H
#define JEU_H

#include <stdbool.h>

#define GRILLE 10
#define MINES 20

typedef struct {
    bool estMine;
    bool revelee;
    bool drapeau;
    int minesAdjacentes;
} Case;

typedef struct {
    Case grille[GRILLE][GRILLE];
    int casesRevelees;
} Plateau;

void initialiserPlateau(Plateau *plateau);
void placerMines(Plateau *plateau);
void calculerMinesAdjacentes(Plateau *plateau);
void explorerCasesAdjacentes(Plateau *plateau, int x, int y);
void placerDrapeau(Plateau *plateau, int x, int y);
void retirerDrapeau(Plateau *plateau, int x, int y);
void afficherPlateau(Plateau *plateau);

#endif



