#include <stdio.h>

int main() {
    float u[3] = {0.0};
    float v[3] = {0.0};
    float uv[3] = {0.0};

    printf("Zadejte souradnice prvniho vektoru: ");
    scanf("%f %f %f", &u[0], &u[1], &u[2]);

    printf("Zadejte souradnice druheho vektoru: ");
    scanf("%f %f %f", &v[0], &v[1], &v[2]);

    uv[0] = u[1] * v[2] - v[1] * u[2];
    uv[1] = u[2] * v[0] - v[2] * u[0];
    uv[2] = u[0] * v[1] - v[0] * u[1];

    printf("Soucin vektoru: %f, %f, %f\n", uv[0], uv[1], uv[2]);
    return 0;
}
