#ifndef IHM_H
#define IHM_H

#include <ncurses.h>
#include "sac.h"

void ihm_initialiser(void);
void ihm_terminer(void);
void ihm_afficher_tableau_stock(const Stock *stock, int ligne_selectionnee);
void ihm_afficher_menu_actions(void);

#endif
