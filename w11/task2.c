#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>

#define PATH_LENGTH 100
#define MAX_ITEMS 5000
#define BUF_SIZE 100
#define RESD_TYPES_COUNT 21

typedef struct {
    char type[7];
    int atom_num;
    char atom_name[5];
    char alt_pos;
    char residue_name[4];
    char id;
    int residue_num;
    char cres;
    float coord_x, coord_y, coord_z;
    float occ, temp;
    char element[3];
    char charge[3];
} ATOM;

typedef struct {
    int residue_num;
    char residue_name[4];
    int first_atom, last_atom;
    double center_x, center_y, center_z;
    int backbone_count;
    int peptide_backbone[100];
    int residue_type;
} RESIDUE;

typedef struct {
    char code3[4];  // three-letter code
    char code1;     // one-letter code
    double color_r;
    double color_g;
    double color_b;
} RESIDUE_TYPE;

RESIDUE_TYPE residue_types[RESD_TYPES_COUNT] =
{
  {"UNK", 'X', 153/255.0, 153/255.0, 153/255.0},
  {"ALA", 'A', 204/255.0, 255/255.0, 255/255.0},
  {"ARG", 'R', 230/255.0,   6/255.0,   6/255.0},
  {"ASN", 'N', 255/255.0, 153/255.0,   0/255.0},
  {"ASP", 'D', 255/255.0, 204/255.0, 153/255.0},
  {"CYS", 'C',   0/255.0, 255/255.0, 255/255.0},
  {"GLN", 'Q', 255/255.0, 102/255.0,   0/255.0},
  {"GLU", 'E', 255/255.0, 204/255.0,   0/255.0},
  {"GLY", 'G',   0/255.0, 255/255.0,   0/255.0},
  {"HIS", 'H', 255/255.0, 255/255.0, 153/255.0},
  {"ILE", 'I',   0/255.0,   0/255.0, 128/255.0},
  {"LEU", 'L',  51/255.0, 102/255.0, 255/255.0},
  {"LYS", 'K', 198/255.0,   6/255.0,   0/255.0},
  {"MET", 'M', 153/255.0, 204/255.0, 255/255.0},
  {"PHE", 'F',   0/255.0, 204/255.0, 255/255.0},
  {"PRO", 'P', 255/255.0, 255/255.0,   0/255.0},
  {"SER", 'S', 204/255.0, 255/255.0, 153/255.0},
  {"THR", 'T',   0/255.0, 255/255.0, 153/255.0},
  {"TRP", 'W', 204/255.0, 153/255.0, 255/255.0},
  {"TYR", 'Y', 204/255.0, 255/255.0, 204/255.0},
  {"VAL", 'V',   0/255.0,   0/255.0, 255/255.0}
};

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
            load_float(buf, 30, 8, &atoms[atoms_count].coord_x);
            load_float(buf, 38, 8, &atoms[atoms_count].coord_y);
            load_float(buf, 46, 8, &atoms[atoms_count].coord_z);
            load_float(buf, 54, 6, &atoms[atoms_count].occ);
            load_float(buf, 60, 6, &atoms[atoms_count].temp);
            load_str(buf, 76, 2, atoms[atoms_count].element);
            load_str(buf, 78, 2, atoms[atoms_count].charge);

            atoms_count++;

            if (atoms_count >= MAX_ITEMS) {
                printf("Velikost pole neni dostatecna!\n");
                break;
            }
        }
        memset(buf, '\0', BUF_SIZE);
    }

    if (feof(f) == 0) {
        printf("Chyba pri cteni souboru po nacteni %i zaznamu!\n", atoms_count);
        return 1;
    }

    fclose(f);

    return 0;
}

int find_residues_range() { // najde pozici prvniho a posledniho atomu rezidui
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
            residues[k].residue_type = 0;
        }
        if (i == atoms_count - 1) {
            residues[k].last_atom = i;
        }

        j = i+1;
    }

    for (int i = 0; i <= k; i++) {
        for (int rt = 0; rt < RESD_TYPES_COUNT; rt++) {
            if (strcmp(residue_types[rt].code3, residues[i].residue_name) == 0) {
                residues[i].residue_type = rt;
                break;
            }
        }
    }

    return k;
}

void print_residues_range() {
    int k = 0;
    k = find_residues_range();

    for (int i = 0; i <= k; i++) {
        printf("Residuum: %d %s, atomy: %d - %d\n", residues[i].residue_num, residues[i].residue_name, residues[i].first_atom, residues[i].last_atom);
    }
}

int calculate_residue_centers() { // geometricky stred atomů rezidui
    int k = 0; // k-te reziduum

    k = find_residues_range(); // pocet rezidui

    for (int i = 0; i <= k; i++) {
        double sumx= 0.0, sumy = 0.0, sumz = 0.0;
        int first = residues[i].first_atom;
        int last = residues[i].last_atom;
        int n = 0; // delitel prumeru

        for (int i = first; i <= last; i++) {
            if (strcmp(atoms[i].element, " H") != 0) {
                sumx += atoms[i].coord_x;
                sumy += atoms[i].coord_y;
                sumz += atoms[i].coord_z;
                n++;
            }
        }

        residues[i].center_x = sumx / n;
        residues[i].center_y = sumy / n;
        residues[i].center_z = sumz / n;
    }

    return k;
}

void print_atoms() {
    int k = 0; // k-te reziduum
    k = find_residues_range(); // pocet rezidui

    for (int i = 0; i <= k; i++) {
        printf("Residuum %d %s, stred: %.2f, %.2f, %.2f\n", residues[i].residue_num, residues[i].residue_name, residues[i].center_x, residues[i].center_y, residues[i].center_z);
    }
}

int find_backbones() {
    int k = 0;
    k = find_residues_range();
    int count = 0; // pocet nalezenych atomu v reziduu
    int j = 0; // j-te reziduum

    for (int i = 0; i <= atoms_count; i++) {
        if (strcmp(atoms[i].atom_name, " N  ") == 0) {
            residues[j].peptide_backbone[count] = atoms[i].atom_num;
            count++;
        } else if (strcmp(atoms[i].atom_name, " CA ") == 0) {
            residues[j].peptide_backbone[count] = atoms[i].atom_num;
            count++;
        } else if (strcmp(atoms[i].atom_name, " C  ") == 0) {
            residues[j].peptide_backbone[count] = atoms[i].atom_num;
            count++;
        } else if (strcmp(atoms[i].atom_name, " O  ") == 0) {
            residues[j].peptide_backbone[count] = atoms[i].atom_num;
            count++;
        }

        if (i == residues[j].last_atom) {
            residues[j].backbone_count = count;
            count = 0;
            j++;
        }
    }

    return k;
}

void print_backbones() {
    int k = 0;
    k = find_backbones();

    for (int i = 0; i <= k; i++) {
        printf("Residuum %d %s, pater: ", residues[i].residue_num, residues[i].residue_name);
        if (residues[i].backbone_count > 0) {
            for (int j = 0; j < residues[i].backbone_count; j++) {
                printf("%i ", residues[i].peptide_backbone[j]);
            }
        }
        printf("\n");
    }
}

void print_residue_types() {
    int k = 0; // k-te reziduum
    k = find_residues_range(); // pocet rezidui

    for (int i = 0; i <= k; i++) {
        printf("Residuum %d %s, typ: %d\n", residues[i].residue_num, residues[i].residue_name, residues[i].residue_type);
    }
}

void draw_colored_arcs() {
    int num_segments = find_residues_range();
    int type_color = 0;

    int win = 0;
    win = g2_open_X11(500, 500);

    double start_angle = 0.0, end_angle = 0.0;

    g2_set_line_width(0, 10);

    for (int i = 0; i < num_segments; i++) {
        start_angle = (360.0/num_segments) * i;
        end_angle = (360.0/num_segments) * (i + 1.0);

        int type_index = residues[i].residue_type;
        type_color = g2_ink(win, residue_types[type_index].color_r, residue_types[type_index].color_g, residue_types[type_index].color_b);

        g2_pen(win, type_color);

        g2_arc(0, 250, 250, 200, 200, start_angle, end_angle);
    }

    getchar(); // Cekame na vstup znaku z klavesnice
    g2_close(win); // Zavreme okno
}

void draw_colored_rectangles() {
    int window_size = 500;
    int segments_row = 30; // segments per row
    int segment_height = 30;
    int segment_width = (window_size - 40) / segments_row;
    int segments_total = find_residues_range() + 1;
    int columns_total = segments_total / segments_row;
    int type_color = 0;
    int x1 = 20;
    int y1 = window_size - 20;
    int y2 = window_size - 40;
    int num_shapes = 0;

    int win = 0;
    win = g2_open_X11(500, 500);

    for (int k = 0; k < columns_total + 1; k++) {
        for (int i = 0; i < segments_row; i++) {
            if (num_shapes == segments_total) break;

            int type_index = residues[num_shapes].residue_type;
            type_color = g2_ink(win, residue_types[type_index].color_r, residue_types[type_index].color_g, residue_types[type_index].color_b);

            g2_pen(win, type_color);
            g2_filled_rectangle(win, x1, y1, x1 + segment_width, y2);

            int center_x = x1 + (segment_width / 2) - 2;
            int center_y = y1 - (segment_height / 2);

            g2_pen(win, 1);

            char code1[2] = {residue_types[type_index].code1, '\0'};
            g2_string(win, center_x, center_y, code1);

            x1 += segment_width;
            num_shapes++;
        }

        y1 -= segment_height;
        y2 -= segment_height;
        x1 = 20;
    }

    getchar(); // Cekame na vstup znaku z klavesnice
    g2_close(win); // Zavreme okno
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

    draw_colored_rectangles();

    return 0;
}
