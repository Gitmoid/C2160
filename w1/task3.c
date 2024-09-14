#include <stdio.h>

int main() {
    int o;
    float a = 0, b = 0, c = 0;
    printf("Zadej cislo operace, kterou chces provest:\t\n"
        "1 = scitani\t\n"
        "2 = odcitani\t\n"
        "3 = nasobeni\t\n"
        "4 = deleni\n"
    );

    scanf("%i", &o);

    printf("Zadej dve cisla A a B oddelena mezerou:\n");
    scanf("%f %f", &a, &b);

    if (o == 1) {
        c = a + b;
    } else if (o == 2) {
        c = a - b;
    } else if (o == 3) {
        c = a * b;
    } else if (o == 4) {
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
