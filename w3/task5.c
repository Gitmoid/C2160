#include <stdio.h>
#define SIZE 3

int main() {
    float ma[3][3] = {{5.0, 7.0, 9.0}, {-2.0, 4.0, -6.0}, {-2.0, 4.0, -6.0}};
    float mb[3][3] = {{1.0, 4.0, -4.0}, {2.0, 8.0, 5.0}, {2.0, 8.0, 5.0}};
    float mc[3][3] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    int i = 0; // řádky matice A
    int j = 0; // sloupce matice B
    int k = 0; // prvky v matici A a B

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                mc[i][j] = mc[i][j] + ma[i][k] * mb[k][j];
            }
        }
    }

    printf("Vysledek nasobeni matic je:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%f ", mc[i][j]);
        }
        printf("\n");
    }

    return 0;
}
