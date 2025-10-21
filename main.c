#include <stdio.h>
#include "BigDigitOperation.c"

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

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&S);
    libereBigBinary(&D);

    return 0;
}
