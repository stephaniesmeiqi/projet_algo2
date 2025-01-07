#include "ia.h"
#include <stdio.h>

// Fonction pour compter les drapeaux autour d'une case
int compterDrapeaux(Noeud *noeud) {
    int count = 0;
    if (noeud->haut && noeud->haut->drapeau) count++;
    if (noeud->bas && noeud->bas->drapeau) count++;
    if (noeud->gauche && noeud->gauche->drapeau) count++;
    if (noeud->droite && noeud->droite->drapeau) count++;
    return count;
}

// Fonction pour compter les cases non révélées autour d'une case
int compterCasesInconnues(Noeud *noeud) {
    int count = 0;
    if (noeud->haut && !noeud->haut->revelee && !noeud->haut->drapeau) count++;
    if (noeud->bas && !noeud->bas->revelee && !noeud->bas->drapeau) count++;
    if (noeud->gauche && !noeud->gauche->revelee && !noeud->gauche->drapeau) count++;
    if (noeud->droite && !noeud->droite->revelee && !noeud->droite->drapeau) count++;
    return count;
}

// Décision déterministe : trouve une action certaine
Decision ia_deterministe(Noeud *racine) {
    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            if (courant->revelee && courant->minesAdjacentes > 0) {
                int drapeaux = compterDrapeaux(courant);
                int inconnues = compterCasesInconnues(courant);

                // Cas 1 : Toutes les mines sont déjà marquées
                if (drapeaux == courant->minesAdjacentes && inconnues > 0) {
                    if (courant->haut && !courant->haut->revelee && !courant->haut->drapeau) {
                        return (Decision){courant->haut->x, courant->haut->y, 'R'};
                    }
                    if (courant->bas && !courant->bas->revelee && !courant->bas->drapeau) {
                        return (Decision){courant->bas->x, courant->bas->y, 'R'};
                    }
                    if (courant->gauche && !courant->gauche->revelee && !courant->gauche->drapeau) {
                        return (Decision){courant->gauche->x, courant->gauche->y, 'R'};
                    }
                    if (courant->droite && !courant->droite->revelee && !courant->droite->drapeau) {
                        return (Decision){courant->droite->x, courant->droite->y, 'R'};
                    }
                }

                // Cas 2 : Toutes les inconnues sont des mines
                if (drapeaux + inconnues == courant->minesAdjacentes) {
                    if (courant->haut && !courant->haut->revelee && !courant->haut->drapeau) {
                        return (Decision){courant->haut->x, courant->haut->y, 'F'};
                    }
                    if (courant->bas && !courant->bas->revelee && !courant->bas->drapeau) {
                        return (Decision){courant->bas->x, courant->bas->y, 'F'};
                    }
                    if (courant->gauche && !courant->gauche->revelee && !courant->gauche->drapeau) {
                        return (Decision){courant->gauche->x, courant->gauche->y, 'F'};
                    }
                    if (courant->droite && !courant->droite->revelee && !courant->droite->drapeau) {
                        return (Decision){courant->droite->x, courant->droite->y, 'F'};
                    }
                }
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
    return (Decision){-1, -1, 'N'}; 
}

// IA principale
Decision ia_decisionnelle(Noeud *racine) {
    Decision decision = ia_deterministe(racine);
    if (decision.action != 'N') {
        return decision;
    }

    // Si aucune décision déterministe n'est possible, choisir aléatoirement
    Noeud *ligne = racine;
    while (ligne != NULL) {
        Noeud *courant = ligne;
        while (courant != NULL) {
            if (!courant->revelee && !courant->drapeau) {
                return (Decision){courant->x, courant->y, 'R'};
            }
            courant = courant->droite;
        }
        ligne = ligne->bas;
    }
    return (Decision){-1, -1, 'N'}; 
}
