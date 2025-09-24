#include "FlappyBird.h"

#define BTN_W_PIN 19 // Saltar
#define BTN_D_PIN 17 // Aumentar velocidad
#define BTN_T_PIN 16 // EXIT

FlappyBird::FlappyBird(Adafruit_SSD1306 &disp) : _display(disp) {
    // Inicialización de variables
    birdY = 32; 
    velocity = 0;
    gravity = 1;
    jumpStrength = -3;
    pipeX = _display.width();
    pipeGap = 25;
    pipeWidth = 5;
    pipeSpeed = 1;
    score = 0;
    gameOver = false;
    dificultad = 0;

    // Configurar pines de botones
    pinMode(BTN_W_PIN, INPUT_PULLDOWN);
    pinMode(BTN_D_PIN, INPUT_PULLDOWN);
    pinMode(BTN_T_PIN, INPUT_PULLDOWN);
}

void FlappyBird::run() {
    bool running = true;
    begin();

    while (running) {
        update();
        draw();
        
        if (digitalRead(BTN_T_PIN) == HIGH) {
        // Salir del juego
            _display.clearDisplay();
            _display.setCursor(10, 20);
            _display.setTextSize(2);
            _display.print("Game Over");
            _display.display();
            running = false;
            delay(300);
        }
    }
}

void FlappyBird::begin() {
  reset();

  // Pantalla de inicio
  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(SSD1306_WHITE);
  _display.setCursor(25, 20);
  _display.println("Flappy Bird");
  _display.setCursor(28, 40);
  _display.println("Presiona W");
  _display.display();
  
  while (digitalRead(BTN_W_PIN) == LOW) {
    delay(10);
  }
}

void FlappyBird::reset() {
  birdY = 32; 
  velocity = 0;
  gravity = 1;
  jumpStrength = -3;
  pipeX = _display.width();
  pipeGap = 25;
  pipeWidth = 5;
  pipeSpeed = 1;
  score = 0;
  gameOver = false;
  dificultad = 0;
}

void FlappyBird::update() {
  if (!gameOver) {
    // Aumentar dificultad
    if (digitalRead(BTN_D_PIN) == HIGH) {
        dificultad++;
        if (dificultad > 10) dificultad = 10; 
        pipeGap = 35 - dificultad * 2; 
        if (pipeGap < 7) pipeGap = 7;  
        pipeSpeed += dificultad / 2;
        delay(200);
    }

    // Saltar
    if (digitalRead(BTN_W_PIN) == HIGH) velocity = jumpStrength;

    velocity += gravity;
    birdY += velocity;
    if (birdY < 0) birdY = 0;
    if (birdY > _display.height() - 1) birdY = _display.height() - 1;

    // Mover tuberías
    pipeX -= pipeSpeed;

    // Puntuación (cuando pasa tubería)
    if (pipeX + pipeWidth < 15 && !gameOver && birdY > 0) {
      score++;
      pipeX = _display.width();
    }

    // Colisiones
    int pipeTop = (_display.height() - pipeGap) / 2;
    int pipeBottom = pipeTop + pipeGap;
    if ((birdY < pipeTop || birdY > pipeBottom) && pipeX < 20 && pipeX > 0) {
      gameOver = true;
    }
  } else {
    // Reiniciar juego
    if (digitalRead(BTN_W_PIN) == HIGH) {
      reset();
      delay(500);
    }
  }
}

void FlappyBird::draw() {
  _display.clearDisplay();
  if (!gameOver) {
    _display.fillCircle(15, birdY, 3, SSD1306_WHITE);
    int pipeTop = (_display.height() - pipeGap) / 2;
    int pipeBottom = pipeTop + pipeGap;
    _display.fillRect(pipeX, 0, pipeWidth, pipeTop, SSD1306_WHITE);
    _display.fillRect(pipeX, pipeBottom, pipeWidth, _display.height() - pipeBottom, SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.print("Score: ");
    _display.print(score);
  } else {
    _display.setCursor(40, 20);
    _display.println("GAME OVER");
    _display.setCursor(40, 40);
    _display.print("Score: ");
    _display.print(score);
  }
  _display.display();
}
