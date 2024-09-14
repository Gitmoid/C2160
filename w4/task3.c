#include <stdio.h>

int main() {
    char string1[20] = "";
    char string2[20] = "";
    char string3[40] = "";
    char gnirts3[40] = "";
    int i = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    printf("Prvni slovo: ");
    scanf("%19s", string1);
    printf("Druhe slovo: ");
    scanf("%19s", string2);

    while (string1[count1] != '\0') {
        count1++;
    }

    while (string2[count2] != '\0') {
        count2++;
    }

    string3[count1] = ' ';

    for (i = 0; i < count1; i++) {
        string3[i] = string1[i];
    }

    for (i = 0; i < count2; i++) {
        string3[i+count1+1] = string2[i];
    }

    while (string3[count3] != '\0') {
        count3++;
    }

    for (i = 0; i < count3; i++) {
        gnirts3[i] = string3[count3-1-i];
    }

    printf("Text retezce: %s\n", string3);
    printf("Text pozpatku: %s\n", gnirts3);

    return 0;
}
