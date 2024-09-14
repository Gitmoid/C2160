#include <stdio.h>
#define SIZE 40

int main() {
    int vf[SIZE] = {1, 1}; // vektor pro F sekvenci
    int vd[9] = {0}; // pocet delitelnych
    int i = 2; // zacatek F
    int j = 0; // zjisteni deleni
    int k = 2; // delitel
    int n = SIZE; // nedelitelna cisla
    int isDiv = 0;

    printf("Fibonacciho posloupnost (%i): 1 1 ", SIZE);

    for (i = 2; i < SIZE; i++) {
        vf[i] = vf[i-2] + vf[i-1];
        printf("%i ", vf[i]);
    }

    for (j = 0; j < SIZE; j++) {
        for (k = 2; k <= 10; k++) {
            if (vf[j] % k == 0) {
                vd[k-2]++;
                isDiv = 1;
            }
        }

        if (isDiv == 1) {
            n--;
            isDiv = 0;
        }
    }

    printf("\nPocty delitelnych cisel: ");

    for (k = 2; k <= 10; k++) {
        printf("%i ", vd[k-2]);
    }

    printf("\nPocet nedelitelnych cisel: %i\n", n);

    return 0;
}
