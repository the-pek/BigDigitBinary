#include <stdio.h>
#include "BigDigit.h"

int main() {
    BigBinary A = creerBigBinaryDepuisChaine("1011");  // 11
    BigBinary B = creerBigBinaryDepuisChaine("101");   // 5

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary S = Addition(A,B);
    printf("A + B = "); afficheBigBinary(S);

    BigBinary D = Soustraction(A,B);
    printf("A - B = "); afficheBigBinary(D);

    printf("A == B ? %d\n", Egal(A,B));
    printf("A < B ? %d\n", Inferieur(A,B));

    BigBinary P = multiplicationEgyptienne(A,B);
    printf("A * B = "); afficheBigBinary(P);

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&S);
    libereBigBinary(&D);
    libereBigBinary(&P);

    return 0;
}