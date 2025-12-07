#include <stdio.h>
#include "BigDigit.h"

int main() {
    BigBinary A = creerBigBinaryDepuisChaine("1100");  // 12
    BigBinary B = creerBigBinaryDepuisChaine("1010");   // 10

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary S = Addition(A,B);
    printf("Addition: A + B = "); afficheBigBinary(S);

    BigBinary D = Soustraction(A,B);
    printf("Soustraction: A - B = "); afficheBigBinary(D);

    printf("Comparaison: ");
    printf(" A == B ? %d\n", Egal(&A,&B));
    printf("A < B ? %d\n", Inferieur(&A,&B));

    BigBinary P = BigBinary_PGCD(&A,&B);
    printf("PGCD: P = "); afficheBigBinary(P);

    BigBinary Me = multiplicationEgyptienne(&A,&B);
    printf("Multiplication Egyptienne A * B = "); afficheBigBinary(Me);

    // CORRIGÉ : le Modulo utilise les pointeurs
    BigBinary Mod = BigBinary_mod(&A,&B);
    printf("Modulo: A mod B = "); afficheBigBinary(Mod);

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&S);
    libereBigBinary(&D);
    libereBigBinary(&P);
    libereBigBinary(&Me);
    libereBigBinary(&Mod);

    return 0;
}