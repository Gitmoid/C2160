#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>
#include <math.h>

#define PI 3.1415926535898

int main() {
    int win = 0;
    win = g2_open_X11(520, 800); // uz jsem to udelal pro tuto velikost okna a nechce se mi to predelavat
    int Ypos = 750;
    int Xpos = 20;

    // text
    g2_set_font_size(0, 24);
    g2_string(0, Xpos, Ypos, "Tento text je napsany pismem velikosti 24");
    g2_set_font_size(0, 15);
    Ypos -= 20;
    g2_string(0, Xpos, Ypos, "Tento text je napsany pismem velikosti 15");
    g2_set_font_size(0, 12);
    Ypos -= 15;
    g2_string(0, Xpos, Ypos, "Tento text je napsany pismem velikosti 12");
    g2_set_font_size(0, 10);
    Ypos -= 15;
    g2_string(0, Xpos, Ypos, "Tento text je napsany pismem velikosti 10");

    // cervena hvezda
    g2_pen(0, 19);
    int centerX = 360;
    int centerY = Ypos;
    int radius = 30;
    for (int i = 0; i < 12; i++) {
        double angle = i * 30 * PI / 180;

        int endX = centerX + radius * cos(angle);
        int endY = centerY + radius * sin(angle);

        g2_line(0, centerX, centerY, endX, endY);
    }

    // modra hvezda
    g2_pen(0, 3);
    centerX = 440;
    g2_set_line_width(0, 3);
    for (int i = 0; i < 12; i++) {
        double angle = i * 30 * PI / 180;

        int endX = centerX + radius * cos(angle);
        int endY = centerY + radius * sin(angle);

        g2_line(0, centerX, centerY, endX, endY);
    }
    g2_pen(0, 0);
    g2_filled_circle(0, centerX, centerY, radius-12);
    g2_set_line_width(0, 1);

    // gradient cervene
    Ypos -= 50;
    int length = 480;
    double grad = 0.0;
    int col = 0;
    int i = Xpos;
    while (i < Xpos + length) {
        col = g2_ink(0, 1, 1-grad, 1-grad);
        g2_pen(0, col);
        g2_line(0, i, Ypos, i, Ypos-30);
        i++;
        grad += 1.0/length;
    }

    // gradient modrych krouzku
    Ypos -= 60;
    radius = 10;
    centerY = Ypos;
    grad = 0.0;
    for (int i = 0; i < 16; i++) {
        centerX = Xpos + i * radius * 3;
        grad = i/15.0;
        col = g2_ink(0, 0+grad, 0+grad, 1);
        g2_pen(0, col);
        g2_filled_circle(0, centerX, centerY, radius);
        g2_pen(0, 1);
        g2_circle(0, centerX, centerY, radius);
    }

    // stridani krouzku
    Ypos -= 50;
    centerY = Ypos;
    for (int i = 0; i < 16; i++) {
        centerX = Xpos + i * radius * 3;
        col = g2_ink(0, 1, 0.5, 0.5);
        if (i % 2 == 1) col = g2_ink(0, 0.5, 0.5, 1);
        g2_pen(0, col);
        g2_filled_circle(0, centerX, centerY, radius);
    }

    // divocina
    Ypos -= 30;
    int w = 50;

    g2_set_line_width(0, 5);
    g2_pen(0, 19);
    g2_line(0, Xpos, Ypos, Xpos+w, Ypos-w);
    g2_line(0, Xpos+w, Ypos, Xpos, Ypos-w);
    Xpos += w + 20;

    g2_pen(0, 3);
    g2_rectangle(0, Xpos, Ypos, Xpos+w, Ypos-w);
    Xpos += w + 20;

    g2_set_line_width(0, 1);
    g2_filled_rectangle(0, Xpos, Ypos, Xpos+w, Ypos-w);
    Xpos += w + 20;

    g2_set_line_width(0, 5);
    g2_pen(0, 7);
    g2_set_line_width(0, 7);
    centerX = Xpos + w/2;
    centerY = Ypos - w/2;
    g2_circle(0, centerX, centerY, w/2);
    Xpos += w + 20;

    g2_set_line_width(0, 1);
    centerX = Xpos + w/2;
    centerY = Ypos - w/2;
    g2_filled_circle(0, centerX, centerY, w/2);
    Xpos += w + 20;

    g2_set_line_width(0, 5);
    centerX = Xpos + w/2;
    centerY = Ypos - w/2;
    g2_pen(0, 19);
    g2_arc(0, centerX, centerY, w/2, w/2, 0, 120);
    g2_pen(0, 3);
    g2_arc(0, centerX, centerY, w/2, w/2, 120, 240);
    g2_pen(0, 25);
    g2_arc(0, centerX, centerY, w/2, w/2, 240, 360);
    Xpos += w + 20;

    g2_set_line_width(0, 1);
    centerX = Xpos + w/2;
    centerY = Ypos - w/2;
    g2_pen(0, 19);
    g2_filled_arc(0, centerX, centerY, w/2, w/2, 0, 120);
    g2_pen(0, 3);
    g2_filled_arc(0, centerX, centerY, w/2, w/2, 120, 240);
    g2_pen(0, 25);
    g2_filled_arc(0, centerX, centerY, w/2, w/2, 240, 360);

    getchar(); // Cekame na vstup znaku z klavesnice
    g2_close(win); // Zavreme okno

    return 0;
}
