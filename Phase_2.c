#include "BigDigit.c"
#include <stdbool.h>
#include "Phase_1.c"

BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    if (BigBinary_isZero(a)) return b;
    if (BigBinary_isZero(b)) return a;

    int k = 0;

    while (BigBinary_isEven(a) && BigBinary_isEven(b)) {
        a = BigBinary_shiftRight(a);
        b = BigBinary_shiftRight(b);
        k++;
    }

    while (BigBinary_isEven(a))
        a = BigBinary_shiftRight(a);

    do {
        while (BigBinary_isEven(b))
            b = BigBinary_shiftRight(b);

        if (BigBinary_compare(a, b) > 0) {
            BigBinary tmp = a;
            a = b;
            b = tmp;
        }

        b = Soustraction(b, a);

    } while (!BigBinary_isZero(b));

    while (k--)
        a = BigBinary_shiftLeft(a);

    return a;
}

BigBinary BigBinary_mod(BigBinary A, BigBinary B) {

}

