#include <stdio.h>
#include <math.h>

int main() {
    int n = 0; // testovane cislo
    int i = 2; // testovany delitel
    int isPrime = 1;

    printf("Zadejte cislo: ");
    scanf("%i", &n);

    if (n <= 1) {
        printf("Cislo %i neni prvocislo\n", n);
        return 0;
    }

    while (i < sqrt(n)+0.1) {
        if (n % i == 0) {
            isPrime = 0;
            break;
        }

        i++;
    }

    if (isPrime == 1) {
        printf("Cislo %i je prvocislo\n", n);
    } else {
        printf("Cislo %i neni prvocislo\n", n);
    }

    return 0;
}
