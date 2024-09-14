// Vypocet korenu kvadraticke rovnice
#include <stdio.h>
#include <math.h>

int quad_eq(float a, float b, float c, float *p_x1, float *p_x2) { // z parametru kvadraticke rovnice vypocte koreny a vrati pocet nalezenych korenu
    float D = 0;

    if (a == 0) {
        printf("Koeficient a je roven 0\n");
        return 0;
    }

    D = b*b-4*a*c;
    if (D < 0) {
        printf("Diskriminant je zaporne cislo: %f\n", D);
        return 0;
    }

    *p_x1 = (-b + sqrt(D))/(2*a);
    *p_x2 = (-b - sqrt(D))/(2*a);

    if (D == 0) {
        return 1;
    } else {
        return 2;
    }
}

int main() {
    float a = 0, b = 0, c = 0;
    float x1 = 0, x2 = 0;
    int root = 0;
    printf("Zadejte koeficienty a, b, c oddelene mezerou a stisknete Enter:\n");
    scanf("%f %f %f", &a , &b, &c);

    root = quad_eq(a, b, c, &x1, &x2);

    if (root == 0) {
        printf("Koreny rovnice neexistuji v R\n");
        }
    else if (root == 1) {
        printf("Koren rovnice je %f\n", x1);
    } else {
        printf("Koreny rovnice jsou %f a %f\n", x1, x2);
    }

    return 0;
}
