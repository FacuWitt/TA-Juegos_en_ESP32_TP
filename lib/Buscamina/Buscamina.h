#ifndef BUSCAMINA_H
#define BUSCAMINA_H

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// Dimensiones del tablero
#define GRID_ROWS 8
#define GRID_COLS 16

class Buscamina {
public:
    // Constructor: Inicializa el juego pasando la referencia a la pantalla
    Buscamina(Adafruit_SSD1306 &disp);
    void run();

private:
    // Variables de Estado del Juego
    Adafruit_SSD1306 &_display;
    int tablero[GRID_ROWS][GRID_COLS];
    int descubierto[GRID_ROWS][GRID_COLS]; // 0: Tapado, 1: Descubierto, 2: Bandera
    
    // Estado del juego
    boolean juego_terminado = false;
    boolean juego_ganado = false;
    unsigned long inicio_tiempo; 
    int total_minas = 30;
    
    // Contadores y estado de entrada
    int contador_banderas = 0;
    unsigned long contador_tiempo = 0;
    int ultimo_estado_desc = HIGH; 
    int ultimo_estado_band = HIGH;
    int ultimo_estado_w = LOW; // Los botones WASD están en INPUT_PULLDOWN
    int ultimo_estado_a = LOW; 
    int ultimo_estado_s = LOW; 
    int ultimo_estado_d = LOW; 

    // Posición del cursor
    int fila_cursor = 0;
    int columna_cursor = 0;

    // Métodos del Juego
    void initGrid(); // Inicializa el tablero y calcula las minas
    void handleInput(); // Lee pot y botones
    void drawGrid(); // Dibuja el estado actual del juego
    void drawGameOver(); // Dibuja la pantalla de fin de juego
    void destapar_celda(int x, int y);
    void verificar_victoria();
};

#endif