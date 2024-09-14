#include <stdio.h>
#include <math.h>

int main() {
    float a = 0, b = 0, c = 0, d = 0, e = 0;
    int p = 0;
    printf("Zadej, kolik cisel chces secist (max 5): ");
    scanf("%i", &p);
    if (p < 1 || p > 5) {
        printf("Zadej spravny pocet cisel\n");
        return 0;
    }

    printf("Postupne zadej na kazdy radek jedno cislo a stiskni Enter:\n");

    if (p > 0) {
        scanf("%f", &a);
    }
    if (p > 1) {
        scanf("%f", &b);
    }
    if (p > 2) {
        scanf("%f", &c);
    }
    if (p > 3) {
        scanf("%f", &d);
    }
    if (p > 4) {
        scanf("%f", &e);
    }

    float s = a+b+c+d+e;

    printf("\nSoucet cisel je %f \n", s);

    return 0;
}
