#include "FroggerGame.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BTN_W_PIN 19
#define BTN_A_PIN 18
#define BTN_S_PIN 5
#define BTN_D_PIN 17



#include <Arduino.h>
#include "Sprites.h"




// _array_lines(0, 1, 8, true, ItemLine(nullptr, 0, true))
FroggerGame::FroggerGame(Adafruit_SSD1306 &disp) : _display(disp), _frog(SCREEN_WIDTH / 2 - 4, 7) {
    // _frogX = SCREEN_WIDTH / 2 - 4;
    // _frogY = SCREEN_HEIGHT - 8;

    pinMode(BTN_W_PIN, INPUT);
    pinMode(BTN_A_PIN, INPUT);
    pinMode(BTN_S_PIN, INPUT);
    pinMode(BTN_D_PIN, INPUT);

    _initial_clock = millis();
    _running = true;
}

void FroggerGame::run(){
    _line_builder = LineBuilder();
    // _array_lines = _line_builder.getRandomLine();
    generateLines();

    while (_running){
        draw();
        checkButtons();
        update();
    }
}

void FroggerGame::draw(){
    _display.clearDisplay();
    _frog.draw(_display);

    for (int i = 0; i < 8; i++){
        _array_lines[i].draw(_display);
    }
    // _array_lines.draw(_display);
    _display.display();
}

void FroggerGame::update(){
    for (int i = 0; i < 8; i++){
        _array_lines[i].update();
    }
    // _array_lines.update();
    // _array_lines.draw(_display);
}

void FroggerGame::checkButtons(){
    if (digitalRead(BTN_W_PIN) == HIGH && _frogLine > 0){
        _frogLine--;
    }
    if (digitalRead(BTN_S_PIN) == HIGH && _frogLine < 7){
        _frogLine++;
    }
    if (digitalRead(BTN_A_PIN) == HIGH && _frogLine > 0){
        // mover a la izquierda
    }
    if (digitalRead(BTN_D_PIN) == HIGH && _frogLine < 7){
        // mover a la derecha
    }
}

void FroggerGame::generateLines(){
    _array_lines.clear();
    for (int i = 1; i < 7; i++) {
        _array_lines.push_back(_line_builder.getRandomLine(i * 8));
    }
    for (int i = 0; i < 6; i++) {
        _array_lines[i].printDebugInfo();
    }
}




