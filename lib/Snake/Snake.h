
#ifndef SNAKE_H
#define SNAKE_H
#include <Adafruit_SSD1306.h>

class Snake {
    public:
        Snake(Adafruit_SSD1306 &disp);
        void run();
    private:
        Adafruit_SSD1306 &_display;
        bool _running;
        int _snake_x[128], _snake_y[64];
        int _snake_length;
        int _dir_x, _dir_y;
        int _food_x, _food_y;
        unsigned long _initial_clock;
        int _update_interval; // milliseconds
        bool pressedKey; // Para evitar multiples cambios de direccion en un solo frame
        static const unsigned char _section_sprite [] PROGMEM;
        static const unsigned char _food_sprite [] PROGMEM;
        
        void move();
        void draw();
        void update();
        void checkButtons();
        void spawnFood();
        void gameOver();
        void win();
};
#endif