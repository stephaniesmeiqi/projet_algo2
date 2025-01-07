#ifndef JEU_H
#define JEU_H
#include <stdbool.h>

#define GRILLE 20
#define MINES 20

typedef struct Noeud {
    int x, y;
    bool estMine;
    bool revelee;
    bool drapeau;
    int minesAdjacentes;
    struct Noeud *haut;
    struct Noeud *bas;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud;

Noeud* initialiserArbre(int taille);
void placerMines(Noeud *racine, int taille, int nombreMines);
void calculerMinesAdjacentes(Noeud *racine);
void explorerCases(Noeud *noeud);
void afficherPlateau(Noeud *racine);
Noeud* rechercherNoeud(Noeud *racine, int x, int y);
void retirerDrapeau(Noeud *noeud);
void libererArbre(Noeud *racine);

#endif
