#include <stdio.h>

int main() {
    char string[20] = "";
    int i = 0;
    int count = 0;

    printf("Zadejte text: ");

    scanf("%19s", string);

    while (string[count] != '\0') {
        count++;
    }

    printf("Pocet znaku: %i\n", count);
    printf("Cast zadaneho textu: %s\n", string+5);

    string[5] = '\0';

    printf("Zkraceny text: %s\n", string);

    return 0;
}
