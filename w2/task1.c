#include <stdio.h>

int main() {
    int a = 1; // podminka pro vypsani cisel
    int n = 0; // pocet vypsanych cisel

    printf("Zadejte cislo: ");
    scanf("%i", &n);

    while(a <= n) {
        printf("%i ", a);
        a++;
    }

    return 0;
}
