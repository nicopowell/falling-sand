#include "raylib.h"
#include "core/Constants.h"
#include "simulation/Element.h"
#include "simulation/Simulation.h"

void paintBrush(Simulation& simulation, Vector2 cursorPosition, int brushSize, Element element);

int main()
{
    // 1. Inicialización
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Guía Rápida");
    SetTargetFPS(60); // Sincroniza el juego a 60 frames por segundo

    Simulation simulation;
    Vector2 cursorPosition;

    int brushSize = 1;
    Element elementSelected = SAND;

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

        if (IsKeyDown(KEY_ONE)) elementSelected = SAND;
        if (IsKeyDown(KEY_TWO)) elementSelected = WATER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            paintBrush(simulation, cursorPosition, brushSize, elementSelected);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            paintBrush(simulation, cursorPosition, brushSize, EMPTY);
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
                Color color;
                switch (simulation.GetCell(x, y)) {
                    case SAND:
                        color = YELLOW;
                        break;
                    case WATER:
                        color = BLUE;
                        break;
                    default:
                        color = BLACK;
                }

                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
            }
        }

        EndDrawing();
    }

    // 3. Desinicialización
    CloseWindow();

    return 0;
}

void paintBrush(Simulation& simulation, Vector2 cursorPosition, int brushSize, Element element) {
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
                    element);
            }
        }
    }
}