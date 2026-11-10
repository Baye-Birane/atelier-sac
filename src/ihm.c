#include <string.h>
#include "ihm.h"

void ihm_initialiser(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);   // Normal
        init_pair(2, COLOR_RED, COLOR_BLACK);     // Alerte stock faible
        init_pair(3, COLOR_BLACK, COLOR_CYAN);    // Sélection en surbrillance
    }
}

void ihm_terminer(void) {
    endwin();
}

void ihm_afficher_tableau_stock(const Stock *stock, int ligne_selectionnee) {
    clear();
    mvprintw(1, 2, "================= ATELIER SAC - GESTION DU STOCK =================");
    mvprintw(3, 2, "%-8s %-16s %-12s %-6s %-10s %-10s %-10s",
             "REF", "MODELE", "COULEUR", "TAILLE", "QUANTITE", "SEUIL", "PRIX");
    mvprintw(4, 2, "------------------------------------------------------------------");

    if (stock == NULL || stock->total == 0) {
        mvprintw(6, 2, "Aucun article en stock actuellement.");
    } else {
        for (int i = 0; i < stock->total; i++) {
            // Si la quantité est inférieure ou égale au seuil, on active l'alerte rouge
            if (stock->articles[i].quantite <= stock->articles[i].seuil_alerte) {
                attron(COLOR_PAIR(2) | A_BOLD);
            } else {
                attron(COLOR_PAIR(1));
            }

            if (i == ligne_selectionnee) {
                attron(COLOR_PAIR(3));
            }

            mvprintw(5 + i, 2, "%-8s %-16s %-12s %-6s %-10d %-10d %-10.2f",
                     stock->articles[i].reference,
                     stock->articles[i].modele,
                     stock->articles[i].couleur,
                     stock->articles[i].taille,
                     stock->articles[i].quantite,
                     stock->articles[i].seuil_alerte,
                     stock->articles[i].prix_unitaire);

            attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3) | A_BOLD);
        }
    }

    ihm_afficher_menu_actions();
    refresh();
}

void ihm_afficher_menu_actions(void) {
    mvprintw(LINES - 3, 2, "------------------------------------------------------------------");
    mvprintw(LINES - 2, 2, "[FLECHES HAUT/BAS] Naviguer   |   [Q] Quitter");
}
