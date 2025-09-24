#include "Pong.h"

#define BTN_W_PIN 19 // P1 UP
#define BTN_A_PIN 18 // P1 DOWN
#define BTN_S_PIN 5  // P2 DOWN
#define BTN_D_PIN 17 // P2 UP
#define BTN_T_PIN 16 // EXIT

Pong::Pong(Adafruit_SSD1306 &disp) : _display(disp)
{
    // Inicialización de variables
    _ball_pos_x = 64;
    _ball_pos_y = 32;
    _vel_x = 2;
    _vel_y = 0;
    _vel_pal = 2; // pal = paleta
    _p1_y = 26;
    _p2_y = 26;
    _score_p1 = 0;
    _score_p2 = 0;
    _cant_toques = 0;

    // Configurar pines de botones
    pinMode(BTN_W_PIN, INPUT_PULLDOWN);
    pinMode(BTN_A_PIN, INPUT_PULLDOWN);
    pinMode(BTN_S_PIN, INPUT_PULLDOWN);
    pinMode(BTN_D_PIN, INPUT_PULLDOWN);
    pinMode(BTN_T_PIN, INPUT_PULLDOWN);
}

void Pong::run() {
    bool running = true;

    draw();
    delay(1000); // Pausa antes de iniciar el juego
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

void Pong::update() { // donde sucede la logica del juego
    digitalRead(BTN_W_PIN);
    digitalRead(BTN_A_PIN);
    digitalRead(BTN_S_PIN);
    digitalRead(BTN_D_PIN);
    
    // movimiento de la bola
    _ball_pos_x += _vel_x;
    _ball_pos_y += _vel_y;

    // movimiento de las paletas
    if (digitalRead(BTN_W_PIN) == HIGH && digitalRead(BTN_A_PIN) == LOW && _p1_y > 0) {
        _p1_y -= _vel_pal;
    }
    if (digitalRead(BTN_A_PIN) == HIGH && _p1_y < 52) {
        _p1_y += _vel_pal;
    }
    if (digitalRead(BTN_D_PIN) == HIGH && digitalRead(BTN_S_PIN) == LOW && _p2_y > 0) {
        _p2_y -= _vel_pal;
    }
    if (digitalRead(BTN_S_PIN) == HIGH && _p2_y < 52) {
        _p2_y += _vel_pal;
    }

    // colisiones con las paletas
    if (4 <= _ball_pos_x && _ball_pos_x <= 6 && _ball_pos_y >= _p1_y && _ball_pos_y <= _p1_y + 12)
    {
        _vel_x = -_vel_x;
        _vel_y += (_ball_pos_y - (_p1_y + 6)) / 3; // La vel vertical depende de donde la pelota golpea la paleta
        _cant_toques++;
    }
    else if (122 <= _ball_pos_x && _ball_pos_x <= 124 && _ball_pos_y >= _p2_y && _ball_pos_y <= _p2_y + 12)
    {
        _vel_x = -_vel_x;
        _vel_y += (_ball_pos_y - (_p2_y + 6)) / 3; // La vel vertical depende de donde la pelota golpea la paleta
        _cant_toques++;
    }
    // colisiones con los bordes superior e inferior
    if (_ball_pos_y <= 0 || _ball_pos_y >= 63)
    {
        _vel_y = -_vel_y;
    }

    if (_cant_toques > 5) {
        _vel_x *= 1.1;
        _cant_toques = 0;
    }


    // goles
    if (_ball_pos_x <= 0)
    {
        goal();
        _score_p2++;
        _ball_pos_x = 64;
        _ball_pos_y = 32;
        _vel_y = 0;
        _cant_toques = 0;
        _vel_x = 2;
    }
    else if (_ball_pos_x >= 128)
    {
        goal();
        _score_p1++;
        _ball_pos_x = 64;
        _ball_pos_y = 32;
        _vel_y = 0;
        _cant_toques = 0;
        _vel_x = -2;
    }

}

void Pong::draw() {
    _display.clearDisplay();

    // Red
    _display.drawFastVLine(64, 0, 64, SSD1306_WHITE);

    // Puntajes
    _display.setCursor(50, 0);
    _display.printf("%02d %02d", _score_p1, _score_p2);

    // Bola
    _display.drawPixel(_ball_pos_x, _ball_pos_y, SSD1306_WHITE);

    // Paletas
    _display.fillRect(4, _p1_y, 2, 12, SSD1306_WHITE);   // Paleta P1
    _display.fillRect(122, _p2_y, 2, 12, SSD1306_WHITE); // Paleta P2

    _display.display();
}

void Pong::goal() { // Animacion de gol
        _display.clearDisplay();
    _display.setCursor(23, 20);
    _display.setTextSize(3);
    _display.fillRect(0, 13, 127, 36, SSD1306_WHITE);
    _display.setTextColor(SSD1306_BLACK);
    _display.print("GOAL!");
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.display();

    delay(500);
}