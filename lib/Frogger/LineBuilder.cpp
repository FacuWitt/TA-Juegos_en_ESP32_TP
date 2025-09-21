#include "LineBuilder.h"
#include "Sprites.h"




LineBuilder::LineBuilder() :
    _bag_item_line {
        ItemLine(Sprites::getCarSprite(), 16, true),        // Autos
        ItemLine(Sprites::getSmallTruckSprite(), 16, true), // Autos
        ItemLine(Sprites::getBigTruckSprite(), 24, true),   // Camiones
        ItemLine(Sprites::getSmallLogSprite(), 16, false),  // Troncos pequeños
        ItemLine(Sprites::getBigLogSprite(), 32, false)     // Troncos
    } {
        // Constructor
}

Line LineBuilder::getRandomLine(int y) {
    int item_index = random(0, 5); // Seleccionar un ItemLine aleatorio del bag
    ItemLine item_line = _bag_item_line[item_index];
    bool is_road = item_line.is_obstacle(); // Aleatoriamente carretera o río
    int space_between = is_road ? random(4, 8) * 8 : random(1, 3) * 8;
    int vel = random(1, 3) * (random(0, 2) == 0 ? 1 : -1);
    return Line(y, vel, space_between, is_road, item_line);
}
