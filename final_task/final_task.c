// Vojtech Vrana
// 2024
// Program nacte PDB soubor s proteinem a urci aminokyseliny proteinu, jejichz peptidicke patere jsou vzajemne spojeny vodikovou vazbou
// V kruhovem grafu jsou tato rezidua spojena barevne rozlisenou krivkou

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

#define PATH_LENGTH 100
#define MAX_ITEMS 5000
#define BUF_SIZE 100
#define RESD_TYPES_COUNT 21

# define M_PIl 3.141592653589793238462643383279502884L

typedef struct {
    char type[7];
    int atom_num;
    char atom_name[5];
    char alt_pos;
    char residue_name[4];
    char id;
    int residue_num;
    char cres;
    double coord_x, coord_y, coord_z;
    double occ, temp;
    char element[3];
    char charge[3];
} ATOM;

typedef struct {
    int residue_num;
    char residue_name[4];
    int first_atom, last_atom;
    double center_x, center_y, center_z;
    int backbone_count;
    int atom_c;
    int atom_c_alpha;
    int atom_n;
    int atom_o;
    int residue_type;
    double angle;
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

typedef struct {
    int residue1;
    int residue2;
} PEPTIDE_HBOND;


// Globalni promenne
ATOM atoms[MAX_ITEMS] = {0}; // atomy pdb souboru
RESIDUE residues[MAX_ITEMS] = {0}; // rezidua
PEPTIDE_HBOND hbonds[MAX_ITEMS] = {0};
int atoms_count = 0; // pocet nactenych atomu
int residues_count = 0; // pocet rezidui
int hbonds_count = 0; // pocet vodikovych vazeb

void load_str(char *buf, int start, int length, char *target) { // nacte a ulozi string
    strncpy(target, buf + start, length);
    target[length] = '\0';
}

void load_int(char *buf, int start, int length, int *target) { // nacte a ulozi int
    char s[30] = "";
    load_str(buf, start, length, s);
    sscanf(s, "%d", target);
}

void load_float(char *buf, int start, int length, double *target) { // nacte a ulozi double
    char s[30] = "";
    load_str(buf, start, length, s);
    sscanf(s, "%lf", target);
}

int load_pdb (char data_in[]) { // nacte z pdb souboru radky ATOM a ulozi do pole atoms
    char buf[BUF_SIZE] = "";
    FILE *f = NULL;

    f = fopen(data_in, "r");
    if (f == NULL) {
        printf("Nelze otevrit vstupni soubor!\n");
        return 1;
    }

    while (fgets(buf, BUF_SIZE, f) != NULL) {
        if (strncmp(buf, "ATOM", 4) == 0) {
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
    int local_residues_count = 0; // k-te reziduum

    for (int i = 0; i < atoms_count; i++) {
        if (i == 0 || atoms[i].residue_num != atoms[i-1].residue_num) {
            if (i != 0) {
                residues[local_residues_count].last_atom = i-1;
                local_residues_count++;
            }
            residues[local_residues_count].first_atom = j;
            residues[local_residues_count].residue_num = atoms[i].residue_num;
            strcpy(residues[local_residues_count].residue_name, atoms[i].residue_name);
            residues[local_residues_count].residue_type = 0;
        }
        if (i == atoms_count - 1) {
            residues[local_residues_count].last_atom = i;
        }

        j = i+1;
    }

    for (int i = 0; i <= local_residues_count; i++) {
        for (int rt = 0; rt < RESD_TYPES_COUNT; rt++) {
            if (strcmp(residue_types[rt].code3, residues[i].residue_name) == 0) {
                residues[i].residue_type = rt;
                break;
            }
        }
    }

    return local_residues_count;
}

void find_backbones() {
    int count = 0; // pocet nalezenych atomu v reziduu
    int j = 0; // j-te reziduum

    for (int i = 0; i <= atoms_count; i++) {
        if (strcmp(atoms[i].atom_name, " N  ") == 0) {
            residues[j].atom_n = i;
            count++;
        } else if (strcmp(atoms[i].atom_name, " CA ") == 0) {
            residues[j].atom_c_alpha = i;
            count++;
        } else if (strcmp(atoms[i].atom_name, " C  ") == 0) {
            residues[j].atom_c = i;
            count++;
        } else if (strcmp(atoms[i].atom_name, " O  ") == 0) {
            residues[j].atom_o = i;
            count++;
        }

        if (i == residues[j].last_atom) {
            residues[j].backbone_count = count;
            count = 0;
            j++;
        }
    }
}

void print_backbones() {
    for (int i = 0; i <= residues_count; i++) {
        printf("Residuum %d %s, N: %i, CA: %i, C: %i, O: %i\n", residues[i].residue_num, residues[i].residue_name, residues[i].atom_n, residues[i].atom_c_alpha, residues[i].atom_c, residues[i].atom_o);
    }
}

double distance(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

void detect_hbonds() {
    find_backbones();
    double limit = 3.2;

    for (int i = 0; i <= residues_count; i++) {
        int n_index = residues[i].atom_n;

        if (n_index < 0 || n_index >= atoms_count) continue;

        float n_x = atoms[n_index].coord_x;
        float n_y = atoms[n_index].coord_y;
        float n_z = atoms[n_index].coord_z;

        for (int j = 0; j <= residues_count; j++) {
            if (i == j || j == i - 1 || j == i + 1) continue;

            int o_index = residues[j].atom_o;

            if (o_index < 0 || o_index >= atoms_count) continue;

            float o_x = atoms[o_index].coord_x;
            float o_y = atoms[o_index].coord_y;
            float o_z = atoms[o_index].coord_z;

            double dist = distance(n_x, n_y, n_z, o_x, o_y, o_z);

            if (dist < limit) {
                hbonds[hbonds_count].residue1 = residues[i].residue_num;
                hbonds[hbonds_count].residue2 = residues[j].residue_num;
                hbonds_count++;
            }
        }
    }
}

void print_hbonds() {
    for (int i = 0; i < hbonds_count; i++) {
        printf("%d a %d\n", hbonds[i].residue1, hbonds[i].residue2);
    }
}

void draw_colored_arcs(int win) {
    int type_color = 0;
    int num_segments = residues_count + 1;

    double start_angle = 90.0, end_angle = 90.0;
    double delta_angle = 360.0/num_segments;
    double current_angle = 0.0;

    g2_set_line_width(0, 10);

    for (int i = 0; i < num_segments; i++) {
        start_angle = 90.0 - (360.0/num_segments) * i;
        end_angle = 90.0 - (360.0/num_segments) * (i + 1.0);

        if (start_angle < 0) start_angle += 360.0;
        if (i == 0) current_angle = 90.0 - delta_angle / 2;
        else current_angle -= delta_angle;
        if (end_angle < 0) end_angle += 360.0;
        if (current_angle < 0) current_angle += 360.0;

        residues[i].angle = current_angle;

        int type_index = residues[i].residue_type;
        type_color = g2_ink(win, residue_types[type_index].color_r, residue_types[type_index].color_g, residue_types[type_index].color_b);

        g2_pen(win, type_color);

        g2_arc(0, 250, 250, 200, 200, end_angle, start_angle);
    }
}

void connect_hbonds(int win) {
    int orange = g2_ink(win, 255, 150, 0);
    int red = g2_ink(win, 255, 0, 0);
    int magenta = g2_ink(win, 150, 0, 255);
    int blue = g2_ink(win, 0, 0, 255);

    g2_set_line_width(win, 1);

    for (int i = 0; i < hbonds_count; i++) {
        int residue1_index = hbonds[i].residue1 - 1;
        int residue2_index = hbonds[i].residue2 - 1;

        double angle1 = residues[residue1_index].angle * M_PIl / 180.0; // radiany
        double angle2 = residues[residue2_index].angle * M_PIl / 180.0;

        double arc_radius = 200;

        int x1 = 250 + arc_radius * cos(angle1);
        int y1 = 250 + arc_radius * sin(angle1);
        int x2 = 250 + arc_radius * cos(angle2);
        int y2 = 250 + arc_radius * sin(angle2);

        double mid_angle = (angle1 + angle2) / 2.0;
        if (fabs(angle1 - angle2) > M_PIl) {
            mid_angle -= M_PIl;
        }

        int midx = 250 + 150 * cos(mid_angle);
        int midy = 250 + 150 * sin(mid_angle);

        double points[6] = {x1, y1, midx, midy, x2, y2};

        int delta_residues = fabs(residue1_index - residue2_index);

        if (delta_residues == 3) {
            g2_pen(win, orange);
        } else if (delta_residues == 4) {
            g2_pen(win, red);
        } else if (delta_residues == 5) {
            g2_pen(win, magenta);
        } else {
            g2_pen(win, blue);
        }

        g2_raspln(win, 3, points, 0.7);
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

    residues_count = find_residues_range();

    detect_hbonds();

    int win = 0;
    win = g2_open_X11(620, 530);

    draw_colored_arcs(win);
    connect_hbonds(win);

    getchar();
    g2_close(win);

    return 0;
}
