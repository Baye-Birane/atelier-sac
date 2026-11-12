#ifndef FICHIER_H
#define FICHIER_H

/* Charger la quantite de sacs depuis le fichier */
int chargerStock(int *quantite);

/* Sauvegarder la quantite actuelle */
int sauvegarderStock(int quantite);

/* Enregistrer une transaction dans l'historique */
int enregistrerTransaction(
    const char *type,
    int quantite,
    int avant,
    int apres
);

#endif
