#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 16


int main() {
    FILE *f = NULL;
    float num[SIZE] = {0.0};
    float num2[SIZE] = {0.0};
    float num3[SIZE] = {0.0};
    float numexp[SIZE] = {0.0};
    float numsin[SIZE] = {0.0};
    float numcos[SIZE] = {0.0};
    char str = 'i';
    char str2[] = "i*i";
    char str3[] = "i*i*i";
    char strexp[] = "exp(i)";
    char strsin[] = "sin(i)";
    char strcos[] = "cos(i)";
    char sep[49] = "-";
    int i = 0;

    for (i = 0; i < SIZE; i++) {
        num[i] = i-5;
        num2[i] = num[i] * num [i];
        num3[i] = num2[i] * num [i];
        numexp[i] = exp(num[i]);
        numsin[i] = sin(num[i]);
        numcos[i] = cos(num[i]);
    }

    for (i = 0; i < 49; i++) {
        sep[i] = '-';
    }

    f = fopen("numbers.txt", "w");

    fprintf(f, "Seznam cisel a souvisejicich matematickych hodnot\n");
    fprintf(f, " %-2c %7s %8s %10s %9s %7s\n",
            str, str2, str3, strexp, strsin, strcos);
    fprintf(f, "%s\n", sep);

    for (i = 0; i < SIZE; i++) {
        fprintf(f, "% -3.0f %7.0f %+8.0f %10.3f %9.6f %+7.4f\n",
                num[i], num2[i], num3[i], numexp[i], numsin[i], numcos[i]);
    }

    fclose(f);
    f = NULL;

    system("kate numbers.txt");

    return 0;
}
