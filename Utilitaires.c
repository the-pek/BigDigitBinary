#include "BigDigit.h"

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
    // A est non-nul : forcer Signe = +1 (pour éviter des inconsistances)
    A->Signe = +1;
}


// test si A == 0 (rapide)
bool isZero(const BigBinary *A) {
    if (A == NULL) return true;
    if (A->Tdigits == NULL || A->Taille == 0) return true;
    // parcourir les digits pour détecter un '1'
    for (int i = 0; i < A->Taille; ++i) {
        if (A->Tdigits[i] == 1) return false;
    }
    // tous zéros
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

// Retourne true si X est pair (y compris 0), false si impair.
// S'appuie sur bitDeDroite() et isZero()
bool isEven(const BigBinary *X) {
    if (isZero(X)) return true;         // 0 est pair
    return bitDeDroite(X) == 0;         // LSB == 0 => pair
}