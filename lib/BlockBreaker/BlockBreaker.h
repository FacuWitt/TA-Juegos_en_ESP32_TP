#ifndef BLOCKBREAKER_H
#define BLOCKBREAKER_H

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// Incluye tus clases de juego
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "Item.h"

class BlockBreaker {
public:
    // Constructor
    BlockBreaker(Adafruit_SSD1306 &disp);
    // Método para iniciar el bucle del juego
    void run();

private:
    // Puntero o referencia al display para dibujar
    Adafruit_SSD1306 &_display;

    // Constantes del juego
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int BALL_RADIUS = 2;
    static const int PLATFORM_WIDTH = 25;
    static const int PLATFORM_HEIGHT = 4;
    static const int ITEM_SIZE = 4;
    static const int ITEM_SPEED_Y = 1;
    static const int MAX_BALLS = 10;
    static const int MAX_ITEMS = 10;
    static const int MAX_BLOCKS = 30;
    static const int BLOCK_WIDTH = 10;
    static const int BLOCK_HEIGHT = 4;
    static const int NUM_ROWS = 3;
    static const int NUM_COLS = 10;
    static const int BTN_A_PIN = 18;
    static const int BTN_D_PIN = 17;


    // Variables de estado del juego
    unsigned long _lastUpdate = 0;
    const int _frameTime = 20;
    bool _running = true;
    bool _gameOver = false;
    
    // Objetos del juego
    Platform _platform;
    Ball _balls[MAX_BALLS];
    Item _items[MAX_ITEMS];
    int _numItems = 0;
    Block _blocks[MAX_BLOCKS];
    int _blockCount = 0;
    
    // Mapa de niveles
    static const int _allLevelsMap[][NUM_ROWS][NUM_COLS];
    static const int NUM_LEVELS;

    // Métodos privados para la lógica interna
    void _init();
    void _updateGameLogic();
    void _drawGameElements();
    void _generateLevel(int levelIndex);
    float _randomFloat(float minVal, float maxVal);
    void _drawCenteredText(String msg, int y);
};

#endif