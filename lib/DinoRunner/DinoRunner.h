#ifndef DINORUNNER_H
#define DINORUNNER_H

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

struct Obstacle {
    int x, y;
    int width, height;
    bool isActive;
    bool isBird;
    bool isLarge;
};

class DinoRunner {
public:
    DinoRunner(Adafruit_SSD1306 &disp);
    
    void run();

private:
    Adafruit_SSD1306 &_display;
    
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int GROUND_Y = 50;
    
    static const int DINO_WIDTH = 20;
    static const int DINO_HEIGHT = 12;
    
    static const int SMALL_CACTUS_WIDTH = 6;
    static const int SMALL_CACTUS_HEIGHT = 12;
    
    static const int LARGE_CACTUS_WIDTH = 8;
    static const int LARGE_CACTUS_HEIGHT = 16;
    
    static const int BIRD_WIDTH = 16;
    static const int BIRD_HEIGHT = 12;
    
    static const int MAX_OBSTACLES = 5;
    
    static const int JUMP_FORCE = 9;
    static const int GRAVITY = 1;
    static const int GAME_SPEED = 3;
    
    static const int BTN_W_PIN = 19;
    static const int BTN_A_PIN = 18;
    static const int BTN_T_PIN = 16;
    
    bool _running;
    bool _gameOver;
    unsigned long _lastUpdate;
    unsigned long _lastObstacle;
    const int _frameTime = 50;
    
    int _dinoX;
    int _dinoY;
    int _dinoVelY;
    bool _isJumping;
    bool _isOnGround;
    
    unsigned long _score;
    static unsigned long _highScore;
    unsigned long _scoreIncrement;
    
    Obstacle _obstacles[MAX_OBSTACLES];
    int _obstacleSpawnTimer;
    int _obstacleSpawnDelay;
    
    int _animFrame;
    unsigned long _lastAnimUpdate;
    const int _animDelay = 200; 
    
    static const unsigned char _dinoRun1[] PROGMEM;
    static const unsigned char _dinoRun2[] PROGMEM;
    static const unsigned char _dinoJump[] PROGMEM;
    static const unsigned char _smallCactus[] PROGMEM;
    static const unsigned char _largeCactus[] PROGMEM;
    static const unsigned char _birdFly1[] PROGMEM;
    static const unsigned char _birdFly2[] PROGMEM;
    
    void initGame();
    
    void update();
    
    void draw();
    
    void checkButtons();
    
    void updateDino();
    
    void updateObstacles();
    
    void spawnObstacle();
    
    void checkCollisions();
    
    void gameOver();
    
    void drawDino();
    
    void drawObstacles();
    
    void drawGround();
    
    void drawUI();
    
    bool isColliding(int dinoX, int dinoY, int dinoW, int dinoH, 
                    int obsX, int obsY, int obsW, int obsH);
};

#endif