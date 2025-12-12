# BigDigitBinary

## Présentation
Ce projet implémente une bibliothèque en **Langage C** dédiée à la manipulation d'entiers de précision arbitraire appelés 
**_BigBinary_**. Contrairement aux types standards du C, limités à 64 bits, cette bibliothèque permet de gérer des 
nombres d'une taille théoriquement illimitée. <br>
Il intègre des algorithmes avancés tels que l'Algorithme Binaire d'Euclide pour le PGCD, la Multiplication Égyptienne, 
et l'Exponentiation Modulaire.

## Phase 1
Cette première phase établit l'infrastructure nécessaire à la manipulation des grands nombres. L'objectif était de dépasser
les limitations des types standards en créant une représentation binaire personnalisée et extensible

### Structures de données
> Pour stocker un entier de précision arbitraire, j'ai utilisé une structure basée sur un tableau dynamique, comme suggéré
dans le sujet. 
> - Stockage Dynamique : Utilisation d'un pointeur int *Tdigits pour allouer uniquement la mémoire nécessaire selon la
taille du nombre. 
> - Convention de Stockage : Les bits sont stockés avec le poids fort en tête (Big Endian) (Tdigits[0] est le MSB), ce 
qui facilite la lecture humaine et l'initialisation depuis des chaînes de caractères. 
> - Méta-données : La structure conserve la Taille (nombre de bits) et le Signe (+1/-1) pour gérer l'arithmétique signée.

### Gestion de la mémoire
> La manipulation de tableaux dynamiques impose une gestion rigoureuse de la mémoire pour éviter les fuites.
> - **Initialisation:** Allocation en fonction de la taille demandée
> - **Libération:** Implémentation d'une fonction qui nettoie le tableau et remet les pointeurs à `null`

### Algorithme Arithmétique
> - L'addition <br>
>  - Parcours des tableaux de la droite `LSB` vers la gauche `MSB`
>  - Gestion d'une variable retenue propagée à chaque étape
>  - Redimensionnement automatique si le résultat dépasse la taille des opérandes
> - La soustraction <br>
>  - Gère le cas `A − B` où `A ≥ B`
>  - Utilise le concept d'emprunt lorsque l'on soustrait un bit `1` à un bit `0`
>  - Normalisation : Une étape critique a été ajoutée pour supprimer les zéros non significatifs en tête du résultat après
     la soustraction
>- Les comparaisons 
>  - Comparaison d'abord sur le signe, puis la taille, et enfin bit par bit

## Phase 2
Cette phase constitue le cœur algorithmique du projet. L'objectif était d'implémenter les opérations **PGCD, Modulo, Exponentiation** 
en respectant une contrainte majeure : **_l'interdiction d'utiliser la division euclidienne classique_**, trop coûteuse ou 
impossible directement sur des grands entiers.

### PGCD : L'Algorithme d'Euclide Binaire
Au lieu de l'algorithme d'Euclide classique qui nécessite des divisions, nous avons i mplémenté l'Algorithme Binaire d'Euclide
> - **Principe:** Il remplace la division par des opérations que l'ordinateur effectue en binaire : des décalages
(divisions par 2) et des soustractions.
> - **Logique implémentée:**
>   - Si A et B sont pairs, on divise les deux par 2
>   - Si l'un est pair et l'autre impair, on divise le pair par 2
>   - Si les deux sont impairs, on soustrait le plus petit au plus grand

### Modulo
Ne pouvant utiliser l'opérateur `%`, l'approche par **soustraction optimisée** a été inspirée de la méthode `Division-free 
mod` décrite dans le sujet.
> - **Méthode:** Au lieu de soustraire `B` à `A` répétitivement, l'algorithme cherche le plus grand multiple de 
B par une puissance de 2 qui rentre dans le reste courant, et le soustrait.
> - **Résultat:** Cela revient à simuler une division euclidienne bit par bit, en utilisant uniquement des décalages 
et des soustractions.

### Multiplication égyptienne
Pour multiplier deux grands nombres binaires, la méthode de la __Multiplication Égyptienne__ a été utilisé
> - **Avantage:** Elle est parfaitement adaptée au binaire car elle ne requiert aucune table de multiplication, juste
des additions et des décalages.
> - **Fonctionnement:** On parcourt les bits du multiplicateur. Si le bit est à 1, on ajoute le multiplicande courant au
résultat. À chaque étape, le multiplicande est doublé.

### Exponentiation Modulaire
La finalité de cette phase est de calculer `A^e mod N`. Comme suggéré dans le sujet, l'algorithme d'exponentiation rapide classique
a été réadapté pour qu'il fonctionne avec la structure de donnée.