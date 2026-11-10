#ifndef SAC_H
#define SAC_H

#define MAX_REF 16
#define MAX_STR 32

typedef struct {
    char reference[MAX_REF];
    char modele[MAX_STR];
    char couleur[MAX_STR];
    char taille[4];          // "S", "M", "L", "XL"
    int quantite;
    int seuil_alerte;        // Seuil déclenchant l'alerte stock faible
    double prix_unitaire;
} Sac;

typedef struct {
    Sac *articles;           // Tableau dynamique
    int total;               // Nombre d'articles enregistrés
    int capacite;            // Taille mémoire allouée
} Stock;

#endif
