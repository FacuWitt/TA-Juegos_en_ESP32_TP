#include "Snake.h"

#define BTN_W_PIN 19 // P1 UP
#define BTN_A_PIN 18 // P1 DOWN
#define BTN_S_PIN 5  // P2 DOWN
#define BTN_D_PIN 17 // P2 UP
#define BTN_T_PIN 16 // EXIT

const unsigned char Snake::_section_sprite[] PROGMEM = {
    B11110000,
    B11110000,
    B11110000,
    B11110000,
};
const unsigned char Snake::_food_sprite[] PROGMEM = {
    B00000000,
    B01100000,
    B01100000,
    B00000000,
};


Snake::Snake(Adafruit_SSD1306 &disp) : _display(disp) {
    _snake_length = 3;
    _dir_x = 1; // Movimiento inicial hacia la derecha
    _dir_y = 0;
    _food_x = 80;
    _food_y = 32;
    _snake_x[0] = 20; // dos vectores que funcionan como matriz de posiciones [x][y]
    _snake_y[0] = 32; // 20,32 es la posicion inicial
    _initial_clock = millis();
    _running = true;
    _update_interval = 50;
    _score = 0;
    pressedKey = false;

    pinMode(BTN_W_PIN, INPUT_PULLDOWN);
    pinMode(BTN_A_PIN, INPUT_PULLDOWN);
    pinMode(BTN_S_PIN, INPUT_PULLDOWN);
    pinMode(BTN_D_PIN, INPUT_PULLDOWN);
    pinMode(BTN_T_PIN, INPUT_PULLDOWN);

}

void Snake::run(){
    while(_running){
        _display.clearDisplay();
        checkButtons();
        if (millis() - _initial_clock >= _update_interval) { // cada 100ms se actualiza el juego, los botones se chequean mas seguido
            _initial_clock = millis();
            move();
            pressedKey = false;
        }
        draw();
        _display.display();
    }
}

void Snake::draw(){
    _display.drawRect(0,8,128,56,SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(2,0);
    _display.print("SCORE: ");
    _display.print(_score);

    for(int i = 0; i < _snake_length; i++){
        _display.drawBitmap(_snake_x[i], _snake_y[i], _section_sprite, 4, 4, SSD1306_WHITE);
    }
    _display.drawBitmap(_food_x, _food_y, _food_sprite, 4, 4, SSD1306_WHITE);
}

void Snake::move(){

    // Mover la cabeza de la serpiente
    if (_snake_x[0] == _food_x && _snake_y[0] == _food_y) { // La serpiente come
        _snake_length++;
        _score += 10;
        if (_score >= 250) {
            win();
            return;
        }
        spawnFood();
    }

    // guardar posición vieja de la cabeza
    int prevX = _snake_x[0];
    int prevY = _snake_y[0];

    _snake_x[0] += _dir_x * 4;
    _snake_y[0] += _dir_y * 4;

    if (_snake_x[0] < 0) _snake_x[0] = 124;
    else if (_snake_x[0] >= 128) _snake_x[0] = 0;
    else if (_snake_y[0] < 8) _snake_y[0] = 60;
    else if (_snake_y[0] >= 64) _snake_y[0] = 8;

    for (int i = _snake_length - 1; i > 0; i--) {
        _snake_x[i] = _snake_x[i - 1];
        _snake_y[i] = _snake_y[i - 1];
    }
    
    for (int i = _snake_length - 1; i > 1; i--) {
        if (_snake_x[0] == _snake_x[i] && _snake_y[0] == _snake_y[i]) {
            gameOver();
        }
    }


}

void Snake::checkButtons(){
    if (!pressedKey){
        if (digitalRead(BTN_W_PIN) == HIGH && _dir_y != 1) {
            _dir_x = 0;
            _dir_y = -1;
            pressedKey = true;
        } else if (digitalRead(BTN_A_PIN) == HIGH && _dir_x != 1) {
            _dir_x = -1;
            _dir_y = 0;
            pressedKey = true;
        } else if (digitalRead(BTN_S_PIN) == HIGH && _dir_y != -1) {
            _dir_x = 0;
            _dir_y = 1;
            pressedKey = true;
        } else if (digitalRead(BTN_D_PIN) == HIGH && _dir_x != -1) {
            _dir_x = 1;
            _dir_y = 0;
            pressedKey = true;
        } else if (digitalRead(BTN_T_PIN) == HIGH) {
            _running = false;
        }
    }
        

}

void Snake::spawnFood(){
    _food_x = random(0, 32) * 4;
    _food_y = random(2, 16) * 4;
}

void Snake::gameOver(){
    for(int i = 0; i < 10; i++){
        _display.clearDisplay();
        _display.display();
        delay(100);
        draw();
        _display.display();
        delay(100);
    }
    _running = false;
}

void Snake::win(){
    _display.clearDisplay();
    _display.setTextSize(2);
    
    for(int i = 0; i < 10; i++){
        _display.clearDisplay();
        draw();
        _display.setTextColor(SSD1306_WHITE);
        _display.setCursor(20, 20);
        _display.println("YOU WIN!");
        _display.display();
        delay(100);
        _display.clearDisplay();
        draw();
        _display.setTextColor(SSD1306_BLACK);
        _display.setCursor(20, 20);
        _display.println("YOU WIN!");
        _display.display();
        delay(100);
    }
    
    _display.display();
    delay(2000);
    _running = false;
}