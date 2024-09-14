#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LENGTH 100
#define MAX_ITEMS 1000
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

ATOM atoms[MAX_ITEMS] = {0};
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

int create_pdb (char data_out[]) {
    FILE *g = NULL;
    int i = 0;

    g = fopen(data_out, "w");

    if (g == NULL) {
        printf("Nelze otevrit vystupni soubor!\n");
        return 1;
    }

    for (i = 0; i < atoms_count; i++) {
        fprintf(g, "%-6.6s%5d %-4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2.2s%2.2s\n", atoms[i].type, atoms[i].atom_num, atoms[i].atom_name, atoms[i].alt_pos, atoms[i].residue_name, atoms[i].id, atoms[i].residue_num, atoms[i].cres, atoms[i].c_x, atoms[i].c_y, atoms[i].c_z, atoms[i].occ, atoms[i].temp, atoms[i].element, atoms[i].charge);
    }

    fclose(g);

    return 0;
}

void create_pdbs (char folder_out[]) {
    FILE *g = NULL;
    char pdb_residue[8] = "residue_";
    char pdb_ext[4] = ".pdb";
    char pdb_name[30] = "";
    char pdb_out[42] = "";
    int i = 0; // i-ty rezidual
    int j = 0; // j-ty radek souboru

    for (i = 0; i < atoms_count; i++) { // pro kazdy rezidual
        if (i == 0 || atoms[i].residue_num != atoms[i-1].residue_num) {
            strcpy(pdb_out, pdb_residue);
            strcat(pdb_out, pdb_name);
            strcat(pdb_out, pdb_ext);
            g = fopen(pdb_out, "w");
            for (j = i; j < atoms_count; j++) {
            fprintf(g, "%-6.6s%5d %-4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2.2s%2.2s\n", atoms[i].type, atoms[i].atom_num, atoms[i].atom_name, atoms[i].alt_pos, atoms[i].residue_name, atoms[i].id, atoms[i].residue_num, atoms[i].cres, atoms[i].c_x, atoms[i].c_y, atoms[i].c_z, atoms[i].occ, atoms[i].temp, atoms[i].element, atoms[i].charge);
            }
        }
    }



    if (g == NULL) {
        printf("Nelze otevrit vystupni soubor!\n");
        return 1;
    }

    fclose(g);

    return 0;
}

void print_residues() {
    for (int i = 0; i < atoms_count; i++) {
        if (i == 0 || atoms[i].residue_num != atoms[i-1].residue_num) {
            printf("%s %2i  %s %2i\n", atoms[i].residue_name, atoms[i].residue_num, atoms[i].atom_name, atoms[i].atom_num);
        }
    }
}

int main(int argc, char *argv[]) {
    char data_in[PATH_LENGTH] = "";
    char folder_out[PATH_LENGTH] = "";

    if (argc > 2) {
        strcpy(data_in, argv[1]);
        strcpy(data_out, argv[2]);
    } else {
        printf("Zadejte nazev vstupniho a vystupniho souboru.\n");
        return 0;
    }

    if (load_pdb(data_in) == 1) return 1;
    if (openwrite(data_out) == 1) return 1;
    //print_residues();

    return 0;
}
