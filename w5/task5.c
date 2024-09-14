#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = NULL; // num1 file
    FILE *g = NULL; // num2 file
    FILE *h = NULL; // results file
    int a = 0; // num1
    int b = 0; // num2

    f = fopen("numbers1.dat", "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor 1!\n");
        return 1;
    }


    g = fopen("numbers2.dat", "r");
    if (g == NULL) {
        printf("Nelze otevrit vstupni soubor 2!\n");
        return 1;
    }

    h = fopen("results.dat", "w");

    while (fscanf(f, "%d", &a) == 1 && fscanf(g, "%d", &b) == 1) {
        fprintf(h, a == b ? "identical\n" : "different\n");
    }

    fclose(f);
    fclose(g);
    fclose(h);

    return 0;
}
