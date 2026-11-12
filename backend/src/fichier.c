#include <stdio.h>
#include <time.h>
#include "fichier.h"

/*
 * Charger le stock depuis le fichier stock.txt.
 *
 * Retourne 1 si la lecture reussit, 0 sinon.
 */
int chargerStock(int *quantite)
{
    FILE *fichier;

    if (quantite == NULL)
    {
        return 0;
    }

    fichier = fopen("data/stock.txt", "r");

    if (fichier == NULL)
    {
        return 0;
    }

    if (fscanf(fichier, "%d", quantite) != 1)
    {
        fclose(fichier);
        return 0;
    }

    fclose(fichier);

    if (*quantite < 0)
    {
        return 0;
    }

    return 1;
}

/*
 * Sauvegarder la quantite actuelle dans stock.txt.
 *
 * Retourne 1 si la sauvegarde reussit, 0 sinon.
 */
int sauvegarderStock(int quantite)
{
    FILE *fichier;

    if (quantite < 0)
    {
        return 0;
    }

    fichier = fopen("data/stock.txt", "w");

    if (fichier == NULL)
    {
        perror("Erreur d'ouverture de stock.txt");
        return 0;
    }

    if (fprintf(fichier, "%d\n", quantite) < 0)
    {
        fclose(fichier);
        return 0;
    }

    if (fclose(fichier) != 0)
    {
        return 0;
    }

    return 1;
}

/*
 * Ajouter une transaction dans transactions.txt.
 *
 * Chaque ligne contient :
 * date et heure, type, quantite, stock avant, stock apres.
 */
int enregistrerTransaction(
    const char *type,
    int quantite,
    int avant,
    int apres)
{
    FILE *fichier;
    time_t maintenant;
    struct tm *dateLocale;
    char dateTexte[20];

    if (type == NULL || quantite <= 0 ||
        avant < 0 || apres < 0)
    {
        return 0;
    }

    /* Recuperer la date et l'heure */
    maintenant = time(NULL);
    dateLocale = localtime(&maintenant);

    if (dateLocale == NULL)
    {
        return 0;
    }

    if (strftime(dateTexte, sizeof(dateTexte),
                 "%Y-%m-%d %H:%M:%S",
                 dateLocale) == 0)
    {
        return 0;
    }

    /*
     * Mode "a" : ajouter une ligne a la fin du fichier
     * sans effacer les transactions precedentes.
     */
    fichier = fopen("data/transactions.txt", "a");

    if (fichier == NULL)
    {
        perror("Erreur d'ouverture de transactions.txt");
        return 0;
    }

    if (fprintf(fichier,
                "%s | %s | Quantite : %d | Avant : %d | Apres : %d\n",
                dateTexte,
                type,
                quantite,
                avant,
                apres) < 0)
    {
        fclose(fichier);
        return 0;
    }

    if (fclose(fichier) != 0)
    {
        return 0;
    }

    return 1;
}
