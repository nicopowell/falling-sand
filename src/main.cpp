#include "raylib.h"
#include "core/Constants.h"
#include "simulation/Element.h"
#include "simulation/Simulation.h"

int main()
{
    // 1. Inicialización
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Guía Rápida");
    SetTargetFPS(60); // Sincroniza el juego a 60 frames por segundo

    Simulation simulation;
    Vector2 cursorPosition;

    int brushSize = 1;

    // 2. Bucle Principal
    while (!WindowShouldClose())
    { // Detecta tecla ESC o botón de cerrar

        // --- Lógica de Actualización (Update) ---
        // Aquí van cálculos, colisiones y entrada de usuario
        cursorPosition = GetMousePosition();

        brushSize += (int)GetMouseWheelMove();
        if (brushSize < 1)
            brushSize = 1;
        if (brushSize > 20)
            brushSize = 20;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            int cx = cursorPosition.x / CELL_SIZE;
            int cy = cursorPosition.y / CELL_SIZE;
            int r = brushSize;
            for (int dy = -r; dy <= r; dy++)
            {
                for (int dx = -r; dx <= r; dx++)
                {
                    if (dx * dx + dy * dy <= r * r)
                    {
                        simulation.SetCell(
                            (Vector2){
                                (float)((cx + dx) * CELL_SIZE),
                                (float)((cy + dy) * CELL_SIZE)},
                            SAND);
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_C)) simulation.Clear();

        simulation.Update();

        // --- Dibujado (Draw) ---
        BeginDrawing();
        ClearBackground(BLACK); // Limpia el frame anterior

        // Dibujo la grilla
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            for (int x = 0; x < GRID_WIDTH; x++)
            {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, simulation.GetCell(x, y) == SAND ? YELLOW : BLACK);
            }
        }

        EndDrawing();
    }

    // 3. Desinicialización
    CloseWindow();

    return 0;
}