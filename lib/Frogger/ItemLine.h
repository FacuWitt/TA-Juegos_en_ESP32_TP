
#ifndef ITEM_LINE_H
#define ITEM_LINE_H
#include <Adafruit_SSD1306.h>
#include <Sprites.h>

class ItemLine {
    public:
        ItemLine(const unsigned char* item_bmp, int w, bool is_obstacle);
        void draw(Adafruit_SSD1306 &display, int y);
        void move(int vel);
        void setX(int x) { _x = x; } // para cuando hay que agregarlo al array de ItemLines en la línea
        int getWidth() { return _w; }
        bool is_obstacle() { return _is_obstacle; }
    private:
        const unsigned char* _item_bmp = nullptr;
        int _x; // posición x del ítem en la línea
        int _w;
        bool _is_obstacle; // true: obstáculo, false: plataforma
        // bool isFroggerColliding(int frogX, int frogY); // La rana siempre tiene 8px de ancho y alto
};

#endif // ITEM_LINE_H
