#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 2

typedef struct {
    int *Tdigits;   // Tableau de bits (MSB → LSB)
    int Taille;     // Nombre de bits significatifs
    int Signe;      // +1 positif, -1 négatif, 0 nul
} BigBinary;

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
    int tousZeros = 1;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    if (tousZeros) nb.Signe = 0;
    return nb;
}

BigBinary BigBinary_shiftRight(BigBinary a) {
    if (a.length == 1) {
        a.bits[0] = 0;
        return a;
    }

    for (int i = 0; i < a.length - 1; i++) {
        a.bits[i] = a.bits[i + 1];
    }
    a.length--;
    return a;
}

BigBinary BigBinary_shiftLeft(BigBinary a) {
    a.bits = realloc(a.bits, (a.length + 1) * sizeof(int));
    for (int i = a.length; i > 0; i--) {
        a.bits[i] = a.bits[i - 1];
    }
    a.bits[0] = 0;
    a.length++;
    return a;
}