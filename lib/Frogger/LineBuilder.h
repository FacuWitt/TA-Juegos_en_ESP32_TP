#ifndef LINE_BUILDER_H
#define LINE_BUILDER_H
#include <Arduino.h>
#include "Line.h"
#include "ItemLine.h"
#include "Sprites.h"


class LineBuilder {
    public:
        LineBuilder();
        Line getRandomLine(int y);
    private:
        ItemLine _bag_item_line [5];
};




#endif // LINE_BUILDER_H