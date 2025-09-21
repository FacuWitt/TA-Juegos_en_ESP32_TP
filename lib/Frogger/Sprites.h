#ifndef SPRITES_H
#define SPRITES_H
#include <Arduino.h>


extern const unsigned char PROGMEM frogger_bmp[];
extern const unsigned char PROGMEM truck_big_bmp[];
extern const unsigned char PROGMEM truck_small_bmp[];
extern const unsigned char PROGMEM log_big_bmp[];
extern const unsigned char PROGMEM log_small_bmp[];
extern const unsigned char PROGMEM goal_bmp[];
extern const unsigned char PROGMEM grass_bmp[];
extern const unsigned char PROGMEM car_bmp[];


class Sprites {
    public:
        static unsigned char const* getFroggerSprite() { return frogger_bmp; }

        static unsigned char const* getBigTruckSprite() { return truck_big_bmp; }
        static unsigned char const* getSmallTruckSprite() { return truck_small_bmp; }
        static unsigned char const* getCarSprite() { return car_bmp; }

        static unsigned char const* getBigLogSprite() { return log_big_bmp; }
        static unsigned char const* getSmallLogSprite() { return log_small_bmp; }

        static unsigned char const* getGoalSprite() { return goal_bmp; }
        static unsigned char const* getGrassSprite() { return grass_bmp; }
};


#endif // SPRITES_H

