#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Juegos
#include "Pong.h"
#include "Snake.h"
#include "FroggerGame.h"
#include "BlockBreaker.h"
#include "DinoRunner.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BTN_W_PIN 19
#define BTN_A_PIN 18
#define BTN_S_PIN 5
#define BTN_D_PIN 17

void drawMenu();
void checkButtons();

const char* menuItems[] = {
  "Ping-Pong",
  "Snake",
  "Frogger",
  "Block Breaker",
  "FLAPPY-BIRD",
  "BUSCAMINAS",
  "DINO-RUNNER"
};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);

int selectedItem = 0;  // índice del menú actual

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  pinMode(BTN_W_PIN, INPUT_PULLDOWN);
  pinMode(BTN_A_PIN, INPUT_PULLDOWN);
  pinMode(BTN_S_PIN, INPUT_PULLDOWN);
  pinMode(BTN_D_PIN, INPUT_PULLDOWN);
}

void loop() {
  drawMenu();
  // FroggerGame(display).run();
  checkButtons();
}


void drawMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Select: 'W' - 'S'");
  // display.println("");


  for (int i = 0; i < menuLength; i++) {
    if (i == selectedItem) {
      display.print("> ");
    } else {
      display.print("  ");
    }
    display.println(menuItems[i]);
  }

  display.println("");
  // display.println("Press 'D' to start");
  display.display();
}

void checkButtons() {
  if (digitalRead(BTN_W_PIN) == HIGH) {
    selectedItem--;
    if (selectedItem < 0) selectedItem = menuLength - 1;
    drawMenu();
    delay(10);
  }
  if (digitalRead(BTN_S_PIN) == HIGH) {
    selectedItem++;
    if (selectedItem >= menuLength) selectedItem = 0;
    drawMenu();
    delay(10);
  }
  if (digitalRead(BTN_D_PIN) == HIGH) {
    Serial.print("Juego seleccionado: ");
    Serial.println(menuItems[selectedItem]);
    switch (selectedItem) {
      case 0:
        Serial.println("Iniciando Pong...");
        Pong(display).run();
        break;
      case 1:
        // Iniciar Snake
        Snake(display).run();
        break;
      case 2:
        // Iniciar Frogger
        FroggerGame(display).run();
        break;

      case 3:
        // Iniciar Block Breaker
        BlockBreaker(display).run();
        break;
      
      case 4:
        // Iniciar Flappy Bird
        break;

      case 5:
        // Iniciar Buscaminas
        break;

      case 6:
        // Iniciar Dino Runner
        DinoRunner(display).run();
        break;
    }
    delay(200);
  }
}