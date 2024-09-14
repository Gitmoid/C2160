// prohodi dve cisla
#include <stdio.h>

void swap(int *p_a, int *p_b) {
    int c = 0;
    c = *p_b;
    *p_b = *p_a;
    *p_a = c;
}

int main() {
    int a = 0, b = 0;
    printf("Dve cislicka oddelena mezerou:\n");
    scanf("%d %d", &a , &b);

    swap(&a, &b);

    printf("%i %i\n", a, b);

    return 0;
}
