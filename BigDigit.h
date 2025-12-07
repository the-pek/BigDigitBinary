//
// Created by the_pek on 16/11/2025.
//

#ifndef _ALGORITHME_BINAIRE_BIGDIGIT_H
#define _ALGORITHME_BINAIRE_BIGDIGIT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 2

typedef struct {
    int *Tdigits;   // Tableau de bits (MSB → LSB)
    int Taille;     // Nombre de bits significatifs
    int Signe;      // +1 positif, -1 négatif, 0 nul
} BigBinary;

//Fonctions phase 1
BigBinary initBigBinary(int taille, int signe);
BigBinary creerBigBinaryDepuisChaine(const char *chaine);
void afficheBigBinary(BigBinary nb);
void libereBigBinary(BigBinary *nb);
BigBinary Addition(BigBinary A, BigBinary B);
BigBinary Soustraction(BigBinary A, BigBinary B);
bool Inferieur(const BigBinary *A, const BigBinary *B);
bool Egal(const BigBinary *A, const BigBinary *B);
//Fonctions phase 2
BigBinary copieBigBinary(const BigBinary *src);
BigBinary shiftLeft(const BigBinary *A, int n);
BigBinary shiftRight(const BigBinary *A, int n);
int bitDeDroite(const BigBinary *A);
void normalize(BigBinary *A);
bool isZero(const BigBinary *A);
bool isEven(const BigBinary *X);

// Nouveau prototype
BigBinary BigBinary_PGCD(const BigBinary *A_in, const BigBinary *B_in);
BigBinary multiplicationEgyptienne(const BigBinary *A, const BigBinary *B);
BigBinary BigBinary_mod(const BigBinary *A, const BigBinary *B);

#endif