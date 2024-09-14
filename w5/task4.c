#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int main() {
    char input1[MAX_SIZE] = "";
    char input2[MAX_SIZE] = "";
    char name[MAX_SIZE] = "";
    int h = 0;
    int w = 0;
    FILE *f = NULL;

    f = fopen("uloha4.txt", "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    fscanf(f, " %99[^= ] = %s", input1, name);
    fscanf(f, " %99[^: ] : %i , %i", input2, &h, &w);

    fclose(f);

    printf("1 pred: %s\n", input1);
    printf("1 po: %s\n", name);
    printf("2 pred: %s\n", input2);
    printf("2 po: %d, %d\n", h, w);

    return 0;
}
