#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

int main() {
    FILE *f = NULL;
    int num1[SIZE] = {0.0};
    int num2[SIZE] = {0.0};
    int i = 0;

    for (i = 0; i < SIZE; i++) {
        num1[i] = i+1;
        num2[i] = num1[i] * num1[i];
    }

    f = fopen("mocniny.dat", "w");

    for (i = 0; i < SIZE; i++) {
        fprintf(f, "%i %i\n", num1[i], num2[i]);
    }

    fclose(f);
    f = fopen("gnuplot.cmd", "w");

    fprintf(f, "plot \"mocniny.dat\" using 1:2\n");
    fprintf(f, "pause -1 \"Hit return\"");

    fclose(f);

    system("gnuplot gnuplot.cmd");

    return 0;
}
