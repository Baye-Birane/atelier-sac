#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
        init_pair(3, COLOR_BLACK, COLOR_CYAN);    // Sélection courante
        init_pair(4, COLOR_GREEN, COLOR_BLACK);   // Messages de succès
        init_pair(5, COLOR_YELLOW, COLOR_BLUE);   // Fenêtres pop-up
    }
}

void ihm_terminer(void) {
    endwin();
}

void ihm_afficher_tableau_stock(const Stock *stock, int ligne_selectionnee) {
    clear();
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(1, 2, "======================= ATELIER SAC - GESTION DES STOCKS =======================");
    mvprintw(3, 2, "%-8s %-18s %-12s %-6s %-10s %-10s %-10s",
             "REF", "MODELE", "COULEUR", "TAILLE", "QUANTITE", "SEUIL", "PRIX (EUR)");
    mvprintw(4, 2, "--------------------------------------------------------------------------------");
    attroff(A_BOLD);

    if (stock == NULL || stock->total == 0) {
        mvprintw(6, 4, "[!] Aucun sac enregistre dans le stock actuellement.");
    } else {
        for (int i = 0; i < stock->total; i++) {
            int est_alerte = (stock->articles[i].quantite <= stock->articles[i].seuil_alerte);

            if (i == ligne_selectionnee) {
                attron(COLOR_PAIR(3));
            } else if (est_alerte) {
                attron(COLOR_PAIR(2) | A_BOLD);
            } else {
                attron(COLOR_PAIR(1));
            }

            mvprintw(5 + i, 2, "%-8s %-18s %-12s %-6s %-10d %-10d %-10.2f",
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

    // Barre d'instructions en bas d'écran
    attron(A_DIM);
    mvprintw(LINES - 3, 2, "--------------------------------------------------------------------------------");
    attroff(A_DIM);
    mvprintw(LINES - 2, 2, "[HAUT/BAS] Naviguer | [A] Ajouter | [S] Supprimer | [R] Rechercher | [Q] Quitter");
    refresh();
}

void ihm_afficher_message(const char *titre, const char *message, int is_erreur) {
    int h = 7, w = 50;
    int y = (LINES - h) / 2;
    int x = (COLS - w) / 2;

    WINDOW *win = newwin(h, w, y, x);
    box(win, 0, 0);

    wattron(win, A_BOLD | (is_erreur ? COLOR_PAIR(2) : COLOR_PAIR(4)));
    mvwprintw(win, 1, (w - (int)strlen(titre)) / 2, "%s", titre);
    wattroff(win, A_BOLD | COLOR_PAIR(2) | COLOR_PAIR(4));

    mvwprintw(win, 3, (w - (int)strlen(message)) / 2, "%s", message);
    mvwprintw(win, 5, (w - 24) / 2, "[Appuyez sur une touche]");

    wrefresh(win);
    wgetch(win);
    delwin(win);
}

int ihm_boite_confirmation(const char *question) {
    int h = 7, w = 54;
    int y = (LINES - h) / 2;
    int x = (COLS - w) / 2;

    WINDOW *win = newwin(h, w, y, x);
    box(win, 0, 0);

    wattron(win, A_BOLD | COLOR_PAIR(2));
    mvwprintw(win, 1, 4, "CONFIRMATION");
    wattroff(win, A_BOLD | COLOR_PAIR(2));

    mvwprintw(win, 3, 4, "%s", question);
    mvwprintw(win, 5, 4, "[O] Oui / Valider       [N] Non / Annuler");
    wrefresh(win);

    int rep = 0;
    while (1) {
        int ch = wgetch(win);
        if (ch == 'o' || ch == 'O') {
            rep = 1;
            break;
        } else if (ch == 'n' || ch == 'N' || ch == 27) { // 27 = Touche Echap
            rep = 0;
            break;
        }
    }

    delwin(win);
    return rep;
}

void ihm_saisie_texte(const char *invite, char *tampon, int taille_max) {
    int h = 7, w = 45;
    int y = (LINES - h) / 2;
    int x = (COLS - w) / 2;

    WINDOW *win = newwin(h, w, y, x);
    box(win, 0, 0);

    mvwprintw(win, 1, 2, "RECHERCHE / SAISIE");
    mvwprintw(win, 3, 2, "%s :", invite);

    echo();
    curs_set(1);
    wrefresh(win);

    mvwgetnstr(win, 3, (int)strlen(invite) + 4, tampon, taille_max - 1);

    noecho();
    curs_set(0);
    delwin(win);
}

int ihm_formulaire_ajouter_sac(Sac *s) {
    int h = 16, w = 55;
    int y = (LINES - h) / 2;
    int x = (COLS - w) / 2;

    WINDOW *win = newwin(h, w, y, x);
    box(win, 0, 0);

    wattron(win, A_BOLD | COLOR_PAIR(1));
    mvwprintw(win, 1, (w - 24) / 2, "=== AJOUTER UN SAC ===");
    wattroff(win, A_BOLD | COLOR_PAIR(1));

    mvwprintw(win, 3,  4, "Reference (ex: SAC001) :");
    mvwprintw(win, 5,  4, "Modele    (ex: A dos)   :");
    mvwprintw(win, 7,  4, "Couleur   (ex: Noir)    :");
    mvwprintw(win, 9,  4, "Taille    (S/M/L/XL)    :");
    mvwprintw(win, 11, 4, "Quantite initiale       :");
    mvwprintw(win, 12, 4, "Seuil alerte stock      :");
    mvwprintw(win, 13, 4, "Prix unitaire (EUR)     :");

    echo();
    curs_set(1);

    // Saisie référence
    wrefresh(win);
    mvwgetnstr(win, 3, 29, s->reference, MAX_REF - 1);
    if (strlen(s->reference) == 0) {
        noecho();
        curs_set(0);
        delwin(win);
        return 0; // Annulation
    }

    // Saisie modèle
    mvwgetnstr(win, 5, 29, s->modele, MAX_STR - 1);

    // Saisie couleur
    mvwgetnstr(win, 7, 29, s->couleur, MAX_STR - 1);

    // Saisie taille
    mvwgetnstr(win, 9, 29, s->taille, 3);

    // Saisie numérique
    char buffer[32];

    mvwgetnstr(win, 11, 29, buffer, 31);
    s->quantite = atoi(buffer);

    mvwgetnstr(win, 12, 29, buffer, 31);
    s->seuil_alerte = atoi(buffer);

    mvwgetnstr(win, 13, 29, buffer, 31);
    s->prix_unitaire = atof(buffer);

    noecho();
    curs_set(0);
    delwin(win);
    return 1; // Saisie réussie
}
