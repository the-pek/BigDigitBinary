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

// ----------------- UTILITAIRES Phase 2-----------------

BigBinary copieBigBinary(const BigBinary *src) {
    BigBinary nb;
    nb.Taille = src->Taille;
    nb.Signe = src->Signe;
    if (nb.Taille > 0) {
        nb.Tdigits = malloc(sizeof(int) * nb.Taille);
        for (int i = 0; i < nb.Taille; ++i) nb.Tdigits[i] = src->Tdigits[i];
    } else {
        nb.Tdigits = NULL;
    }
    return nb;
}

void normalize(BigBinary *A) {
    if (A->Taille <= 0 || A->Tdigits == NULL) {
        // représenter zéro
        if (A->Tdigits) free(A->Tdigits);
        A->Tdigits = malloc(sizeof(int));
        A->Tdigits[0] = 0;
        A->Taille = 1;
        A->Signe = 0;
        return;
    }
    int i = 0;
    while (i < A->Taille && A->Tdigits[i] == 0) i++;
    if (i == A->Taille) {
        // tout zéro
        free(A->Tdigits);
        A->Tdigits = malloc(sizeof(int));
        A->Tdigits[0] = 0;
        A->Taille = 1;
        A->Signe = 0;
        return;
    }
    if (i > 0) {
        int newT = A->Taille - i;
        int *newArr = malloc(sizeof(int) * newT);
        for (int j = 0; j < newT; ++j) newArr[j] = A->Tdigits[j + i];
        free(A->Tdigits);
        A->Tdigits = newArr;
        A->Taille = newT;
    }
    // Si on arrive ici, A est non-nul ; garder Signe tel quel (+1 attendu)
}

// test si A == 0 (rapide)
bool isZero(const BigBinary *A) {
    if (A->Signe == 0) return true;
    if (A->Taille == 0 || A->Tdigits == NULL) return true;
    for (int i = 0; i < A->Taille; ++i) if (A->Tdigits[i] == 1) return false;
    return true;
}

BigBinary shiftLeft(const BigBinary *A, int n) {
    if (n <= 0) return copieBigBinary(A);
    if (isZero(A)) return creerBigBinaryDepuisChaine("0");

    BigBinary R;
    R.Taille = A->Taille + n;
    R.Signe = A->Signe;
    R.Tdigits = malloc(sizeof(int) * R.Taille);
    // copier les bits d'origine (MSB..LSB)
    for (int i = 0; i < A->Taille; ++i) R.Tdigits[i] = A->Tdigits[i];
    // ajouter n zéros en fin (poids faible)
    for (int i = 0; i < n; ++i) R.Tdigits[A->Taille + i] = 0;
    // déjà normalisé si A l'était
    return R;
}

// Décalage droit n bits (/ 2^n, arrondi vers 0) : renvoie nouvel BigBinary (alloc)
BigBinary shiftRight(const BigBinary *A, int n) {
    if (n <= 0) return copieBigBinary(A);
    if (isZero(A)) return creerBigBinaryDepuisChaine("0");
    if (n >= A->Taille) return creerBigBinaryDepuisChaine("0");

    BigBinary R;
    R.Taille = A->Taille - n;
    R.Signe = A->Signe;
    R.Tdigits = malloc(sizeof(int) * R.Taille);
    // on copie les MSB jusqu'à taille-n
    for (int i = 0; i < R.Taille; ++i) R.Tdigits[i] = A->Tdigits[i];
    normalize(&R);
    return R;
}

// retourne LSB (bit de droite) (0 ou 1)
int bitDeDroite(const BigBinary *A) {
    if (isZero(A)) return 0;
    return A->Tdigits[A->Taille - 1];
}