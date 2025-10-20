#include <stdio.h>
#include "BigDigitOperation.c"

int main() {
    BigBinary A = creerBigBinaryDepuisChaine("1011");  // 11
    BigBinary B = creerBigBinaryDepuisChaine("101");   // 5

    printf("A = "); afficheBigBinary(A);
    printf("B = "); afficheBigBinary(B);

    BigBinary S = Addition(A,B);
    printf("A + B = "); afficheBigBinary(S);

    libereBigBinary(&A);
    libereBigBinary(&B);
    libereBigBinary(&S);
    return 0;
}
