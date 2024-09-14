#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 50
typedef struct {
    char str[5];
    float energy_exp;
    float energy_calc;
} ENERGY_ITEM;

ENERGY_ITEM items[MAX_ITEMS] = {{0}};
int count = 0; // Pocet nactenych hodnot

int openread (char data_in[]) {
    FILE *f = NULL;

    f = fopen(data_in, "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fscanf(f, "%4s %f %f", items[count].str, &items[count].energy_exp, &items[count].energy_calc) == 3) {
        if (count >= MAX_ITEMS) {
            if (feof(f) == 0) {
                printf("Velikost pole neni dostatecna!\n");
            }
            break;
        }
        count++;
    }

    if (feof(f) == 0) {
        printf("Chyba pri cteni souboru po nacteni %i zaznamu!\n", count);
        return 1;
    }

    fclose(f);

    return 0;
}

int openwrite (char data_out[]) {
    FILE *g = NULL;
    int i = 1;

    g = fopen(data_out, "w");

    if (g == NULL) {
        printf("Nelze otevrit vystupni soubor!\n");
        return 1;
    }

    for (i = count-1; i >= 0; i--) {
        fprintf(g, "%s %6.2f %6.2f\n", items[i].str, items[i].energy_exp, items[i].energy_calc);
    }

    fclose(g);

    return 0;
}

int main() {
    char data_in[] = "data1.dat";
    char data_out[] = "data1my.dat";

    if (openread(data_in) == 1) return 1;
    if (openwrite(data_out) == 1) return 1;

    system("kate data1my.dat");

    return 0;
}
