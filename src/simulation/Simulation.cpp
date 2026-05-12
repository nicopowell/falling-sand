#include "Simulation.h"

Simulation::Simulation() {
    // Lleno el grid de aire
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

void Simulation::SetCell(Vector2 position, Element element) {
    grid[(int)position.y/CELL_SIZE][(int)position.x/CELL_SIZE] = element;
}

Element Simulation::GetCell(int x, int y) {
    return grid[x][y];
}