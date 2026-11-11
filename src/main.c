#include <stdlib.h>
#include <string.h>
#include "sac.h"
#include "ihm.h"

int main(void) {
    // Allocation dynamique simulée du stock (respect des exigences techniques)
    Stock stock;
    stock.capacite = 10;
    stock.total = 2;
    stock.articles = malloc(stock.capacite * sizeof(Sac));

    // Donnée initiale 1
    strcpy(stock.articles[0].reference, "SAC001");
    strcpy(stock.articles[0].modele, "Sac a dos cuir");
    strcpy(stock.articles[0].couleur, "Noir");
    strcpy(stock.articles[0].taille, "M");
    stock.articles[0].quantite = 20;
    stock.articles[0].seuil_alerte = 5;
    stock.articles[0].prix_unitaire = 49.90;

    // Donnée initiale 2 (Alerte stock critique)
    strcpy(stock.articles[1].reference, "SAC002");
    strcpy(stock.articles[1].modele, "Pochette bandoul.");
    strcpy(stock.articles[1].couleur, "Cognac");
    strcpy(stock.articles[1].taille, "S");
    stock.articles[1].quantite = 3;
    stock.articles[1].seuil_alerte = 5;
    stock.articles[1].prix_unitaire = 29.00;

    ihm_initialiser();

    int selection = 0;
    int en_cours = 1;

    while (en_cours) {
        ihm_afficher_tableau_stock(&stock, selection);
        int ch = getch();

        switch (ch) {
            case 'q':
            case 'Q':
                en_cours = 0;
                break;

            case KEY_UP:
                if (selection > 0) selection--;
                break;

            case KEY_DOWN:
                if (selection < stock.total - 1) selection++;
                break;

            case 'a':
            case 'A': {
                Sac nouveau;
                if (ihm_formulaire_ajouter_sac(&nouveau)) {
                    if (stock.total < stock.capacite) {
                        stock.articles[stock.total++] = nouveau;
                        ihm_afficher_message("SUCCES", "Le sac a ete ajoute au stock.", 0);
                    } else {
                        ihm_afficher_message("ERREUR", "Memoire du stock saturee !", 1);
                    }
                }
                break;
            }

            case 's':
            case 'S': {
                if (stock.total > 0) {
                    if (ihm_boite_confirmation("Voulez-vous vraiment supprimer cet article ?")) {
                        // Décalage pour simuler la suppression
                        for (int i = selection; i < stock.total - 1; i++) {
                            stock.articles[i] = stock.articles[i + 1];
                        }
                        stock.total--;
                        if (selection >= stock.total && selection > 0) selection--;
                        ihm_afficher_message("INFO", "Article supprime avec succes.", 0);
                    }
                }
                break;
            }

            case 'r':
            case 'R': {
                char recherche[MAX_REF];
                ihm_saisie_texte("Entrez la reference du sac", recherche, MAX_REF);
                int trouve = -1;
                for (int i = 0; i < stock.total; i++) {
                    if (strcmp(stock.articles[i].reference, recherche) == 0) {
                        trouve = i;
                        break;
                    }
                }
                if (trouve != -1) {
                    selection = trouve;
                    ihm_afficher_message("RESULTAT", "Article localise dans le tableau.", 0);
                } else {
                    ihm_afficher_message("NON TROUVE", "Aucun sac avec cette reference.", 1);
                }
                break;
            }
        }
    }

    ihm_terminer();
    free(stock.articles);
    return 0;
}
