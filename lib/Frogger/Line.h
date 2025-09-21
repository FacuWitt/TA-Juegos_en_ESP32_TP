
#ifndef LINE_H
#define LINE_H
#include <Adafruit_SSD1306.h>
#include <ItemLine.h>
#include <vector>

class Line {
    public:
        Line(int y, int vel, int space_between, bool is_road, ItemLine item_line);
        void update();
        void draw(Adafruit_SSD1306 &display);
        void printDebugInfo();
    private:
        int _y;
        int _vel;
        int _space_between;
        bool _direction; // true: right, false: left
        bool _is_road; // true: carretera, false: río
        unsigned long _last_update_time;
        ItemLine _item_line;
        std::vector<ItemLine> _array_items_line; // array dinamico de items en la línea
        void generateItemsLine();
};
#endif // LINE_H
