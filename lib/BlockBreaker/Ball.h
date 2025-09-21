#ifndef BALL_H
#define BALL_H
#include <Adafruit_SSD1306.h>

class Block;
class Platform;

class Ball {
    private:
        float x;
        float y;
        int radius;
        float speedX;
        float speedY;
        bool active;
    public:
        Ball(float startX, float startY, int radius, float speedX, float speedY);
        Ball();
        void update(int SCREEN_WIDTH, int SCREEN_HEIGHT, Platform &platform, Block blocks[], int numBlocks);
        void draw(Adafruit_SSD1306 &display);
        bool isActive();
        void setInactive();
};

#endif