#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 100

int main() {
    int count = 0; // Pocet nactenych hodnot
    int i = 0;
    int num[MAX_ITEMS] = {0.0};
    FILE *f = NULL;

    f = fopen("cisla.dat", "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fscanf(f, "%d , ", &num[count]) == 1) {
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

    printf("Pocet cisel: %d\n", count);

    for (i = count-1; i >= 0; i--) {
        printf("%d ", num[i]);
    }

    fclose(f);

    printf("\n");

    return 0;
}
