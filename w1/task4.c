#include <stdio.h>

int main() {
    char o;
    float a = 0, b = 0, c = 0;
    printf("Zadej cislo operace, kterou chces provest:\t\n"
        "+ = scitani\t\n"
        "- = odcitani\t\n"
        "* = nasobeni\t\n"
        "/ = deleni\n"
    );

    scanf("%c", &o);

    printf("Zadej dve cisla A a B oddelena mezerou:\n");
    scanf("%f %f", &a, &b);

    if (o == '+') {
        c = a + b;
    } else if (o == '-') {
        c = a - b;
    } else if (o == '*') {
        c = a * b;
    } else if (o == '/') {
        if (b != 0) {
            c = a / b;
        } else {
            printf("Nulou delit nelze");
            return 0;
        }
    } else {
        printf("Nebyla zadana platna operace");
        return 0;
    }

    printf("Vysledek operace je %f\n", c);
    return 0;
}
