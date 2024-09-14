#include <stdio.h>
typedef struct {
    float a;
    float b;
    float c;
} vector_3d;

int main() {
    vector_3d v1 = {0.0};
    vector_3d v2 = {0.0};
    vector_3d sum = {0.0};

    printf("Zadejte souradnice prvniho vektoru: ");
    scanf("%f %f %f", &v1.a, &v1.b, &v1.c);
    printf("Zadejte souradnice druheho vektoru: ");
    scanf("%f %f %f", &v2.a, &v2.b, &v2.c);

    sum.a = v1.b*v2.c - v2.b*v1.c;
    sum.b = v1.c*v2.a - v2.c*v1.a;
    sum.c = v1.a*v2.b - v2.a*v1.b;
    printf("Vektorovy soucin: %f %f %f\n", sum.a, sum.b, sum.c);
}
