#include <stdlib.h>
#include <string.h>
#include "sac.h"
#include "ihm.h"

int main(void) {
    // Simulation d'un stock initial pour tester l'IHM
    Stock stock;
    stock.total = 3;
    stock.capacite = 5;
    stock.articles = malloc(stock.capacite * sizeof(Sac));

    // Donnée 1 : stock normal
    strcpy(stock.articles[0].reference, "SAC001");
    strcpy(stock.articles[0].modele, "Sac a dos");
    strcpy(stock.articles[0].couleur, "Noir");
    strcpy(stock.articles[0].taille, "M");
    stock.articles[0].quantite = 25;
    stock.articles[0].seuil_alerte = 5;
    stock.articles[0].prix_unitaire = 30.0;

    // Donnée 2 : ALERTE (quantite <= seuil)
    strcpy(stock.articles[1].reference, "SAC002");
    strcpy(stock.articles[1].modele, "Sac bandouliere");
    strcpy(stock.articles[1].couleur, "Marron");
    strcpy(stock.articles[1].taille, "S");
    stock.articles[1].quantite = 2;
    stock.articles[1].seuil_alerte = 5;
    stock.articles[1].prix_unitaire = 45.0;

    // Donnée 3 : stock normal
    strcpy(stock.articles[2].reference, "SAC003");
    strcpy(stock.articles[2].modele, "Pochette");
    strcpy(stock.articles[2].couleur, "Bleu");
    strcpy(stock.articles[2].taille, "L");
    stock.articles[2].quantite = 14;
    stock.articles[2].seuil_alerte = 4;
    stock.articles[2].prix_unitaire = 20.0;

    ihm_initialiser();

    int selection = 0;
    int ch;

    while (1) {
        ihm_afficher_tableau_stock(&stock, selection);
        ch = getch();

        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == KEY_UP && selection > 0) {
            selection--;
        } else if (ch == KEY_DOWN && selection < stock.total - 1) {
            selection++;
        }
    }

    ihm_terminer();
    free(stock.articles);
    return 0;
}
