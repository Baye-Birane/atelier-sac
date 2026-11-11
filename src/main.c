#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sac.h"
#include "ihm.h"

int main(void) {
    Stock stock;
    stock.capacite = 50;
    stock.total = 12;
    stock.articles = malloc(stock.capacite * sizeof(Sac));

    for (int i = 0; i < stock.total; i++) {
        snprintf(stock.articles[i].reference, MAX_REF, "SAC%03d", i + 1);
        snprintf(stock.articles[i].modele, MAX_STR, "Modele %d", i + 1);
        strcpy(stock.articles[i].couleur, (i % 2 == 0) ? "Noir" : "Marron");
        strcpy(stock.articles[i].taille, (i % 3 == 0) ? "L" : "M");
        stock.articles[i].quantite = (i % 4 == 0) ? 2 : 18;
        stock.articles[i].seuil_alerte = 5;
        stock.articles[i].prix_unitaire = 35.0 + (i * 3.0);
    }

    ihm_initialiser();

    int selection = 0;
    int premier_affiche = 0;
    int en_cours = 1;

    while (en_cours) {
        int lignes_visibles = LINES - 9;
        if (lignes_visibles < 1) lignes_visibles = 1;

        if (selection < premier_affiche) {
            premier_affiche = selection;
        } else if (selection >= premier_affiche + lignes_visibles) {
            premier_affiche = selection - lignes_visibles + 1;
        }

        ihm_afficher_tableau_stock(&stock, selection, premier_affiche);
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
                        selection = stock.total - 1;
                        ihm_afficher_message("SUCCES", "Le sac a ete ajoute au stock.", 0);
                    } else {
                        ihm_afficher_message("ERREUR", "Memoire du stock saturee !", 1);
                    }
                }
                break;
            }

            case 'm':
            case 'M': {
                if (stock.total > 0) {
                    // Passage par référence du sac sélectionné
                    if (ihm_formulaire_modifier_sac(&stock.articles[selection])) {
                        ihm_afficher_message("SUCCES", "Fiche article mise a jour !", 0);
                    }
                } else {
                    ihm_afficher_message("ERREUR", "Aucun sac a modifier.", 1);
                }
                break;
            }

            case 's':
            case 'S': {
                if (stock.total > 0) {
                    if (ihm_boite_confirmation("Voulez-vous supprimer cet article ?")) {
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
