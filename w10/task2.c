#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

void draw_colored_segments(int num_segments) {
    double start_angle = 0.0, end_angle = 0.0;

    g2_set_line_width(0, 10);
    for (int i = 0; i < num_segments; i++) {
        start_angle = (360.0/num_segments) * i;
        end_angle = (360.0/num_segments) * (i + 1.0);

        if (i % 2 == 0) {
            g2_pen(0, 19);
        } else {
            g2_pen(0, 3);
        }

        g2_arc(0, 250, 250, 200, 200, start_angle, end_angle);
    }
}

int main(int argc, char *argv[]) {
    int num_segments = 0;

    if (argc > 1) {
        sscanf(argv[1], "%d", &num_segments);
        if (num_segments < 1) {
            printf("Pocet segmentu musi byt kladne cislo.\n");
            return 0;
        }
    } else {
        printf("Zadejte pocet segmentu.\n");
        return 0;
    }

    int win = 0;
    win = g2_open_X11(500, 500);

    draw_colored_segments(num_segments);

    getchar(); // Cekame na vstup znaku z klavesnice
    g2_close(win); // Zavreme okno

    return 0;
}
