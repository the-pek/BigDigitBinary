#include "BigDigit.h"

// Crée un BigBinary de taille donnée (tous les bits à 0)
BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);

    for (int i = 0; i < taille; ++i) {
        nb.Tdigits[i] = 0;
    }

    return nb;
}

// Libère la mémoire
void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}

//Affichage
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf("-");
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);
    }
    printf("\n");
}

//Initialisation
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;

    // Compte seulement les caractères valides
    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') nb.Taille++;
    }

    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = +1;
    int index = 0;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            index++;
        }
    }

    // Normalisation obligatoire !
    normalize(&nb);

    return nb;
}