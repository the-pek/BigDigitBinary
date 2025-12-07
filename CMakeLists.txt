cmake_minimum_required(VERSION 4.0)
project(_Algorithme_Binaire C)

set(CMAKE_C_STANDARD 11)

add_executable(_Algorithme_Binaire main.c
        BigDigit.h
        BigDigit.c
        Phase_1.c
        Phase_2.c
        Utilitaires.c
)
