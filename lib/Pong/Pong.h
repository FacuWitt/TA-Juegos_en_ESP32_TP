#ifndef PONG_H
#define PONG_H

#include <Adafruit_SSD1306.h>

// void startPong(Adafruit_SSD1306 &display);

class Pong {
public:
    Pong(Adafruit_SSD1306 &disp);
    void run();
private:
    Adafruit_SSD1306 &_display;
    int _ball_pos_x, _ball_pos_y;
    int _vel_x, _vel_y;
    int _vel_pal; // velocidad de la paleta
    int _p1_y, _p2_y; // posiciones Y de las paletas
    int _score_p1, _score_p2;
    int _cant_toques;
    void draw();
    void update();
    void goal();
    // boolean pal_coll();
};

#endif