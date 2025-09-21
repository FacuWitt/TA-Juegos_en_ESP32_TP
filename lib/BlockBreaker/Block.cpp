#include "Block.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Ball.h"

Block::Block(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    active = true;
    hasItem = (random(0, 100) < 20); // 20% probabilidad
}

Block::Block()
{
    x = y = width = height = 0;
    active = false;
    hasItem = false;
}

void Block::draw(Adafruit_SSD1306 &display)
{
    if (active) {
        display.fillRect(x, y, width, height, WHITE);
    }
}

bool Block::checkCollision(int ballX, int ballY, int ballRadius)
{
    if (!active) return false;

    // Check for collision
    if (ballX + ballRadius > x && ballX - ballRadius < x + width &&
        ballY + ballRadius > y && ballY - ballRadius < y + height) {
        active = false; // Deactivate block on collision
        return true;
    }
    return false;
}

bool Block::isActive() {
    return active;
}

bool Block::getHasItem() {
    return hasItem;
}

void Block::setHasItem(bool value) {
    hasItem = value;
}

int Block::getX() {
    return x;
}
int Block::getY() {
    return y;
}
int Block::getWidth() {
    return width;
}
int Block::getHeight() {
    return height;
}