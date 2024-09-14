#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 1000

typedef struct {
    float x;
    float y;
    float z;
} VECTOR_3D;

typedef struct {
    char type[7];
    int atomic_number;
    char atom_name[5];
    char residue_name[4];
    int residue_num;
    VECTOR_3D coord;
    char element[3];
} MY_PDB;

MY_PDB items[MAX_ITEMS] = {{0}};
int count = 0; // Pocet nactenych hodnot

int openread (char data_in[]) {
    FILE *f = NULL;

    f = fopen(data_in, "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fscanf(f, "%6s%d%4s%3s%d%f%f%f%2s", items[count].type, &items[count].atomic_number, items[count].atom_name, items[count].residue_name, &items[count].residue_num, &items[count].coord.x, &items[count].coord.y, &items[count].coord.z, items[count].element) == 9) {
        if (count >= MAX_ITEMS) {
            if (feof(f) == 0) {
                printf("Velikost pole neni dostatecna!\n");
            }
            break;
        }
        count++;
    }

    if (feof(f) == 0) {
        printf("Chyba pri cteni souboru po nacteni %i zaznamu!\n", count);
        return 1;
    }

    fclose(f);

    return 0;
}

int openwrite (char data_out[]) {
    FILE *g = NULL;
    int i = 0;

    g = fopen(data_out, "w");

    if (g == NULL) {
        printf("Nelze otevrit vystupni soubor!\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        fprintf(g, "%-6s%5d %-4s %3s%6d%12.3f%8.3f%8.3f%24s\n", items[i].type, items[i].atomic_number, items[i].atom_name, items[i].residue_name, items[i].residue_num, items[i].coord.x, items[i].coord.y, items[i].coord.z, items[i].element);
    } // atom_name opravdu netusim, jak mam zarovnat

    fclose(g);

    return 0;
}

int countatoms (void) {
    int i = 0;
    int countH = 0;
    int countC = 0;
    int countN = 0;
    int countO = 0;
    int countS = 0;
    char el = 0;

    for (i = 0; i < count; i++) {
        el = items[i].element[0];
        switch (el) {
            case 'H':
                countH++;
                break;
            case 'C':
                countC++;
                break;
            case 'N':
                countN++;
                break;
            case 'O':
                countO++;
                break;
            case 'S':
                countS++;
                break;
            default:
                // tady bych treba mohl pocitat nezarazene prvky
                break;
        }
    }

    printf("Celkem: %i\nH: %i\nC: %i\nN: %i\nO: %i\nS: %i\n", count, countH, countC, countN, countO, countS);

    return 0;
}

int main() {
    char data_in[] = "crambin_simple.pdb";
    char data_out[] = "crambindata.pdb";

    if (openread(data_in) == 1) return 1;
    if (openwrite(data_out) == 1) return 1;
    countatoms();

    system("kate crambindata.pdb");

    return 0;
}
