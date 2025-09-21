
#include "Frog.h"
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Sprites.h"

Frog::Frog(int x, int n_line) : _x(x), _n_line(n_line) {
    _x = x;
    _n_line = n_line;
    _frog_bmp = Sprites::getFroggerSprite();
}
void Frog::draw(Adafruit_SSD1306 &display) {
    display.drawBitmap(_x, _n_line * 8, _frog_bmp, 8, 8, SSD1306_WHITE);
}