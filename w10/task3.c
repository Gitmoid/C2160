#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

void draw_colored_segments(int segments_total, int segments_row) {
    int segment_size = 460 / segments_row;
    int columns_total = segments_total / segments_row;
    int x1 = 20;
    int y1 = 480;
    int y2 = 460;
    int num_shapes = 0;

    for (int k = 0; k < columns_total+1; k++) {
        for (int i = 0; i < segments_row; i++) {
            if (num_shapes % 2 == 0) {
                g2_pen(0, 19);
            } else {
                g2_pen(0, 3);
            }

            g2_filled_rectangle(0, x1, y1, x1+segment_size, y2);

            x1 += segment_size;
            num_shapes++;
            if (num_shapes == segments_total) break;
        }
        y1 -= 30;
        y2 -= 30;
        x1 = 20;
    }
}

int main(int argc, char *argv[]) {
    int segments_total = 0;
    int segments_row = 0;

    if (argc > 2) {
        sscanf(argv[1], "%d", &segments_total);
        sscanf(argv[2], "%d", &segments_row);
        if (segments_total < 1 || segments_row < 1) {
            printf("Pocet segmentu musi byt kladne cislo.\n");
            return 0;
        }
    } else {
        printf("Zadejte celkovy pocet segmentu a pocet segmentu na jednom radku.\n");
        return 0;
    }

    int win = 0;
    win = g2_open_X11(500, 500);

    draw_colored_segments(segments_total, segments_row);

    getchar(); // Cekame na vstup znaku z klavesnice
    g2_close(win); // Zavreme okno

    return 0;
}
