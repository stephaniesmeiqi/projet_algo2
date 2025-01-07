#include "jeu.h"
#include "ia.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main() {
    // Initialisation de la grille et du jeu
    Noeud *racine = initialiserArbre(GRILLE);
    srand(time(NULL));

    placerMines(racine, GRILLE, MINES);
    calculerMinesAdjacentes(racine);
    bool perdu = false;

    // Boucle principale du jeu
    while (!perdu) {
    afficherPlateau(racine);
    printf("Choisissez une action :\n");
    printf("  R x y : Révéler une case\n");
    printf("  F x y : Placer un drapeau\n");
    printf("  U x y : Retirer un drapeau\n");
    printf("  I    : Laisser l'IA jouer un coup\n");
    printf("  Q    : Quitter le jeu\n");

    char action;
    int x, y;
    scanf(" %c", &action);

    if (action == 'Q' || action == 'q') {
        printf("Vous avez quitté le jeu.\n");
        break;
    }

    if (action == 'R' || action == 'F' || action == 'U') {
        scanf("%d %d", &x, &y);
        Noeud *caseChoisie = rechercherNoeud(racine, x, y);

        if (caseChoisie == NULL) {
            printf("Coordonnées invalides. Essayez encore.\n");
            continue;
        }

        switch (action) {
            case 'R': // Révéler une case
                if (caseChoisie->estMine) {
                    printf("BOOM ! Vous avez perdu.\n");
                    perdu = true;
                } else {
                    explorerCases(caseChoisie);
                }
                break;

            case 'F': // Placer un drapeau
                if (!caseChoisie->revelee) {
                    caseChoisie->drapeau = true;
                    printf("Drapeau placé en (%d, %d).\n", x, y);
                } else {
                    printf("Impossible de placer un drapeau sur une case révélée.\n");
                }
                break;

            case 'U': // Retirer un drapeau
                if (caseChoisie->drapeau) {
                    retirerDrapeau(caseChoisie);
                    printf("Drapeau retiré de (%d, %d).\n", x, y);
                } else {
                    printf("Aucun drapeau à retirer en (%d, %d).\n");
                }
                break;
        }

        // Vérifier si le joueur a gagné
        if (verifierVictoire(racine)) {
            afficherPlateau(racine);
            printf("Félicitations, vous avez gagné !\n");
            break;
        }
    } else if (action == 'I') {
        Decision decision = ia_decisionnelle(racine);

        if (decision.action == 'R') {
            printf("Réveler la case (%d, %d).\n", decision.x, decision.y);
        } else if (decision.action == 'F') {
            printf("Placer un drapeau sur la case (%d, %d).\n", decision.x, decision.y);
        } else {
            printf("L'IA ne trouve pas de solution évidente.\n");
        }

        if (verifierVictoire(racine)) {
            afficherPlateau(racine);
            printf("Félicitations, vous avez gagné !\n");
            break;
        }
    } else {
        printf("Action invalide. Essayez encore.\n");
    }
}


    // Libérer les ressources
    libererArbre(racine);
    return 0;
}
