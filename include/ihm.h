#ifndef IHM_H
#define IHM_H

#include <ncurses.h>
#include "sac.h"

// Cycle de vie ncurses
void ihm_initialiser(void);
void ihm_terminer(void);

// Écrans principaux
void ihm_afficher_tableau_stock(const Stock *stock, int ligne_selectionnee);
void ihm_afficher_message(const char *titre, const char *message, int is_erreur);

// Formulaires et boîtes de dialogue
int  ihm_formulaire_ajouter_sac(Sac *nouveau_sac);
int  ihm_boite_confirmation(const char *question);
void ihm_saisie_texte(const char *invite, char *tampon, int taille_max);
int  ihm_saisie_entier(const char *invite);

#endif
