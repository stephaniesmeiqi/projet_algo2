#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>

void initialiserPlateau(Plateau *plateau) {
    for (int i = 0; i < GRILLE; i++) {
        for (int j = 0; j < GRILLE; j++) {
            plateau->grille[i][j].estMine = false;
            plateau->grille[i][j].revelee = false;
            plateau->grille[i][j].drapeau = false;
            plateau->grille[i][j].minesAdjacentes = 0;
        }
    }
    plateau->casesRevelees = 0;
}

void placerMines(Plateau *plateau) {
    int placedMines = 0;
    while (placedMines < MINES) {
        int x = rand() % GRILLE;
        int y = rand() % GRILLE;
        if (!plateau->grille[x][y].estMine) {
            plateau->grille[x][y].estMine = true;
            placedMines++;
        }
    }
}

void calculerMinesAdjacentes(Plateau *plateau) {
    for (int x = 0; x < GRILLE; x++) {
        for (int y = 0; y < GRILLE; y++) {
            if (plateau->grille[x][y].estMine) {
                continue;
            }
            int count = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < GRILLE && ny >= 0 && ny < GRILLE && plateau->grille[nx][ny].estMine) {
                        count++;
                    }
                }
            }
            plateau->grille[x][y].minesAdjacentes = count;
        }
    }
}

void explorerCasesAdjacentes(Plateau *plateau, int x, int y) {
    if (x < 0 || x >= GRILLE || y < 0 || y >= GRILLE || plateau->grille[x][y].revelee || plateau->grille[x][y].drapeau) {
        return;
    }

    plateau->grille[x][y].revelee = true;
    plateau->casesRevelees++;

    if (plateau->grille[x][y].minesAdjacentes == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    explorerCasesAdjacentes(plateau, x + i, y + j);
                }
            }
        }
    }
}

void placerDrapeau(Plateau *plateau, int x, int y) {
    if (!plateau->grille[x][y].revelee) {
        plateau->grille[x][y].drapeau = true;
    }
}

void retirerDrapeau(Plateau *plateau, int x, int y) {
    plateau->grille[x][y].drapeau = false;
}

void afficherPlateau(Plateau *plateau) {
    printf("   ");
    for (int i = 0; i < GRILLE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < GRILLE; i++) {
        printf("%d  ", i);
        for (int j = 0; j < GRILLE; j++) {
            if (plateau->grille[i][j].revelee) {
                if (plateau->grille[i][j].estMine) {
                    printf("M ");
                } else {
                    printf("%d ", plateau->grille[i][j].minesAdjacentes);
                }
            } else if (plateau->grille[i][j].drapeau) {
                printf("D ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }
}
