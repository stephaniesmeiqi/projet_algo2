#include "jeu.h"
#include "player.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

bool jouerTour(Plateau *plateau) {
    int x, y;
    char action;
    printf("Choisissez une action (R pour reveler, F pour placer un drapeau, U pour retirer un drapeau, A pour afficher les recommandations) et les coordonnees (x y) : ");
    scanf(" %c %d %d", &action, &x, &y);

    if ((action != 'A' && (x < 0 || x >= GRILLE || y < 0 || y >= GRILLE))) {
        printf("Coordonnees invalides.\n");
        return false;
    }

    switch (action) {
        case 'R':
            if (plateau->grille[x][y].estMine) {
                return true;
            }
            explorerCasesAdjacentes(plateau, x, y);
            break;

        case 'F':
            placerDrapeau(plateau, x, y);
            break;

        case 'U':
            retirerDrapeau(plateau, x, y);
            break;

        case 'A': {
            ArbreDecision *arbre = construireArbre(plateau, x, y);
            afficherRecommandations(arbre);
            free(arbre);
            break;
        }

        default:
            printf("Action invalide.\n");
    }
    return false;
}

int main() {
    Plateau plateau;
    bool perdu = false;
    time_t debut;

    srand(time(NULL));
    initialiserPlateau(&plateau);
    placerMines(&plateau);
    calculerMinesAdjacentes(&plateau);
    debut = time(NULL);

    while (!perdu && plateau.casesRevelees < (GRILLE * GRILLE - MINES)) {
        afficherPlateau(&plateau);
        perdu = jouerTour(&plateau);
    }

    if (perdu) {
        printf("Vous avez perdu !\n");
    } else {
        printf("Felicitation, vous avez gagne en %ld secondes !\n", time(NULL) - debut);
    }

    afficherPlateau(&plateau);
    return 0;
}
