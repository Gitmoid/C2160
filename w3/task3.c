#include <stdio.h>
#define SIZE 4

int main() {
    float u[SIZE] = {0.0};
    float v[SIZE] = {0.0};
    float skal = 0;
    int i = 0;

    printf("%i hodnot(y) pro prvni vektor oddelene mezerou: ", SIZE);
    for (i = 0; i < SIZE; i++) {
        scanf("%f", &u[i]);
    }

    printf("%i hodnot(y) pro druhy vektor oddelene mezerou: ", SIZE);
    for (i = 0; i < SIZE; i++) {
        scanf("%f", &v[i]);
    }

    for (i = 0; i < SIZE; i++) {
        skal = skal + u[i] * v[i];
    }

    printf("Skalarni soucin: %f \n", skal);
    return 0;
}
