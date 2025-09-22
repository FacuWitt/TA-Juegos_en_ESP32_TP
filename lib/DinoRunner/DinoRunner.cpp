#include "DinoRunner.h"

// Static variable initialization
unsigned long DinoRunner::_highScore = 0;

// Detailed Chrome Dino style sprites (16x16 for dino, various sizes for obstacles)

// T-Rex running frame 1 (20x12) 
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

// T-Rex running frame 2 (20x12) - piernas alternadas
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

// T-Rex jumping (20x12) - piernas recogidas
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

// Small cactus (6x12) - Chrome Dino style
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

// Large cactus (8x16) - Chrome Dino style  
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

// Pterodactyl flying frame 1 (16x12) - Wings DOWN, right-facing
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

// Pterodactyl flying frame 2 (16x12) - Wings UP, right-facing
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
    
    // Initialize obstacles
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
    
    // Initialize dino
    _dinoX = 20;
    _dinoY = GROUND_Y - DINO_HEIGHT;
    _dinoVelY = 0;
    _isJumping = false;
    _isOnGround = true;
    
    // Clear obstacles
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        _obstacles[i].isActive = false;
    }
    
    _obstacleSpawnTimer = 0;
    _obstacleSpawnDelay = 60; // frames between obstacles (more frequent spawning)
    
    _lastUpdate = millis();
    _lastObstacle = millis();
}

void DinoRunner::checkButtons() {
    // Jump button (W)
    if(digitalRead(BTN_W_PIN) == HIGH && _isOnGround && !_gameOver) {
        _dinoVelY = -JUMP_FORCE;
        _isJumping = true;
        _isOnGround = false;
        delay(100); // Simple debouncing
    }
    
    // Back to menu button (A) or restart if game over
    if(digitalRead(BTN_A_PIN) == HIGH) {
        if(_gameOver) {
            initGame(); // Restart game
        } else {
            _running = false; // Back to menu
        }
        delay(200); // Simple debouncing
    }
}

void DinoRunner::update() {
    // Update animation
    unsigned long currentTime = millis();
    if(currentTime - _lastAnimUpdate >= _animDelay) {
        _animFrame = (_animFrame + 1) % 2; // Toggle between 0 and 1
        _lastAnimUpdate = currentTime;
    }
    
    // Update score
    _scoreIncrement++;
    if(_scoreIncrement >= 10) { // Increment score every 10 frames
        _score++;
        _scoreIncrement = 0;
        
        // Increase difficulty more aggressively over time
        if(_score % 100 == 0 && _obstacleSpawnDelay > 25) {
            _obstacleSpawnDelay -= 2;
        }
    }
    
    updateDino();
    updateObstacles();
    checkCollisions();
}

void DinoRunner::updateDino() {
    // Apply gravity
    if(!_isOnGround) {
        _dinoVelY += GRAVITY;
        _dinoY += _dinoVelY;
        
        // Check if landed
        if(_dinoY >= GROUND_Y - DINO_HEIGHT) {
            _dinoY = GROUND_Y - DINO_HEIGHT;
            _dinoVelY = 0;
            _isJumping = false;
            _isOnGround = true;
        }
    }
}

void DinoRunner::updateObstacles() {
    // Move existing obstacles
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(_obstacles[i].isActive) {
            _obstacles[i].x -= GAME_SPEED;
            
            // Deactivate obstacles that moved off screen
            if(_obstacles[i].x + _obstacles[i].width < 0) {
                _obstacles[i].isActive = false;
            }
        }
    }
    
    // Spawn new obstacles
    _obstacleSpawnTimer++;
    if(_obstacleSpawnTimer >= _obstacleSpawnDelay) {
        spawnObstacle();
        _obstacleSpawnTimer = 0;
    }
}

void DinoRunner::spawnObstacle() {
    // Find an inactive obstacle slot
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(!_obstacles[i].isActive) {
            _obstacles[i].isActive = true;
            _obstacles[i].x = SCREEN_WIDTH + 10;
            
            // Randomly choose between cactus and bird
            if(random(0, 100) < 70) { // 70% chance for cactus
                _obstacles[i].isBird = false;
                // Randomly choose between small and large cactus
                if(random(0, 100) < 60) { // 60% small cactus
                    _obstacles[i].isLarge = false;
                    _obstacles[i].y = GROUND_Y - SMALL_CACTUS_HEIGHT;
                    _obstacles[i].width = SMALL_CACTUS_WIDTH;
                    _obstacles[i].height = SMALL_CACTUS_HEIGHT;
                } else { // 40% large cactus
                    _obstacles[i].isLarge = true;
                    _obstacles[i].y = GROUND_Y - LARGE_CACTUS_HEIGHT;
                    _obstacles[i].width = LARGE_CACTUS_WIDTH;
                    _obstacles[i].height = LARGE_CACTUS_HEIGHT;
                }
            } else { // 30% chance for bird
                _obstacles[i].isBird = true;
                _obstacles[i].isLarge = false;
                _obstacles[i].y = GROUND_Y - DINO_HEIGHT - BIRD_HEIGHT - 8; // Flying height
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
            // Reduce hitboxes by 2 pixels on each side for more forgiving collisions
            int dinoHitX = _dinoX + 2;
            int dinoHitY = _dinoY + 2;
            int dinoHitW = DINO_WIDTH - 6;
            int dinoHitH = DINO_HEIGHT - 6;
            
            int obsHitX = _obstacles[i].x + 1;
            int obsHitY = _obstacles[i].y + 1;
            int obsHitW = _obstacles[i].width - 3;
            int obsHitH = _obstacles[i].height - 3;
            
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
    
    // Update high score
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
        // Game over screen
        _display.setTextSize(1);
        _display.setTextColor(SSD1306_WHITE);
        _display.setCursor(30, 20);
        _display.println("GAME OVER");
        
        _display.setCursor(20, 35);
        _display.print("Press A to restart");
    }
    
    _display.display();
}

void DinoRunner::drawGround() {
    // Draw ground line
    _display.drawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, SSD1306_WHITE);
}

void DinoRunner::drawDino() {
    // Use appropriate sprite based on dino state
    if(_isOnGround) {
        // Running animation
        if(_animFrame == 0) {
            _display.drawBitmap(_dinoX, _dinoY, _dinoRun1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
        } else {
            _display.drawBitmap(_dinoX, _dinoY, _dinoRun2, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
        }
    } else {
        // Jumping sprite
        _display.drawBitmap(_dinoX, _dinoY, _dinoJump, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
    }
}

void DinoRunner::drawObstacles() {
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(_obstacles[i].isActive) {
            if(_obstacles[i].isBird) {
                // Draw pterodactyl with wing animation
                if(_animFrame == 0) {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _birdFly1, BIRD_WIDTH, BIRD_HEIGHT, SSD1306_WHITE);
                } else {
                    _display.drawBitmap(_obstacles[i].x, _obstacles[i].y, 
                                      _birdFly2, BIRD_WIDTH, BIRD_HEIGHT, SSD1306_WHITE);
                }
            } else {
                // Draw cactus (small or large)
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
    
    // Current score
    _display.setCursor(0, 0);
    _display.print("Score: ");
    _display.println(_score);
    
    // High score
    _display.setCursor(0, 10);
    _display.print("Best: ");
    _display.println(_highScore);
    
    // Simple controls hint
    if(_score < 50) { // Show controls for new players
        _display.setCursor(70, 0);
        _display.println("W=Jump");
        _display.setCursor(70, 10);
        _display.println("A=Menu");
    }
}
