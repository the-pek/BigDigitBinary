#include "BigDigit.h"

BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    // Cas simples : renvoyer copies profondes
    if (isZero(&A)) return copieBigBinary(&B);
    if (isZero(&B)) return copieBigBinary(&A);

    int k = 0;

    // 1) Extraire facteurs de 2 communs
    while (isEven(&A) && isEven(&B)) {
        BigBinary newA = shiftRight(&A, 1);
        BigBinary newB = shiftRight(&B, 1);

        libereBigBinary(&A);
        libereBigBinary(&B);

        A = newA;
        B = newB;

        k++;
    }

    // 2) Rendre A impair
    while (isEven(&A)) {
        BigBinary newA = shiftRight(&A, 1);
        libereBigBinary(&A);
        A = newA;
    }

    // 3) Boucle principale
    while (!isZero(&B)) {
        // rendre B impair
        while (isEven(&B)) {
            BigBinary newB = shiftRight(&B, 1);
            libereBigBinary(&B);
            B = newB;
        }

        // s'assurer que A <= B, sinon swap A <-> B (avec copies profondes et libérations)
        if (!Inferieur(A, B)) {
            BigBinary tmpA = copieBigBinary(&A);
            BigBinary tmpB = copieBigBinary(&B);
            libereBigBinary(&A);
            libereBigBinary(&B);
            A = tmpB;
            B = tmpA;
        }

        // B = B - A  (B >= A ici)
        BigBinary newB = Soustraction(B, A);
        libereBigBinary(&B);
        B = newB;
    }

    // 4) Remultiplier A par 2^k
    while (k-- > 0) {
        BigBinary newA = shiftLeft(&A, 1);
        libereBigBinary(&A);
        A = newA;
    }

    normalize(&A);
    return A; // caller doit libérer la BigBinary retournée
}


BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    if (isZero(&B)) {
        // modulo par 0 : non défini
        // Par sécurité, retourner A tel quel ou gérer erreur
        return A;
    }
    if (isZero(&A)) {
        return creerBigBinaryDepuisChaine("0");
    }
    if (Inferieur(A, B)) {
        return A; // A < B → A est déjà le reste
    }

    // Boucle principale : tant que A >= B
    while (!Inferieur(A, B)) {

        // temp = B (copie indépendante)
        BigBinary temp = copieBigBinary(&B);

        // Trouver le plus grand multiple 2^k * B <= A
        // C’est-à-dire doubler temp tant qu’il reste <= A
        while (1) {
            BigBinary temp_shift = shiftLeft(&temp, 1); // B * 2

            if (Inferieur(A, temp_shift)) {
                // temp_shift > A → on garde temp comme dernier multiple valide
                libereBigBinary(&temp_shift);
                break;
            }

            // sinon, temp = temp_shift et on continue
            libereBigBinary(&temp);
            temp = temp_shift;
        }

        // A = A - temp
        BigBinary newA = Soustraction(A, temp);
        libereBigBinary(&A);
        A = newA;

        // nettoyage
        libereBigBinary(&temp);

        // Toujours normaliser après une opération qui peut créer des zéros de tête
        normalize(&A);
    }

    return A;   // A est le reste (appelant doit libérer)
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