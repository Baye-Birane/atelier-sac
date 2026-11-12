#include <stdio.h>
#include "stock.h"

int main(void)
{
    int choix;
    int quantite;

    initialiserStock();

    do
    {
        printf("\n===== GESTION DES SACS =====\n");
        printf("1. Afficher le stock\n");
        printf("2. Ajouter des sacs\n");
        printf("3. Retirer des sacs\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
        {
            printf("Saisie invalide.\n");
            return 1;
        }

        switch (choix)
        {
            case 1:
                afficherStock();
                break;

            case 2:
                printf("Quantite a ajouter : ");
                if (scanf("%d", &quantite) == 1)
                    entreeStock(quantite);
                break;

            case 3:
                printf("Quantite a retirer : ");
                if (scanf("%d", &quantite) == 1)
                    sortieStock(quantite);
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
