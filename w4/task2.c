#include <stdio.h>

int main() {
    char string[20] = "";
    char gnirts[20] = "";
    int i = 0;
    int count = 0;

    printf("Zadejte text: ");

    scanf("%19s", string);

    while (string[count] != '\0') {
        count++;
    }

    for (i = 0; i < count; i++) {
        gnirts[i] = string[count-1-i];
    }

    printf("Text pozpatku: %s\n", gnirts);

    return 0;
}
