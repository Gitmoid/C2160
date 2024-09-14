#include <stdio.h>
#define SIZE 9

int main() {
    int va[SIZE] = {2, 7, 8, 13, 246, 564, 111, 2344, 67998};
    int ve[SIZE] = {0};
    int a = 0;
    int e = 0;

    printf("Vektor: ");
    for (a = 0; a < SIZE; a++) {
        printf("%i ", va[a]);
    }

    for (a = 0; a < SIZE; a++) {
        if (va[a] % 2 == 0) {
            ve[e] = va[a];
            // printf("%i ", va[a]);
            e++;
        }
    }

    printf("\nPocet sudych cisel vektoru: %i", e); // u e++ jsem se asi prepsal

    printf("\nSude hodnoty vektoru: ");
    for (a = 0; a < e; a++) { // chtel jsem si usetrit jeden for cyklus, proto jsem hodnoty vypisoval z "va" a ne az na konci xd
        printf("%i ", ve[a]);
    }

    printf("\n");

    return 0;
}
