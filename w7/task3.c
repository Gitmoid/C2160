#include <stdio.h>
#include <string.h>
#define SIZE 50

void merge_strings(char *p_s1) {
    char s1[SIZE] = "";
    char s2[7] = "";
    char s3[11] = "";
    int length = 0;

    length = strlen(p_s1);
    printf("Delka retezce: %i\n", length);

    strncpy(s1, p_s1, 4);
    s1[4] = '\0';
    strncpy(s2, &p_s1[9], 6);
    s2[6] = '\0';

    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);

    if (strcmp(s1, s2) == 0) printf("Retezce jsou totozne\n");
    else printf("Retezce jsou rozdilne\n");

    strcpy(s3, s1);
    strcat(s3, s2);

    printf("s3: %s\n", s3);

    length = strlen(s3);
    printf("Delka s3: %i\n", length);
}

int main(int argc, char *argv[]) {
    char string[SIZE] = "";
    if (argc > 1) {
        strcpy(string, argv[1]);
    } else {
        printf("String 1: ");
        scanf("%49s", string);
    }

    printf("Retezec: %s\n", string);

    merge_strings(string);
    return 0;
}
