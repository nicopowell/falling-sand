#include "raylib.h"
#include "core/Constants.h"
#include "simulation/Element.h"
#include "simulation/Simulation.h"

int main() {
    // 1. Inicialización
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Guía Rápida");
    SetTargetFPS(60); // Sincroniza el juego a 60 frames por segundo

    Simulation simulation;

    Vector2 cursorPosition;


    // 2. Bucle Principal
    while (!WindowShouldClose()) { // Detecta tecla ESC o botón de cerrar
        
        // --- Lógica de Actualización (Update) ---
        // Aquí van cálculos, colisiones y entrada de usuario
        cursorPosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            simulation.SetCell(cursorPosition, SAND);
        }

        simulation.Update();

        // --- Dibujado (Draw) ---
        BeginDrawing();
            ClearBackground(BLACK); // Limpia el frame anterior

            // Dibujo la grilla
            for (int i = 0; i < GRID_HEIGHT; i++) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, simulation.GetCell(i, j) == SAND ? YELLOW : BLACK);
                }
            }

        EndDrawing();
    }

    // 3. Desinicialización
    CloseWindow(); 

    return 0;
}