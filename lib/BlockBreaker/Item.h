#ifndef ITEM_H
#define ITEM_H

#include <Adafruit_SSD1306.h>

class Platform;

class Item {
    private:
        int x;
        int y;
        int width;
        int height;
        bool active;
        int speedY;
    public:
        Item(int x, int y, int width, int height, int speedY);
        Item();
        void draw(Adafruit_SSD1306 &display);
        bool update(int SCREEN_HEIGHT, Platform &platform);
        bool isActive();
};

#endif