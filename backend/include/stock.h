#ifndef STOCK_H
#define STOCK_H

/* Initialiser le stock en chargeant les donnees sauvegardees */
void initialiserStock(void);

/* Ajouter des sacs au stock */
int entreeStock(int quantite);

/* Retirer des sacs du stock */
int sortieStock(int quantite);

/* Afficher la quantite disponible */
void afficherStock(void);

/* Verifier si le stock est faible */
int stockFaible(void);

/* Obtenir la quantite actuelle */
int obtenirQuantiteStock(void);

#endif
