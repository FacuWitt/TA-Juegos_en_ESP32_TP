#ifndef BLOCK_H
#define BLOCK_H

#include <Adafruit_SSD1306.h>
class Ball;

class Block {
    private:
        int x;
        int y;
        int width;
        int height;
        bool active;
        bool hasItem;
    public:
        Block(int x, int y, int width, int height);
        Block();
        void draw(Adafruit_SSD1306 &display);
        bool checkCollision(int ballX, int ballY, int ballRadius);
        bool isActive();
        bool getHasItem();
        void setHasItem(bool value);
        int getX();
        int getY();
        int getWidth();
        int getHeight();
};

#endif