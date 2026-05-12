#include "raylib.h"

int main() {
    // 1. Inicialización
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Guía Rápida");
    SetTargetFPS(60); // Sincroniza el juego a 60 frames por segundo

    // 2. Bucle Principal
    while (!WindowShouldClose()) { // Detecta tecla ESC o botón de cerrar
        
        // --- Lógica de Actualización (Update) ---
        // Aquí van cálculos, colisiones y entrada de usuario

        // --- Dibujado (Draw) ---
        BeginDrawing();
            ClearBackground(BLACK); // Limpia el frame anterior

        EndDrawing();
    }

    // 3. Desinicialización
    CloseWindow(); 

    return 0;
}