#ifndef PLATFORM_H
#define PLATFORM_H

#include <Adafruit_SSD1306.h>

class Platform {
    private:
        int x;
        int y;
        int width;
        int height;
        int speed;
    public:
        Platform(int startX, int startY, int width, int height);
        void update(int direction, int SCREEN_WIDTH);
        void draw(Adafruit_SSD1306 &display);
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        void setX(int newX) { x = newX; }
};

#endif