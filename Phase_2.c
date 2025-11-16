#include "BigDigit.h"

BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {

}

BigBinary BigBinary_mod(BigBinary A, BigBinary B) {

}

BigBinary multiplicationEgyptienne(BigBinary A, BigBinary B) {
    // cas rapides
    if (isZero(&A) || isZero(&B)) return creerBigBinaryDepuisChaine("0");

    // résultat initial 0
    BigBinary resultat = creerBigBinaryDepuisChaine("0");
    // copies locales (on va les modifier)
    BigBinary a = copieBigBinary(&A);
    BigBinary b = copieBigBinary(&B);

    // boucle principale : tant que b != 0
    while (!isZero(&b)) {
        if (bitDeDroite(&b) == 1) {
            BigBinary tmp = Addition(resultat, a);
            libereBigBinary(&resultat);
            resultat = tmp;
        }
        // a = a << 1
        BigBinary tmpA = shiftLeft(&a, 1);
        libereBigBinary(&a);
        a = tmpA;

        // b = b >> 1
        BigBinary tmpB = shiftRight(&b, 1);
        libereBigBinary(&b);
        b = tmpB;
    }

    // nettoyage des temporaires
    libereBigBinary(&a);
    libereBigBinary(&b);

    normalize(&resultat);
    return resultat; // caller doit libérer
}