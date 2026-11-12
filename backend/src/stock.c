#include <stdio.h>
#include "stock.h"
#include "fichier.h"

/* Quantite actuelle de sacs */
static int quantiteStock = 0;

/* Seuil a partir duquel le stock est considere comme faible */
#define SEUIL_STOCK_FAIBLE 10

/*
 * Initialiser le stock en chargeant
 * les donnees sauvegardees.
 */
void initialiserStock(void)
{
    int quantite;

    if (chargerStock(&quantite))
    {
        quantiteStock = quantite;
        printf("Stock charge : %d sacs disponibles.\n",
               quantiteStock);
    }
    else
    {
        quantiteStock = 0;
        printf("Aucun stock sauvegarde. Stock initialise a 0.\n");

        sauvegarderStock(quantiteStock);
    }
}

/*
 * Ajouter des sacs au stock.
 */
int entreeStock(int quantite)
{
    int ancienneQuantite;

    if (quantite <= 0)
    {
        printf("Erreur : la quantite doit etre positive.\n");
        return 0;
    }

    /* Eviter un depassement de la capacite d'un int */
    if (quantite > 2147483647 - quantiteStock)
    {
        printf("Erreur : quantite trop importante.\n");
        return 0;
    }

    ancienneQuantite = quantiteStock;
    quantiteStock += quantite;

    /* Sauvegarder le nouveau stock */
    if (!sauvegarderStock(quantiteStock))
    {
        quantiteStock = ancienneQuantite;
        printf("Erreur lors de la sauvegarde du stock.\n");
        return 0;
    }

    /* Enregistrer la transaction */
    if (!enregistrerTransaction(
            "ENTREE",
            quantite,
            ancienneQuantite,
            quantiteStock))
    {
        printf("Attention : transaction non enregistree.\n");
        return 0;
    }

    printf("%d sacs ajoutes avec succes.\n", quantite);

    if (stockFaible())
    {
        printf("Attention : le stock de sacs est faible.\n");
    }

    return 1;
}

/*
 * Retirer des sacs du stock.
 */
int sortieStock(int quantite)
{
    int ancienneQuantite;

    if (quantite <= 0)
    {
        printf("Erreur : la quantite doit etre positive.\n");
        return 0;
    }

    /* Verifier la disponibilite des sacs */
    if (quantite > quantiteStock)
    {
        printf("Erreur : stock insuffisant.\n");
        printf("Stock disponible : %d sacs.\n",
               quantiteStock);
        return 0;
    }

    ancienneQuantite = quantiteStock;
    quantiteStock -= quantite;

    /* Sauvegarder le nouveau stock */
    if (!sauvegarderStock(quantiteStock))
    {
        quantiteStock = ancienneQuantite;
        printf("Erreur lors de la sauvegarde du stock.\n");
        return 0;
    }

    /* Enregistrer la transaction */
    if (!enregistrerTransaction(
            "SORTIE",
            quantite,
            ancienneQuantite,
            quantiteStock))
    {
        printf("Attention : transaction non enregistree.\n");
        return 0;
    }

    printf("%d sacs retires avec succes.\n", quantite);

    if (stockFaible())
    {
        printf("Attention : le stock de sacs est faible.\n");
    }

    return 1;
}

/*
 * Afficher le stock disponible.
 */
void afficherStock(void)
{
    printf("\n========== ETAT DU STOCK ==========\n");
    printf("Quantite de sacs disponibles : %d\n",
           quantiteStock);

    if (stockFaible())
    {
        printf("Alerte : stock faible !\n");
    }
    else
    {
        printf("Stock suffisant.\n");
    }

    printf("===================================\n");
}

/*
 * Verifier si le stock est faible.
 */
int stockFaible(void)
{
    return quantiteStock <= SEUIL_STOCK_FAIBLE;
}

/*
 * Retourner la quantite actuelle.
 */
int obtenirQuantiteStock(void)
{
    return quantiteStock;
}
