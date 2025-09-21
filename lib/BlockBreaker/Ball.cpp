#include "Ball.h"
#include <Arduino.h>
#include "Block.h"
#include "Platform.h"

Ball::Ball(float startX, float startY, int radius, float speedX, float speedY)
{
    x = startX;
    y = startY;
    this->radius = radius;
    this->speedX = speedX;
    this->speedY = speedY;
    active = true;
}

Ball::Ball()
{
    x = y = radius = speedX = speedY = 0;
    active = false;
}

void Ball::update(int SCREEN_WIDTH, int SCREEN_HEIGHT, Platform &platform, Block blocks[], int numBlocks)
{
    if (!active) return;

    x += speedX;
    y += speedY;

    // Rebota en las paredes laterales
    if (x <= 0 || x + radius >= SCREEN_WIDTH) { speedX = -speedX; }

    // Rebota en el techo
    if (y <= 0 ) { speedY = -speedY;}

    // Rebotar en la plataforma
    if (y + radius >= platform.getY() && x + radius >= platform.getX() && x <= platform.getX() + platform.getWidth()) {
        speedY = -speedY;
    }

    for (int i = 0; i < numBlocks; i++) {
        if (blocks[i].isActive() && blocks[i].checkCollision(x, y, radius)) {
            speedY = -speedY;
        }
    }

    // La pelota desaparece porque no reboto en la plataforma
    if (y + radius > SCREEN_HEIGHT) { 
        setInactive();
    }
}

void Ball::draw(Adafruit_SSD1306 &display)
{
    if (active) {
        display.fillCircle(x, y, radius, WHITE);
    }
}

bool Ball::isActive() {
    return active;
}

void Ball::setInactive() {
    active = false;
    speedX = 0;
    speedY = 0;
    x = -10;
    y = -10;
}