#include "ItemLine.h"

ItemLine::ItemLine(const unsigned char* item_bmp, int w, bool is_obstacle)
    : _item_bmp(item_bmp), _w(w), _is_obstacle(is_obstacle) {
        // Inicializar otras variables si es necesario
}

void ItemLine::move(int vel) {
    _x += vel;
    if (_x > 128) {
        _x = -_w; // reaparece por la izquierda
    }
    else if (_x + _w < 0) {
        _x = 128; // reaparece por la derecha
    }
    // Aquí puedes agregar lógica adicional para manejar el movimiento, como reiniciar la posición si sale de la pantalla
}

void ItemLine::draw(Adafruit_SSD1306 &display, int y) {
    display.fillRect(_x, y, _w, 8, SSD1306_BLACK); // Fondo
    display.drawBitmap(_x, y, _item_bmp, _w, 8, SSD1306_WHITE);
}