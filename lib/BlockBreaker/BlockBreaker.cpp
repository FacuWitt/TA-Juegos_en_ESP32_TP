#include "BlockBreaker.h"

// Define el mapa de niveles, que es una variable estática de la clase.
const int BlockBreaker::_allLevelsMap[][BlockBreaker::NUM_ROWS][BlockBreaker::NUM_COLS] = {
    // Nivel 1 - Túnel
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    // Nivel 2 - Muralla
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
    // Nivel 3 - Escalera
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
     {1, 1, 0, 0, 0, 0, 0, 0, 1, 1}},
    // Nivel 4 - Zigzag
    {{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {0, 1, 1, 0, 0, 0, 0, 1, 1, 0}},
    // Nivel 5: Pirámide invertida
    {{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
     {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
     {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}},
    // Nivel 6: Pasillo central
    {{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
     {1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
     {1, 1, 1, 1, 0, 0, 1, 1, 1, 1}},
    // Nivel 7: Puntos aleatorios
    {{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0}},
    // Nivel 8: Diamante
    {{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
     {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
     {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}},
    // Nivel 9: Muros exteriores
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
    // Nivel 10: Bloques en 'T'
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
     {0, 0, 0, 0, 1, 1, 0, 0, 0, 0}}};

// Define el número total de niveles
const int BlockBreaker::NUM_LEVELS = sizeof(BlockBreaker::_allLevelsMap) / sizeof(BlockBreaker::_allLevelsMap[0]);

// Constructor: Inicializa la pantalla y la plataforma.
BlockBreaker::BlockBreaker(Adafruit_SSD1306 &disp) :
    _display(disp),
    _platform(51, 58, PLATFORM_WIDTH, PLATFORM_HEIGHT) {
}

// Método run(): Contiene el bucle principal del juego.
void BlockBreaker::run() {
    _init(); // Llama al método de inicialización del juego.
    while (_running) {
        if (millis() - _lastUpdate >= _frameTime) {
            _lastUpdate = millis();
            _updateGameLogic();
            _drawGameElements();
        }

        if (_gameOver) {
            delay(2000); // Espera 2 segundos
            _running = false;
        }

    }
}

// Métodos de lógica interna del juego:
// A continuación se muestra cómo implementar cada método privado, moviendo el código de tu `main.cpp`.

// Inicialización del juego
void BlockBreaker::_init() {
    int randomLevelIndex = random(0, NUM_LEVELS);
    _generateLevel(randomLevelIndex);

    _balls[0] = Ball(64, 54, BALL_RADIUS, _randomFloat(-1, 1), _randomFloat(-2, -1));
    for (int i = 1; i < MAX_BALLS; i++) {
        _balls[i].setInactive();
    }
    _running = true;
}

// Actualiza toda la lógica del juego
void BlockBreaker::_updateGameLogic() {
    
    

    int direction = 0;
    if (digitalRead(BTN_A_PIN) == HIGH) {
        direction = -1; // Mover a la izquierda
    } else if (digitalRead(BTN_D_PIN) == HIGH) {
        direction = 1;  // Mover a la derecha
    }
    _platform.update(direction, SCREEN_WIDTH);

    bool allBallsInactive = true;
    for (int i = 0; i < MAX_BALLS; i++) {
        if (_balls[i].isActive()) {
            _balls[i].update(SCREEN_WIDTH, SCREEN_HEIGHT, _platform, _blocks, _blockCount);
            allBallsInactive = false;
        }
    }

    for (int i = 0; i < _numItems; i++) {
        if (!_items[i].isActive()) continue;
        if (_items[i].update(SCREEN_HEIGHT, _platform)) {
            for (int j = 0; j < MAX_BALLS; j++) {
                if (!_balls[j].isActive()) {
                    _balls[j] = Ball(
                        _platform.getX() + _platform.getWidth() / 2,
                        _platform.getY() - BALL_RADIUS,
                        BALL_RADIUS,
                        _randomFloat(-1, 1),
                        _randomFloat(-2, -1));
                    break;
                }
            }
        }
    }

    bool allBlocksInactive = true;
    for (int i = 0; i < _blockCount; i++) {
        if (_blocks[i].isActive()) {
            allBlocksInactive = false;
        } else {
            if (_blocks[i].getHasItem() && _numItems < MAX_ITEMS) {
                _items[_numItems++] = Item(_blocks[i].getX() + _blocks[i].getWidth() / 2 - (ITEM_SIZE / 2),
                                          _blocks[i].getY() + _blocks[i].getHeight(),
                                          ITEM_SIZE, ITEM_SIZE, ITEM_SPEED_Y);
                _blocks[i].setHasItem(false);
            }
        }
    }

    if (allBlocksInactive) {
        for (int i = 0; i < MAX_BALLS; i++) {
            _balls[i].setInactive();
        }
    }

    if (allBallsInactive || allBlocksInactive) {
        _gameOver = true;
    }
}

// Dibuja todos los elementos del juego en la pantalla.
void BlockBreaker::_drawGameElements() {
    _display.clearDisplay();

    if (!_gameOver) {
        _platform.draw(_display);
    
        for (int i = 0; i < _blockCount; i++) {
            if (_blocks[i].isActive()) {
                _blocks[i].draw(_display);
            }
        }
    
        for (int i = 0; i < MAX_BALLS; i++) {
            if (_balls[i].isActive()) {
                _balls[i].draw(_display);
            }
        }
    
        for (int i = 0; i < _numItems; i++) {
            if (_items[i].isActive()) {
                _items[i].draw(_display);
            }
        }
    }

    if (_gameOver) {
        bool allBlocksInactive = true;
        for (int i = 0; i < _blockCount; i++) {
            if (_blocks[i].isActive()) {
                allBlocksInactive = false;
                break;
            }
        }
    
        if (allBlocksInactive) {
            _drawCenteredText("YOU WIN", SCREEN_HEIGHT / 2 - 4);
        } else {
            _drawCenteredText("GAME OVER", SCREEN_HEIGHT / 2 - 4);
        }
        
    }

    _display.display();
}

// Genera un nivel a partir del mapa.
void BlockBreaker::_generateLevel(int levelIndex) {
    _blockCount = 0;
    const int (*currentMap)[NUM_COLS] = _allLevelsMap[levelIndex];
    const int gap = 2;
    const int startX = 10;
    const int startY = 10;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (currentMap[row][col] == 1) {
                int blockX = startX + col * (BLOCK_WIDTH + gap);
                int blockY = startY + row * (BLOCK_HEIGHT + gap);
                _blocks[_blockCount] = Block(blockX, blockY, BLOCK_WIDTH, BLOCK_HEIGHT);
                _blockCount++;
            }
        }
    }
}

// Genera un float aleatorio.
float BlockBreaker::_randomFloat(float minVal, float maxVal) {
    return minVal + ((float)random(0, 1000) / 1000.0) * (maxVal - minVal);
}

// Dibuja texto centrado.
void BlockBreaker::_drawCenteredText(String msg, int y) {
    int x = (SCREEN_WIDTH - msg.length() * 6) / 2;
    _display.setCursor(x, y);
    _display.println(msg);
}