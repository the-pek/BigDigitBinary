#include "BigDigit.c"

//Addition
BigBinary Addition(BigBinary A, BigBinary B) {
    int maxSize = (A.Taille > B.Taille ? A.Taille : B.Taille);
    BigBinary res = initBigBinary(maxSize + 1, +1);

    int i = A.Taille - 1;
    int j = B.Taille - 1;
    int k = res.Taille - 1;
    int retenue = 0;

    while (i >= 0 || j >= 0) {
        int bitA = (i >= 0) ? A.Tdigits[i] : 0;
        int bitB = (j >= 0) ? B.Tdigits[j] : 0;

        int somme = bitA + bitB + retenue;
        res.Tdigits[k] = somme % 2;
        retenue = somme / 2;

        i--; j--; k--;
    }

    res.Tdigits[k] = retenue;

    // Normaliser (si le premier bit = 0 inutile)
    if (res.Tdigits[0] == 0) {
        for (int t = 1; t < res.Taille; t++) {
            res.Tdigits[t-1] = res.Tdigits[t];
        }
        res.Taille--;
        res.Tdigits = realloc(res.Tdigits, sizeof(int) * res.Taille);
    }

    return res;
}