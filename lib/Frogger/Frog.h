#ifndef FROG_H
#define FROG_H

#include <Adafruit_SSD1306.h>
#include <Sprites.h>

class Frog {
    public:
        Frog(int x, int n_line);
        void draw(Adafruit_SSD1306 &display);
    private:
        int _n_line; // línea en la que está la rana (0 a 7) -> 7, inicio, 0 fin
        int _x; // posición x de la rana (0 a 120)
        const unsigned char *_frog_bmp = nullptr;
};

#endif // FROG_H