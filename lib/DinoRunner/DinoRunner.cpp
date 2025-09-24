#include "DinoRunner.h"

unsigned long DinoRunner::_highScore = 0;

// (20x12)
const unsigned char DinoRunner::_dinoRun1[] PROGMEM = {
  0x00, 0x3F, 0xF0, // ..........##########
  0x00, 0x33, 0xF0, // ..........##..######
  0x00, 0x3D, 0xF0, // ..........####.#####
  0x00, 0x3F, 0xC0, // ..........########..
  0x81, 0xFC, 0x00, // #......#######......
  0xE7, 0xFF, 0x00, // ###..###########....
  0xFF, 0xFC, 0x00, // ##############......
  0x3F, 0xF8, 0x00, // ..###########.......
  0x1F, 0xF0, 0x00, // ...#########........
  0x07, 0x60, 0x00, // .....###.##.........
  0x06, 0x30, 0x00, // .....##...##........
  0x06, 0x30, 0x00, // .....##...##........
};

// (20x12)
const unsigned char DinoRunner::_dinoRun2[] PROGMEM = {
  0x00, 0x3F, 0xF0, // ..........##########
  0x00, 0x33, 0xF0, // ..........##..######
  0x00, 0x3D, 0xF0, // ..........####.#####
  0x00, 0x3F, 0xC0, // ..........########..
  0x81, 0xFC, 0x00, // #......#######......
  0xE7, 0xFF, 0x00, // ###..###########....
  0xFF, 0xFC, 0x00, // ##############......
  0x3F, 0xF8, 0x00, // ..###########.......
  0x1F, 0xF0, 0x00, // ...#########........
  0x06, 0x18, 0x00, // .....##....##.......
  0x06, 0x00, 0x00, // .....##.............
  0x00, 0x18, 0x00, // ...........##.......
};

// (20x12)
const unsigned char DinoRunner::_dinoJump[] PROGMEM = {
  0x00, 0x3F, 0xF0, // ..........##########
  0x00, 0x33, 0xF0, // ..........##..######
  0x00, 0x3D, 0xF0, // ..........####.#####
  0x00, 0x3F, 0xC0, // ..........########..
  0x81, 0xFC, 0x00, // #......#######......
  0xE7, 0xFF, 0x00, // ###..###########....
  0xFF, 0xFC, 0x00, // ##############......
  0x3F, 0xF8, 0x00, // ..###########.......
  0x1F, 0xF0, 0x00, // ...#########........
  0x03, 0x30, 0x00, // ......##..##........
  0x03, 0x30, 0x00, // ......##..##........
  0x00, 0x00, 0x00, // ....................
};

// (6x12)
const unsigned char DinoRunner::_smallCactus[] PROGMEM = {
  0x30, // ..##....
  0x30, // ..##....
  0x30, // ..##....
  0xB4, // #.##.#..
  0xB4, // #.##.#..
  0x30, // ..##....
  0x30, // ..##....
  0x30, // ..##....
  0x30, // ..##....
  0x30, // ..##....
  0x30, // ..##....
  0x30  // ..##....
};

// (8x16)
const unsigned char DinoRunner::_largeCactus[] PROGMEM = {
  0x18, // ...##...
  0x18, // ...##...
  0x18, // ...##...
  0x5A, // .#.##.#.
  0x5A, // .#.##.#.
  0x18, // ...##...
  0x18, // ...##...
  0x18, // ...##...
  0x18, // ...##...
  0x5A, // .#.##.#.
  0x5A, // .#.##.#.
  0x18, // ...##...
  0x18, // ...##...
  0x18, // ...##...
  0x18, // ...##...
  0x18  // ...##...
};

// (16x12)
const unsigned char DinoRunner::_birdFly1[] PROGMEM = {
  0x00, 0x00, // ................
  0x03, 0x00, // ......##........
  0x07, 0x80, // .....####.......
  0x0F, 0xC0, // ....######......
  0x1F, 0xCC, // ...#######..##..
  0xFF, 0xEE, // ###########.###.
  0x07, 0xDE, // .....#####.####.
  0x03, 0xF3, // ......####..##..
  0x01, 0xE0, // .......###......
  0x00, 0x60, // .........##.....
  0x00, 0x10, // ..........#.....
  0x00, 0x10  // ..........#.....
};

// (16x12)
const unsigned char DinoRunner::_birdFly2[] PROGMEM = {
  0x06, 0x00, // .....##.........
  0x0F, 0x00, // ....####........
  0x1F, 0x80, // ...######.......
  0x3F, 0x90, // ..#######..#....
  0x1F, 0x38, // ...#####..###...
  0x03, 0xEE, // ......###.####..
  0x01, 0xCE, // .......##..###..
  0x00, 0x4C, // ........#..##...
  0x00, 0x50, // .........#.#....
  0x00, 0x30, // ..........##....
  0x00, 0x10, // ...........#....
  0x00, 0x10  // ...........#....
};

DinoRunner::DinoRunner(Adafruit_SSD1306 &disp) : _display(disp) {
    _running = false;
    _gameOver = false;
    _lastUpdate = 0;
    _lastObstacle = 0;
    _score = 0;
    _scoreIncrement = 0;
    _animFrame = 0;
    _lastAnimUpdate = 0;
    
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        _obstacles[i].isActive = false;
    }
}

void DinoRunner::run() {
    initGame();
    
    while(_running) {
        unsigned long currentTime = millis();
        
        if(currentTime - _lastUpdate >= _frameTime) {
            checkButtons();
            
            if(!_gameOver) {
                update();
            }
            
            draw();
            _lastUpdate = currentTime;
        }
    }
}

void DinoRunner::initGame() {
    _running = true;
    _gameOver = false;
    _score = 0;
    _scoreIncrement = 0;
    
    _dinoX = 20;
    _dinoY = GROUND_Y - DINO_HEIGHT;
    _dinoVelY = 0;
    _isJumping = false;
    _isOnGround = true;
    
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        _obstacles[i].isActive = false;
    }
    
    _obstacleSpawnTimer = 0;
    _obstacleSpawnDelay = 60;
    
    _lastUpdate = millis();
    _lastObstacle = millis();
}

void DinoRunner::checkButtons() {
    if(digitalRead(BTN_W_PIN) == HIGH && _isOnGround && !_gameOver) {
        _dinoVelY = -JUMP_FORCE;
        _isJumping = true;
        _isOnGround = false;
        delay(100);
    }
    
    if(digitalRead(BTN_T_PIN) == HIGH) {
        _running = false;
        delay(200);
    }
    
    if(digitalRead(BTN_A_PIN) == HIGH && _gameOver) {
        initGame();
        delay(200);
    }
}

void DinoRunner::update() {
    unsigned long currentTime = millis();
    if(currentTime - _lastAnimUpdate >= _animDelay) {
        _animFrame = (_animFrame + 1) % 2;
        _lastAnimUpdate = currentTime;
    }
    
    _scoreIncrement++;
    if(_scoreIncrement >= 10) {
        _score++;
        _scoreIncrement = 0;
        
        if(_score % 100 == 0 && _obstacleSpawnDelay > 25) {
            _obstacleSpawnDelay -= 2;
        }
    }
    
    updateDino();
    updateObstacles();
    checkCollisions();
}

void DinoRunner::updateDino() {
    if(!_isOnGround) {
        _dinoVelY += GRAVITY;
        _dinoY += _dinoVelY;
        
        if(_dinoY >= GROUND_Y - DINO_HEIGHT) {
            _dinoY = GROUND_Y - DINO_HEIGHT;
            _dinoVelY = 0;
            _isJumping = false;
            _isOnGround = true;
        }
    }
}

void DinoRunner::updateObstacles() {
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(_obstacles[i].isActive) {
            _obstacles[i].x -= GAME_SPEED;
            
            if(_obstacles[i].x + _obstacles[i].width < 0) {
                _obstacles[i].isActive = false;
            }
        }
    }
    
    _obstacleSpawnTimer++;
    if(_obstacleSpawnTimer >= _obstacleSpawnDelay) {
        spawnObstacle();
        _obstacleSpawnTimer = 0;
    }
}

void DinoRunner::spawnObstacle() {
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(!_obstacles[i].isActive) {
            _obstacles[i].isActive = true;
            _obstacles[i].x = SCREEN_WIDTH + 10;
            
            if(random(0, 100) < 70) {
                _obstacles[i].isBird = false;
                
                if(random(0, 100) < 60) {
                    _obstacles[i].isLarge = false;
                    _obstacles[i].y = GROUND_Y - SMALL_CACTUS_HEIGHT;
                    _obstacles[i].width = SMALL_CACTUS_WIDTH;
                    _obstacles[i].height = SMALL_CACTUS_HEIGHT;
                } else {
                    _obstacles[i].isLarge = true;
                    _obstacles[i].y = GROUND_Y - LARGE_CACTUS_HEIGHT;
                    _obstacles[i].width = LARGE_CACTUS_WIDTH;
                    _obstacles[i].height = LARGE_CACTUS_HEIGHT;
                }
            } else {
                _obstacles[i].isBird = true;
                _obstacles[i].isLarge = false;
                _obstacles[i].y = GROUND_Y - DINO_HEIGHT - BIRD_HEIGHT - 8;
                _obstacles[i].width = BIRD_WIDTH;
                _obstacles[i].height = BIRD_HEIGHT;
            }
            break;
        }
    }
}

void DinoRunner::checkCollisions() {
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(_obstacles[i].isActive) {
            int dinoHitX = _dinoX + 2;
            int dinoHitY = _dinoY + 2;
            int dinoHitW = DINO_WIDTH - 4;
            int dinoHitH = DINO_HEIGHT - 4;
            
            int obsHitX = _obstacles[i].x + 1;
            int obsHitY = _obstacles[i].y + 1;
            int obsHitW = _obstacles[i].width - 2;
            int obsHitH = _obstacles[i].height - 2;
            
            if(isColliding(dinoHitX, dinoHitY, dinoHitW, dinoHitH,
                          obsHitX, obsHitY, obsHitW, obsHitH)) {
                gameOver();
                return;
            }
        }
    }
}

bool DinoRunner::isColliding(int dinoX, int dinoY, int dinoW, int dinoH, 
                            int obsX, int obsY, int obsW, int obsH) {
    return (dinoX < obsX + obsW &&
            dinoX + dinoW > obsX &&
            dinoY < obsY + obsH &&
            dinoY + dinoH > obsY);
}

void DinoRunner::gameOver() {
    _gameOver = true;
    
    if(_score > _highScore) {
        _highScore = _score;
    }
}

void DinoRunner::draw() {
    _display.clearDisplay();
    
    drawGround();
    drawDino();
    drawObstacles();
    drawUI();
    
    if(_gameOver) {
        _display.setTextSize(1);
        _display.setTextColor(SSD1306_WHITE);
        _display.setCursor(30, 20);
        _display.println("GAME OVER");
        
        _display.setCursor(20, 35);
        _display.println("A=Restart T=Menu");
    }
    
    _display.display();
}

void DinoRunner::drawGround() {
    _display.drawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, SSD1306_WHITE);
}

void DinoRunner::drawDino() {
    if(_isOnGround) {
        if(_animFrame == 0) {
            _display.drawBitmap(_dinoX, _dinoY, _dinoRun1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
        } else {
            _display.drawBitmap(_dinoX, _dinoY, _dinoRun2, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
        }
    } else {
        _display.drawBitmap(_dinoX, _dinoY, _dinoJump, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
    }
}

void DinoRunner::drawObstacles() {
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(_obstacles[i].isActive) {
            if(_obstacles[i].isBird) {
                if(_animFrame == 0) {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _birdFly1, BIRD_WIDTH, BIRD_HEIGHT, SSD1306_WHITE);
                } else {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _birdFly2, BIRD_WIDTH, BIRD_HEIGHT, SSD1306_WHITE);
                }
            } else {
                if(_obstacles[i].isLarge) {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _largeCactus, LARGE_CACTUS_WIDTH, LARGE_CACTUS_HEIGHT, SSD1306_WHITE);
                } else {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _smallCactus, SMALL_CACTUS_WIDTH, SMALL_CACTUS_HEIGHT, SSD1306_WHITE);
                }
            }
        }
    }
}

void DinoRunner::drawUI() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    
    _display.setCursor(0, 0);
    _display.print("Score: ");
    _display.println(_score);
    
    _display.setCursor(0, 10);
    _display.print("Best: ");
    _display.println(_highScore);
    
    if(_score < 50) {
        _display.setCursor(70, 0);
        _display.println("W=Jump");
        _display.setCursor(70, 10);
        _display.println("T=Menu");
    }
}