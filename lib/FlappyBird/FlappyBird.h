#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class FlappyBird {
  public:
    FlappyBird(Adafruit_SSD1306 &disp);    
    void run();

  private:
    Adafruit_SSD1306 &_display;
    int _buttonPin, _potPin;
    int birdY, velocity, gravity, jump, dificultad;
    int pipeX, pipeGap, pipeWidth, pipeSpeed;
    int score;
    bool gameOver;

    // Métodos
    void begin();       
    void update();      
    void draw();        
    void reset();   
};

#endif