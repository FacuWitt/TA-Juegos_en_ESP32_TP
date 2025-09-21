
#ifndef FROGGER_H
#define FROGGER_H
#include <Adafruit_SSD1306.h>

class Frogger {
    public:
        Frogger(Adafruit_SSD1306 &disp);
        void run();
    private:
        Adafruit_SSD1306 &_display;
        int _frogX;
        int _frogY;
        int _lifes = 3;

        unsigned long _initial_clock;
        bool _running;
        void draw();
        void update();
        void checkButtons();
        const unsigned char *_frog_bmp = nullptr;
        const unsigned char *_truck_big_bmp = nullptr;
        const unsigned char *_truck_small_bmp = nullptr;
        const unsigned char *_log_big_bmp = nullptr;
        const unsigned char *_goal_bmp = nullptr;
        const unsigned char *_grass_bmp = nullptr;
        // const byte *_title_bmp = nullptr;


};

#endif // FROGGER_H