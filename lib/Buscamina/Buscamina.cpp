#include "Buscamina.h"
#include <Fonts/TomThumb.h> // Para la fuente

#define BTN_W_PIN 19 // P1 UP
#define BTN_A_PIN 18 // P1 DOWN
#define BTN_S_PIN 5  // P2 DOWN
#define BTN_D_PIN 17 // P2 UP
#define BTN_T_PIN 16 // EXIT
#define BTN_DESC_PIN 4 // Destapar
#define BTN_BAND_PIN 2 // Bandera

// Constructor: Inicializa la referencia a la pantalla y los pines
Buscamina::Buscamina(Adafruit_SSD1306 &disp): _display(disp)
{    
    initGrid();
    inicio_tiempo = millis(); // Guarda el tiempo de inicio
}

// Metodo de Inicio
void Buscamina::initGrid() {

    pinMode(BTN_W_PIN, INPUT_PULLDOWN);
    pinMode(BTN_A_PIN, INPUT_PULLDOWN);
    pinMode(BTN_S_PIN, INPUT_PULLDOWN);
    pinMode(BTN_D_PIN, INPUT_PULLDOWN);
    pinMode(BTN_T_PIN, INPUT_PULLDOWN);
    pinMode(BTN_DESC_PIN, INPUT_PULLUP);
    pinMode(BTN_BAND_PIN, INPUT_PULLUP);
    // Reiniciar estado
    juego_terminado = false;
    juego_ganado = false;
    
    // Generando minas...
    int cantidad_bombas_generadas = 0;
    for(int f = 0; f < GRID_ROWS; f++){
        for(int c = 0; c < GRID_COLS; c++){
            int numero = random(0, 99);
            if (cantidad_bombas_generadas < total_minas && numero < 29){ // total_minas como límite
                tablero[f][c] = -1;
                cantidad_bombas_generadas++;
            } else {
                tablero[f][c] = 0;
            }
            descubierto[f][c] = 0;
        }
    }
    total_minas = cantidad_bombas_generadas; // Ajusta total_minas si la generación fue variable

    // Calculando minas de celdas vacias
    for(int f = 0; f < GRID_ROWS; f++){
        for(int c = 0; c < GRID_COLS; c++){
            if(tablero[f][c] != -1){
                int contadorBombasVecinas = 0;
                for(int dy = -1; dy < 2; dy++){
                    for(int dx = -1; dx < 2; dx++){
                        if (dx != 0 || dy != 0){ 
                            int nx = c + dx;
                            int ny = f + dy;
                            if (ny >= 0 && ny < GRID_ROWS && nx >= 0 && nx < GRID_COLS){ 
                                if(tablero[ny][nx] == -1){
                                    contadorBombasVecinas ++;
                                }                            }
                        }
                    }
                }
                tablero[f][c] = contadorBombasVecinas;
            }
        }
    }
    Serial.println("Tablero inicializado:");
}

// Manejo de Entradas y Lógica de Botones 

void Buscamina::handleInput() {
    //cálculo de posición
    int valor_w = digitalRead(BTN_W_PIN);
    int valor_d = digitalRead(BTN_D_PIN);
    int valor_s = digitalRead(BTN_S_PIN);
    int valor_a = digitalRead(BTN_A_PIN);

    if(valor_w == HIGH && ultimo_estado_w == LOW){
        if (fila_cursor > 0){
            fila_cursor -= 1;
        }
        else{
            fila_cursor = 7;
        }
    }
    ultimo_estado_w = valor_w;

    if(valor_s == HIGH && ultimo_estado_s == LOW){
        if(fila_cursor < 7){
            fila_cursor += 1;
        }
        else{
            fila_cursor = 0;
        }
    }
    ultimo_estado_s = valor_s;

    if(valor_a == HIGH && ultimo_estado_a == LOW){
        if(columna_cursor > 0){
            columna_cursor -= 1;
        }
        else {
            columna_cursor = 15;
        }
    }
    ultimo_estado_a = valor_a;

    if(valor_d == HIGH && ultimo_estado_d == LOW){
        if(columna_cursor < 15){
            columna_cursor +=1;
        }
        else{
            columna_cursor = 0;
        }
    }
    ultimo_estado_d = valor_d;

    //fila_cursor = (indice / GRID_COLS); 
    //columna_cursor = indice % GRID_COLS;

    // Logica del Botón de Descubrir
    int estado_actual_desc = digitalRead(BTN_DESC_PIN);
    if (estado_actual_desc == LOW && ultimo_estado_desc == HIGH) {
        if (descubierto[fila_cursor][columna_cursor] != 2) { 
           destapar_celda(columna_cursor, fila_cursor);
        }
    }
    ultimo_estado_desc = estado_actual_desc; 

    // Logica del Botón de Bandera
    int estado_actual_band = digitalRead(BTN_BAND_PIN);
    if (estado_actual_band == LOW && ultimo_estado_band == HIGH) {
        if (descubierto[fila_cursor][columna_cursor] == 0) {
            descubierto[fila_cursor][columna_cursor] = 2; // Poner bandera
        } else if (descubierto[fila_cursor][columna_cursor] == 2) {
            descubierto[fila_cursor][columna_cursor] = 0; // Quitar bandera
        }
    }
    ultimo_estado_band = estado_actual_band;
}

// Metodo principal
void Buscamina::run() {
    // Resetear el juego antes de empezar
    initGrid();
    inicio_tiempo = millis();
    
    while (!juego_terminado) {
        // Actualiza el tiempo transcurrido
        contador_tiempo = millis() - inicio_tiempo; 

        handleInput(); 

        // Recontar banderas
        contador_banderas = 0;
        for(int f = 0; f < GRID_ROWS; f++){
            for(int c = 0; c < GRID_COLS; c++){
                if (descubierto[f][c] == 2) {
                    contador_banderas++;
                }
            }
        }

        // Chequeo de Victoria
        verificar_victoria(); 

        // Dibujo
        drawGrid();

        delay(50); // delay
    }
    
    // Termina el loop y se dibuja la pantalla de finalizacion
    drawGameOver();
    delay(5000); // 5 segundos para ver resultados
    _display.clearDisplay();
    _display.setFont(NULL);
}

// Lógica del Juego 
void Buscamina::destapar_celda(int x, int y){
    // Validacidar límites
    if (y < 0 || y >= GRID_ROWS || x < 0 || x >= GRID_COLS) return;

    // Validación si ya esta destapado o tiene bandera
    if(descubierto[y][x] == 1 || descubierto[y][x] == 2) return; 

    descubierto[y][x] = 1; // Marcar como descubierto

    if (tablero[y][x] == -1){
        juego_terminado = true;
        juego_ganado = false;
        return;
    }
    if (tablero[y][x] == 0){
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx != 0 || dy != 0) {
                    int nx = x + dx;
                    int ny = y + dy;
                    destapar_celda(nx, ny);
                }
            }
        }
    }
}

void Buscamina::verificar_victoria() {
    if (juego_terminado) return;

    int celdas_descubiertas_sin_mina = 0;
    for(int f = 0; f < GRID_ROWS; f++){
        for(int c = 0; c < GRID_COLS; c++){
            // Solo se cuentan las celdas seguras que ya estan descubiertas
            if (descubierto[f][c] == 1 && tablero[f][c] != -1) {
                celdas_descubiertas_sin_mina++;
            }
        }
    }
    
    if (celdas_descubiertas_sin_mina == (GRID_ROWS * GRID_COLS - total_minas)) {
        juego_terminado = true;
        juego_ganado = true;
    }
}

// Metodos de Dibujo

void Buscamina::drawGrid() {
    _display.clearDisplay();
    _display.setFont(&TomThumb);
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);

    for(int f = 0; f < GRID_ROWS; f++){
        for(int c = 0; c < GRID_COLS; c++){
            // Dibuja el marco de la celda
            _display.drawRect(c*8, f*8, 8, 8, SSD1306_WHITE);

            if(descubierto[f][c] == 1){
                // Celda Descubierta
                int valor = tablero[f][c];
                if(valor == -1){
                  // Mina
                  _display.fillCircle(c * 8 + 4, f * 8 + 4, 3, SSD1306_WHITE);
                }
                else if(valor != 0){
                  // Número de minas
                  _display.setCursor(c * 8 + 2, f * 8 + 7);
                  _display.print(valor);
                }
            }
            else if(descubierto[f][c] == 2){
                // Celda con Bandera
                _display.fillTriangle(
                  c * 8 + 2, f * 8 + 6,
                  c * 8 + 2, f * 8 + 2,
                  c * 8 + 6, f * 8 + 4,
                  SSD1306_WHITE
                );
            }
            else{ // descubierto[f][c] == 0 (Celda Tapada)
                // Relleno de NEGRO para que el marco BLANCO se vea
                _display.fillRect(c*8 , f*8 , 7, 7, SSD1306_BLACK);
            }
        }
    }
    
    // Dibujar Cursor
    int f = fila_cursor;
    int c = columna_cursor;

    if (descubierto[f][c] == 0) {
        // Si está tapada (negra) se rellena con blanco
        _display.fillRect(c * 8, f * 8, 8, 8, SSD1306_WHITE);
        // Marco interno de negro
        _display.drawRect(c * 8 + 1, f * 8 + 1, 6, 6, SSD1306_BLACK);
    } else {
        // Si está descubierta o con bandera, dibuja un borde negro para resaltar
        _display.drawRect(c * 8, f * 8, 8, 8, SSD1306_BLACK); 
        _display.drawRect(c * 8 + 1, f * 8 + 1, 6, 6, SSD1306_WHITE);
    }

    _display.display();
}

void Buscamina::drawGameOver() {
    _display.clearDisplay();
    _display.setTextColor(SSD1306_WHITE);

    // Mostrar estado: GANASTE o GAME OVER
    _display.setTextSize(2);
    if (juego_ganado) {
        _display.setCursor(5, 10);
        _display.println("GANASTE!");
    } else {
        _display.setCursor(5, 10);
        _display.println("GAME OVER");
    }

    // Mostrar tiempo en segundos
    _display.setTextSize(1);
    _display.setCursor(5, 35);
    _display.print("TIEMPO: ");
    _display.print(contador_tiempo / 1000.0f, 1); 
    _display.print("s");


    // Mostrar Banderas
    _display.setCursor(5, 50);
    _display.print("BANDERAS: ");
    _display.print(contador_banderas);
    
    // Mostrar minas totales
    _display.setCursor(5, 60);
    _display.print("MINAS TOTALES: ");
    _display.print(total_minas);
    
    _display.display();
}