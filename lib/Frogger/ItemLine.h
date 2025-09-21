
#ifndef ITEM_LINE_H
#define ITEM_LINE_H
#include <Adafruit_SSD1306.h>
#include <Sprites.h>

class ItemLine {
    public:
        void draw(Adafruit_SSD1306 &display);
    private:
        const unsigned char* _item_bmp = nullptr;
        int _x;
        int _w;
        bool _is_obstacle; // true: obstáculo, false: plataforma
        bool isFroggerColliding(int frogX, int frogY); // La rana siempre tiene 8px de ancho y alto
};

#endif // ITEM_LINE_H
