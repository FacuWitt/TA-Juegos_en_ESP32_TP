#include "FroggerGame.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BTN_W_PIN 19
#define BTN_A_PIN 18
#define BTN_S_PIN 5
#define BTN_D_PIN 17



#include <Arduino.h>
#include "Sprites.h"





FroggerGame::FroggerGame(Adafruit_SSD1306 &disp) : _display(disp), _frog(SCREEN_WIDTH / 2 - 4, 7){
    // _frogX = SCREEN_WIDTH / 2 - 4;
    // _frogY = SCREEN_HEIGHT - 8;
    _initial_clock = millis();
    _running = true;
}

void FroggerGame::run(){

    while (_running){
        draw();
        checkButtons();
        update();
    }
}

void FroggerGame::draw(){
    _display.clearDisplay();
    _frog.draw(_display);
    _display.display();
}

void FroggerGame::update(){

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

void FroggerGame::generateRoadLines(){
}



