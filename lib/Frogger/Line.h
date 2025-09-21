
#ifndef LINE_H
#define LINE_H
#include <Adafruit_SSD1306.h>
#include <ItemLine.h>

class Line {
    public:
        Line(int y, int vel, bool is_road, ItemLine item_line);
        void update();
        void draw(Adafruit_SSD1306 &display);
    private:
        int _y;
        int _vel;
        int _space_between;
        bool _direction; // true: right, false: left
        int _x;
        bool _is_road; // true: carretera, false: río
        ItemLine _item_line;

        
        
};
#endif // LINE_H
