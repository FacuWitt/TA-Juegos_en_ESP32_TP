#include "Line.h"


Line::Line(int y, int vel, int space_between, bool is_road, ItemLine item_line) :
    _y(y), _vel(vel), _space_between(space_between), _is_road(is_road), _item_line(item_line) {
    generateItemsLine();
    _last_update_time = millis();
}

void Line::update(){

    for (auto &item : _array_items_line) {
        item.move(_vel); // Velocidad se mide en px/segundo
    }
}

void Line::draw(Adafruit_SSD1306 &display){
    // Dibujar la línea (carretera o río) y los vehículos o troncos en la pantalla
    // Aquí puedes implementar la lógica para dibujar los elementos en la pantalla
       
    for (auto &item : _array_items_line) {
        if (!item.is_obstacle()) {
            display.fillRect(0, _y, 128, 8, SSD1306_WHITE); // Fondo
        }
        item.draw(display, _y);
    }
}


void Line::generateItemsLine() {
    // Lógica para generar vehículos o troncos en la línea según el espacio entre ellos
    // Puedes usar la variable _space_between para determinar cuándo agregar un nuevo ítem
    // y la variable _is_road para decidir si es una carretera o un río
    // int cant_items = (128 / (_space_between + _item_line.getWidth())) + 1; // space between va a ser siempre un divisor de 128
    int cant_items = 128 / (_space_between);

    if (!_item_line.is_obstacle()){
        Serial.println("Línea de río, ");
        Serial.println("cantidad de plataformas: ");
        Serial.println(cant_items);

    }
    _array_items_line.clear(); // limpiar por si se llama de nuevo

    for (int i = 0; i < cant_items; i++) {
        int x_position = i * (_space_between); // posición x inicial del ítem
        ItemLine copy = _item_line;  // hacemos una copia del template
        copy.setX(x_position);
        _array_items_line.push_back(copy); // lo agregamos al vector
    }
}

void Line::printDebugInfo() {
    Serial.print("Line at y=");
    Serial.print(_y/8);
    Serial.print(", vel=");
    Serial.print(_vel);
    Serial.print(", space_between=");
    Serial.print(_space_between);
    Serial.print(", is_road=");
    Serial.print(_is_road ? "true" : "false");
    Serial.print(", item_width=");
    Serial.print(_item_line.getWidth());
    Serial.print(", item_is_obstacle=");
    Serial.println(_item_line.is_obstacle() ? "true" : "false");
}