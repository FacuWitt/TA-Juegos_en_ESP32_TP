#include "Item.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Platform.h"

Item::Item(int x, int y, int width, int height, int speedY) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->active = true;
    this->speedY = speedY;
}

Item::Item() {
    x = y = width = height = 0;
    this->active = false;
}

void Item::draw(Adafruit_SSD1306 &display) {
    if (active) {
        display.fillRect(x, y, width, height, SSD1306_WHITE);
    }
}

bool Item::update(int SCREEN_HEIGHT, Platform &platform) {
    if (!active) return false;

    y += speedY;

    // Desactiva si sale de la pantalla
    if (y > SCREEN_HEIGHT) {
        active = false;
        return false;
    }

    // Verificar colisión con la plataforma
    if (x < platform.getX() + platform.getWidth() &&
        x + width > platform.getX() &&
        y + height >= platform.getY() &&
        y <= platform.getY() + platform.getHeight()) {
        active = false;
        return true;
    }

    return false;
}

bool Item::isActive() {
    return active;
}
