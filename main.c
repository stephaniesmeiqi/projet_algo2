#include "jeu.h"
#include "ia.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main() {
    Noeud *racine = initialiserArbre(GRILLE);
    srand(time(NULL));

    placerMines(racine, GRILLE, MINES);
    calculerMinesAdjacentes(racine);

    bool perdu = false;

    while (!perdu) {
        afficherPlateau(racine);
        printf("Choisissez une action (R pour révéler, F pour placer un drapeau, U pour retirer un drapeau, A pour afficher les recommandations, Q pour quitter) : ");
        char action;
        int x, y;
        scanf(" %c", &action);

        if (action == 'Q' || action == 'q') {
            printf("Vous avez quitté le jeu.\n");
            break;
        }

        if (action != 'A') {
            scanf("%d %d", &x, &y);
            Noeud *caseChoisie = rechercherNoeud(racine, x, y);
            if (caseChoisie == NULL) {
                printf("Coordonnées invalides.\n");
                continue;
            }

            switch (action) {
                case 'R':
                    if (caseChoisie->estMine) {
                        printf("Vous avez perdu !\n");
                        perdu = true;
                    } else {
                        explorerCases(caseChoisie);
                    }
                    break;
                case 'F':
                    caseChoisie->drapeau = true;
                    break;
                case 'U':
                    retirerDrapeau(caseChoisie);
                    break;
                default:
                    printf("Action invalide.\n");
            }
        } else {
            afficherRecommandationsIA(racine);
        }
    }

    libererArbre(racine);
    printf("Partie terminée.\n");
    return 0;
}
