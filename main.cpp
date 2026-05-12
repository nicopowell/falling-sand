#include "raylib.h"

int main() {
    // 1. Inicialización
    const int screenWidth = 500;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Raylib - Guía Rápida");
    SetTargetFPS(60); // Sincroniza el juego a 60 frames por segundo

    // Celda y grilla
    const int CELL_SIZE = 5;
    const int GRID_WIDTH = screenWidth / CELL_SIZE;
    const int GRID_HEIGHT = screenHeight / CELL_SIZE;


    // 2. Bucle Principal
    while (!WindowShouldClose()) { // Detecta tecla ESC o botón de cerrar
        
        // --- Lógica de Actualización (Update) ---
        // Aquí van cálculos, colisiones y entrada de usuario

        // --- Dibujado (Draw) ---
        BeginDrawing();
            ClearBackground(BLACK); // Limpia el frame anterior

            // Dibujo la grilla
            for (int i = 0; i < GRID_HEIGHT; i++) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, (i+j)%2 == 0 ? WHITE : GRAY);
                }
            }

        EndDrawing();
    }

    // 3. Desinicialización
    CloseWindow(); 

    return 0;
}