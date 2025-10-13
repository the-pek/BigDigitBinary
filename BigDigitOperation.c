#include "BigDigit.c"

//Soustraction

BigBinary Soustraction(BigBinary A, BigBinary B) {
    BigBinary res = initBigBinary(A.Taille, +1);

    int i = A.Taille - 1;
    int j = B.Taille - 1;
    int k = res.Taille - 1;
    int emprunt = 0;

    while (i >= 0) {
        int bitA = A.Tdigits[i];
        int bitB = (j >= 0) ? B.Tdigits[j] : 0;

        int diff = bitA - bitB - emprunt;
        if (diff < 0) {
            diff += 2;
            emprunt = 1;
        } else {
            emprunt = 0;
        }

        res.Tdigits[k] = diff;
        i--; j--; k--;
    }

    // Normaliser (supprimer les zéros en tête)
    int shift = 0;
    while (shift < res.Taille-1 && res.Tdigits[shift] == 0) {
        shift++;
    }
    if (shift > 0) {
        for (int t = shift; t < res.Taille; t++) {
            res.Tdigits[t-shift] = res.Tdigits[t];
        }
        res.Taille -= shift;
        res.Tdigits = realloc(res.Tdigits, sizeof(int) * res.Taille);
    }

    return res;
}
