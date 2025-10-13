#include <stdio.h>
#include "BigDigitOperation.c"

int main() {
    BigBinary A = creerBigBinaryDepuisChaine("1011");  // 11
    BigBinary B = creerBigBinaryDepuisChaine("101");   // 5

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary D = Soustraction(A,B);
    printf("A - B = "); afficheBigBinary(D);

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&D);
    return 0;
}
