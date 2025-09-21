
#ifndef FROGGER_GAME_H
#define FROGGER_GAME_H
#include <Adafruit_SSD1306.h>
#include <Line.h>
#include <Frog.h>

class FroggerGame {
    public:
        FroggerGame(Adafruit_SSD1306 &disp);
        void run();
    private:
        Adafruit_SSD1306 &_display;
        Frog _frog;
        int _frogLine; // línea en la que está la rana (0-7)
        // Line _roadLines[8];

        unsigned long _initial_clock;
        bool _running;
        void draw();
        void update();
        void checkButtons();
        void generateRoadLines();

        // ItemLine _item_lines[8];

        const unsigned char *_frog_bmp = nullptr;
        const unsigned char *_truck_big_bmp = nullptr;
        const unsigned char *_truck_small_bmp = nullptr;
        const unsigned char *_log_big_bmp = nullptr;
        const unsigned char *_goal_bmp = nullptr;
        const unsigned char *_grass_bmp = nullptr;
        // const byte *_title_bmp = nullptr;


};

#endif // FROGGER_GAME_H