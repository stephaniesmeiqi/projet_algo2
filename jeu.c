// jeu.c
#include "jeu.h"
#include <stdlib.h>
#include <stdio.h>

Noeud* creerNoeud(int x, int y) {
    Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
    noeud->x = x;
    noeud->y = y;
    noeud->estMine = false;
    noeud->revelee = false;
    noeud->drapeau = false;
    noeud->minesAdjacentes = 0;
    noeud->haut = NULL;  
    noeud->bas = NULL; 
    noeud->gauche = NULL;
    noeud->droite = NULL;
    return noeud;
}

Noeud* initialiserArbre(int taille) {
    Noeud *racine = creerNoeud(0, 0);
    Noeud *ligneCourante = racine;

    for (int i = 0; i < taille; i++) {
        Noeud *courant = ligneCourante;
        for (int j = 0; j < taille; j++) {
            if (j < taille - 1) {
                courant->droite = creerNoeud(i, j + 1);
                courant->droite->gauche = courant;
                courant = courant->droite;
            }
        }
        if (i < taille - 1) {
            ligneCourante->bas = creerNoeud(i + 1, 0);
            ligneCourante->bas->haut = ligneCourante;
            ligneCourante = ligneCourante->bas;
        }
    }

    return racine;
}

void placerMines(Noeud *racine, int taille, int nombreMines) {
    int placedMines = 0;
    while (placedMines < nombreMines) {
        int x = rand() % taille;
        int y = rand() % taille;
        Noeud *noeud = rechercherNoeud(racine, x, y);
        if (noeud != NULL && !noeud->estMine) {
            noeud->estMine = true;
            placedMines++;
        }
    }
}

void calculerMinesAdjacentes(Noeud *racine) {
    if (racine == NULL) return;

    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            if (!courant->estMine) {
                int count = 0;
                if (courant->haut && courant->haut->estMine) count++;
                if (courant->bas && courant->bas->estMine) count++;
                if (courant->gauche && courant->gauche->estMine) count++;
                if (courant->droite && courant->droite->estMine) count++;
                courant->minesAdjacentes = count;
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
}

void explorerCases(Noeud *noeud) {
    if (noeud == NULL || noeud->revelee || noeud->drapeau) return;

    noeud->revelee = true;

    if (noeud->minesAdjacentes == 0) {
        explorerCases(noeud->haut);
        explorerCases(noeud->bas);
        explorerCases(noeud->gauche);
        explorerCases(noeud->droite);
    }
}

void afficherPlateau(Noeud *racine) {
    if (racine == NULL) return;

    Noeud *ligne = racine;
    printf("   ");
    for (int i = 0; i < GRILLE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    int row = 0;
    while (ligne != NULL) {
        printf("%d  ", row++);
        Noeud *courant = ligne;
        
        while (courant != NULL) {
            if (courant->revelee) {
                if (courant->estMine) {
                    
                } else {
                    printf("%d ", courant->minesAdjacentes);
                }
            } else if (courant->drapeau) {
                printf("D ");
            } else {
                printf("# ");
            }
            courant = courant->droite;
        }
        printf("\n");
        ligne = ligne->bas;
    }
}

Noeud* rechercherNoeud(Noeud *racine, int x, int y) {
    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            if (courant->x == x && courant->y == y) {
                return courant;
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
    return NULL;
}

void retirerDrapeau(Noeud *noeud) {
    if (noeud != NULL && noeud->drapeau) {
        noeud->drapeau = false;
    }
}

void libererArbre(Noeud *racine) {
    if (racine == NULL) return;
    libererArbre(racine->droite);
    libererArbre(racine->bas);
    free(racine);
}

bool verifierVictoire(Noeud *racine) {
    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            // Si une case non-mine n'est pas révélée, le joueur n'a pas encore gagné
            if (!courant->estMine && !courant->revelee) {
                return false;
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
    return true; // Toutes les cases non-mine ont été révélées
}
