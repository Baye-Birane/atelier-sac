#ifndef IHM_H
#define IHM_H

#include <ncurses.h>
#include "sac.h"

// Initialisation et fermeture
void ihm_initialiser(void);
void ihm_terminer(void);

// Écran principal avec gestion du défilement
void ihm_afficher_tableau_stock(const Stock *stock, int ligne_selectionnee, int premier_affiche);
void ihm_afficher_message(const char *titre, const char *message, int is_erreur);

// Boîtes de dialogue et formulaires
int  ihm_formulaire_ajouter_sac(Sac *nouveau_sac);
int  ihm_boite_confirmation(const char *question);
void ihm_saisie_texte(const char *invite, char *tampon, int taille_max);

#endif
