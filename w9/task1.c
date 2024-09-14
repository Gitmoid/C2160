#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LENGTH 100
#define MAX_ITEMS 2000
#define BUF_SIZE 100

typedef struct {
    char type[7];
    int atom_num;
    char atom_name[5];
    char alt_pos;
    char residue_name[4];
    char id;
    int residue_num;
    char cres;
    float c_x, c_y, c_z;
    float occ, temp;
    char element[3];
    char charge[3];
} ATOM;

typedef struct {
    int residue_num;
    char residue_name[4];
    int first_atom;
    int last_atom;
} RESIDUE;

ATOM atoms[MAX_ITEMS] = {0};
RESIDUE residues[MAX_ITEMS] = {0};
int atoms_count = 0; // Pocet nactenych hodnot

void load_str(char *buf, int start, int length, char *target) { // nacte a ulozi string
    strncpy(target, buf + start, length);
    target[length] = '\0';
}

void load_int(char *buf, int start, int length, int *target) { // nacte a ulozi int
    char s[30] = "";
    load_str(buf, start, length, s);
    sscanf(s, "%d", target);
}

void load_float(char *buf, int start, int length, float *target) { // nacte a ulozi float
    char s[30] = "";
    load_str(buf, start, length, s);
    sscanf(s, "%f", target);
}

int load_pdb (char data_in[]) {
    char buf[BUF_SIZE] = "";
    FILE *f = NULL;

    f = fopen(data_in, "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fgets(buf, BUF_SIZE, f) != NULL) {
        if (strncmp(buf, "ATOM", 4) == 0 ||
            strncmp(buf, "HETATM", 6) == 0) {
            load_str(buf, 0, 6, atoms[atoms_count].type);
            load_int(buf, 6, 5, &atoms[atoms_count].atom_num);
            load_str(buf, 12, 4, atoms[atoms_count].atom_name);
            atoms[atoms_count].alt_pos = buf[16];
            load_str(buf, 17, 3, atoms[atoms_count].residue_name);
            atoms[atoms_count].id = buf[21];
            load_int(buf, 22, 4, &atoms[atoms_count].residue_num);
            atoms[atoms_count].cres = buf[26];
            load_float(buf, 30, 8, &atoms[atoms_count].c_x);
            load_float(buf, 38, 8, &atoms[atoms_count].c_y);
            load_float(buf, 46, 8, &atoms[atoms_count].c_z);
            load_float(buf, 54, 6, &atoms[atoms_count].occ);
            load_float(buf, 60, 6, &atoms[atoms_count].temp);
            load_str(buf, 76, 2, atoms[atoms_count].element);
            load_str(buf, 78, 2, atoms[atoms_count].charge);
        }

        if (atoms_count >= MAX_ITEMS) {
            if (feof(f) == 0) {
                printf("Velikost pole neni dostatecna!\n");
            }
            break;
        }
        atoms_count++;
        memset(buf, '\0', BUF_SIZE);
    }

    if (feof(f) == 0) {
        printf("Chyba pri cteni souboru po nacteni %i zaznamu!\n", atoms_count);
        return 1;
    }

    fclose(f);

    return 0;
}

void print_residue_atoms() {
    int j = 0; // prvni atom
    int k = 0; // k-te reziduum

    for (int i = 0; i < atoms_count; i++) {
        if (i == 0 || atoms[i].residue_num != atoms[i-1].residue_num) {
            if (i != 0) {
                residues[k].last_atom = i-1;
                k++;
            }
            residues[k].first_atom = j;
            residues[k].residue_num = atoms[i].residue_num;
            strcpy(residues[k].residue_name, atoms[i].residue_name);
        }
        if (i == atoms_count - 1) {
            residues[k].last_atom = i;
        }

        j = i+1;
    }

    for (int i = 0; i <= k; i++) {
        printf("Residuum: %d %s, atomy: %d - %d\n", residues[i].residue_num, residues[i].residue_name, residues[i].first_atom, residues[i].last_atom);
    }
}


int main(int argc, char *argv[]) {
    char data_in[PATH_LENGTH] = "";

    if (argc > 1) {
        strcpy(data_in, argv[1]);
    } else {
        printf("Zadejte nazev vstupniho souboru.\n");
        return 0;
    }

    if (load_pdb(data_in) == 1) return 1;
    print_residue_atoms();

    return 0;
}
