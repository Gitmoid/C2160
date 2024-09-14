#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 100

int main() {
    int count = 0; // Pocet nactenych hodnot
    int i = 0;
    float exp[MAX_ITEMS] = {0.0}; // Pole pro nacteni 1. hodnot
    float the[MAX_ITEMS] = {0.0}; // Pole pro nacteni 2. hodnot
    FILE *f = NULL;

    f = fopen("data1.dat", "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fscanf(f, "%*s %f %f", &exp[count], &the[count]) == 2) {
        count++;
        if (count >= MAX_ITEMS) {
            if (feof(f) == 0) {
                printf("Velikost pole neni dostatecna!\n");
            }
            break;
        }
    }

    if (feof(f) == 0) {
        printf("Chyba pri cteni souboru po nacteni %i zaznamu!\n",
        count);
    }

    fclose(f);

    f = fopen("data1my.dat", "w");

    for (i = count-1; i >= 0; i--) {
        fprintf(f, "%6.2f %6.2f\n", exp[i], the[i]);
    }

    fclose(f);

    system("kate data1my.dat");

    return 0;
}
