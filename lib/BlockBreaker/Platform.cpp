#include "Platform.h"
#include <Arduino.h>


Platform::Platform(int startX, int startY, int width, int height)
{
    x = startX;
    y = startY;
    this->width = width;
    this->height = height;
    speed = 2;
}

void Platform::update(int direction, int SCREEN_WIDTH)
{
    x += direction * speed;

    if (x < 0) {
        x = 0;
    }
    if (x > SCREEN_WIDTH - width) {
        x = SCREEN_WIDTH - width;
    }
}

void Platform::draw(Adafruit_SSD1306 &display)
{
    display.fillRect(x, y, width, height, WHITE);
}

int Platform::getX() {
    return x;
}

int Platform::getY() {
    return y;
}

int Platform::getWidth() {
    return width;
}

int Platform::getHeight() {
    return height;
}
