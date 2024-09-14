#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 20

int main() {
    FILE *f = NULL;
    int num1[SIZE] = {0.0};
    int num2[SIZE] = {0.0};
    int i = 0;
    int d = 2; // testovany delitel
    int a = SIZE; // pozadovany pocet prvocisel
    int p = 0; // pocet nalezenych prvocisel
    int n = 2; // testovane cislo
    int isPrime = 1;

    while(p < a) {
        while (d < sqrt(n)+0.1) {
            if (n % d == 0) {
                isPrime = 0;
                break;
            }

            d++;
        }

        if (isPrime == 1) {
            num2[p] = n;
            isPrime = 1;
            p++;
        }

        n++;
        d = 2;
        isPrime = 1;
    }

    for (i = 0; i < SIZE; i++) {
        num1[i] = i+1;
    }

    f = fopen("mocniny.dat", "w");

    for (i = 0; i < SIZE; i++) {
        fprintf(f, "%i %i\n", num1[i], num2[i]);
    }

    fclose(f);
    f = fopen("gnuplot.cmd", "w");

    fprintf(f, "plot \"mocniny.dat\" using 1:2\n");
    fprintf(f, "pause -1 \"Hit return\"");

    fclose(f);

    system("gnuplot gnuplot.cmd");

    return 0;
}
