#include <stdio.h>
#include <math.h>

int main() {
    float a = 0, b = 0, c = 0;
    float D = 0;
    printf("Zadejte koeficienty a, b, c oddelene mezerou a stisknete Enter:\n");
    scanf("%f %f %f", &a , &b, &c);

    if (a == 0) {
        printf("Koeficient a je roven 0\n");
        return 0;
    }

    D = b*b-4*a*c;
    if (D < 0) {
        printf("Diskriminant je zaporne cislo: %f\n", D);
        return 0;
    }

    float x1 = (-b + sqrt(D))/(2*a);
    float x2 = (-b - sqrt(D))/(2*a);

    printf("Koreny rovnice jsou %f a %f\n", x1, x2);

    return 0;
}
