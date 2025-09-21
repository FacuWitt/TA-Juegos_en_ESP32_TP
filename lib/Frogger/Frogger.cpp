#include "Frogger.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#include <Arduino.h>
#include "Sprites.h"


Frogger::Frogger(Adafruit_SSD1306 &disp) : _display(disp) {
    _frogX = SCREEN_WIDTH / 2 - 4;
    _frogY = SCREEN_HEIGHT - 8;
    _initial_clock = millis();
    _running = true;
    _frog_bmp = frogger_bmp;
    _truck_big_bmp = truck_big_bmp;
    _truck_small_bmp = truck_small_bmp;
    _log_big_bmp = log_big_bmp;
    _goal_bmp = goal_bmp;
    _grass_bmp = grass_bmp;
}

void Frogger::run(){
    while (_running){
        draw();
        checkButtons();
        update();
    }
}

void Frogger::draw(){
    _display.clearDisplay();
    _display.drawBitmap(_frogX, _frogY, _frog_bmp, 8, 8, SSD1306_WHITE);
    _display.drawBitmap(10, 20, _truck_big_bmp, 32, 7, SSD1306_WHITE);
    _display.drawBitmap(80, 40, _truck_small_bmp, 24, 7, SSD1306_WHITE);
    _display.drawBitmap(8, 30, _log_big_bmp, 32, 8, SSD1306_WHITE);
    _display.drawBitmap(40, 30, _log_big_bmp, 32, 8, SSD1306_WHITE);
    // _display.drawBitmap(0,0, _grass_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(16,0, _grass_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(32, 0, _goal_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(48, 0, _grass_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(64, 0, _grass_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(80, 0, _goal_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(96, 0, _grass_bmp, 16, 8, SSD1306_WHITE);
    // _display.drawBitmap(112, 0, _grass_bmp, 16, 8, SSD1306_WHITE);

    _display.drawBitmap(32, 0, _grass_bmp, 16, 8, SSD1306_WHITE);
    _display.drawBitmap(80, 0, _grass_bmp, 16, 8, SSD1306_WHITE);
    _display.display();
}

void Frogger::update(){

}

void Frogger::checkButtons(){

}



