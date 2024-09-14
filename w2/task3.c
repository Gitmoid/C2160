#include <stdio.h>
#include <math.h>

int main() {
    int a = 0; // pozadovany pocet prvocisel
    int p = 0; // pocet vypsanych prvocisel
    int n = 2; // testovane cislo
    int i = 2; // testovany delitel
    int isPrime = 1; // podminka

    printf("Zadejte pocet prvocisel: ");
    scanf("%i", &a);

    while(p < a) {
        while (i < sqrt(n)+0.1) {
            if (n % i == 0) {
                isPrime = 0;
                break;
            }

            i++;
        }

        if (isPrime == 1) {
            printf("%i ", n);
            isPrime = 1;
            p++;
        }

        n++;
        i = 2;
        isPrime = 1;
    }

    printf("\n");
    return 0;
}
