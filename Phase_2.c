#include "BigDigit.h"

BigBinary BigBinary_PGCD(const BigBinary *A_in, const BigBinary *B_in) {

    BigBinary A = copieBigBinary(A_in);
    BigBinary B = copieBigBinary(B_in);

    // Cas simples : renvoyer copies profondes
    // B doit être libéré
    if (isZero(&A)) {
        libereBigBinary(&B); return A;
    }
    // A doit être libéré
    if (isZero(&B)) {
        libereBigBinary(&A); return B;
    }

    int k = 0;

    // Extraire facteurs de 2 communs
    while (isEven(&A) && isEven(&B)) {
        BigBinary newA = shiftRight(&A, 1);
        BigBinary newB = shiftRight(&B, 1);

        libereBigBinary(&A);
        libereBigBinary(&B);

        A = newA;
        B = newB;

        k++;
    }

    // Rendre A impair
    while (isEven(&A)) {
        BigBinary newA = shiftRight(&A, 1);
        libereBigBinary(&A);
        A = newA;
    }

    // Boucle principale
    while (!isZero(&B)) {
        // rendre B impair
        while (isEven(&B)) {
            BigBinary newB = shiftRight(&B, 1);
            libereBigBinary(&B);
            B = newB;
        }

        // s'assurer que A <= B
        if (!Inferieur(&A, &B)) {
            BigBinary tmpA = A; // Swap simple de structure (échange les pointeurs internes)
            A = B;
            B = tmpA;
        }

        // B = B - A  (B >= A ici)
        BigBinary newB = Soustraction(B, A);
        libereBigBinary(&B);
        B = newB;
    }

    // Remultiplier A par 2^k
    while (k-- > 0) {
        BigBinary newA = shiftLeft(&A, 1);
        libereBigBinary(&A);
        A = newA;
    }

    normalize(&A);
    libereBigBinary(&B);

    return A;
}

BigBinary BigBinary_mod(const BigBinary *A_in, const BigBinary *B_in) {

    BigBinary Reste = copieBigBinary(A_in); // Reste (a) commence par A
    BigBinary Diviseur = copieBigBinary(B_in); // Diviseur (b) est B

    // Si A < B, alors A mod B = A
    if (Inferieur(&Reste, &Diviseur)) {
        libereBigBinary(&Diviseur);
        return Reste;
    }

    // Tant que Reste >= Diviseur (B)
    while (!Inferieur(&Reste, &Diviseur)) {

        // Trouver la plus grande puissance de 2 de B, T = B * 2^k, telle que T <= Reste
        BigBinary T = copieBigBinary(&Diviseur);
        BigBinary T_shift = creerBigBinaryDepuisChaine("0");

        // Boucle de recherche du k max: Tant que T * 2 <= Reste
        while (1) {
            T_shift = shiftLeft(&T, 1);

            if (Inferieur(&Reste, &T_shift)) {
                libereBigBinary(&T_shift);
                break;
            }

            libereBigBinary(&T);
            T = T_shift;
        }

        BigBinary NouveauReste = Soustraction(Reste, T);

        libereBigBinary(&Reste);
        libereBigBinary(&T);

        Reste = NouveauReste;
    }
    libereBigBinary(&Diviseur);

    return Reste;
}

BigBinary multiplicationEgyptienne(const BigBinary *A_in, const BigBinary *B_in) {
    BigBinary Resultat = creerBigBinaryDepuisChaine("0");

    // Copies profondes modifiables pour les calculs internes
    BigBinary a = copieBigBinary(A_in);
    BigBinary b = copieBigBinary(B_in);

    // Boucle tant que le multiplicateur (b) > 0
    while (!isZero(&b)) {

        // Test du bit de poids faible (LSB) de b
        if (bitDeDroite(&b) == 1) {
            // Resultat = Resultat + a
            BigBinary NouvelleSomme = Addition(Resultat, a);
            libereBigBinary(&Resultat); // Libérer l'ancien Resultat
            Resultat = NouvelleSomme;
        }

        // a = a * 2 (shift left)
        BigBinary tmpA = shiftLeft(&a, 1); // shiftLeft retourne un BigBinary alloué
        libereBigBinary(&a);
        a = tmpA;

        // b = b / 2 (shift right)
        BigBinary tmpB = shiftRight(&b, 1); // shiftRight retourne un BigBinary alloué
        libereBigBinary(&b);
        b = tmpB;
    }

    libereBigBinary(&a);
    libereBigBinary(&b);

    return Resultat;
}

BigBinary BigBinary_expMod(const BigBinary *M_in, unsigned int e, const BigBinary *N_in) {
    // Reste (résultat final) = 1 (en BigBinary)
    BigBinary Reste = creerBigBinaryDepuisChaine("1");

    // Base courante (M) = M_in mod N_in (M = M mod N)
    BigBinary Base_courante = BigBinary_mod(M_in, N_in);

    // Le modulo N (Diviseur) est une copie
    BigBinary N = copieBigBinary(N_in);

    // Boucle d'Exponentiation Rapide
    while (e > 0) {

        // Si le bit de poids faible de 'e' est 1 (e est impair)
        if (e & 1) {
            // Calculer Reste * Base_courante (via multiplication Egyptienne)
            BigBinary Produit = multiplicationEgyptienne(&Reste, &Base_courante);
            libereBigBinary(&Reste);

            // Appliquer le modulo N
            Reste = BigBinary_mod(&Produit, &N);
            libereBigBinary(&Produit);
        }

        // e = e / 2 (décalage à droite)
        e >>= 1;

        // Base_courante = (Base_courante * Base_courante) mod N

        // Calcule Base_courante * Base_courante (via multiplication Egyptienne)
        BigBinary Carre = multiplicationEgyptienne(&Base_courante, &Base_courante);
        libereBigBinary(&Base_courante);

        // Appliquer le modulo N
        Base_courante = BigBinary_mod(&Carre, &N);
        libereBigBinary(&Carre);
    }

    libereBigBinary(&Base_courante);
    libereBigBinary(&N);

    return Reste;
}