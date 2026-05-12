#include "Simulation.h"
#include <cstdlib>
#include <ctime>

Simulation::Simulation() {
    srand(time(NULL));

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

void Simulation::SetCell(Vector2 position, Element element) {
    int x = (int)position.x/CELL_SIZE;
    int y = (int)position.y/CELL_SIZE;

    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) return;

    grid[y][x] = element;
}

Element Simulation::GetCell(int x, int y) {
    return grid[x][y];
}

void Simulation::Update() {
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == SAND){

                // Cae abajo
                if (y + 1 < GRID_HEIGHT && grid[y+1][x] == EMPTY) {
                    grid[y][x] = EMPTY;
                    grid[y+1][x] = SAND;
                    continue;
                }

                // Elige direccion aleatoria
                bool leftFirst = rand() % 2 == 0;

                if (leftFirst) {
                    // Izquierda -> Derecha
                    if (x > 0 && y + 1 < GRID_HEIGHT && grid[y+1][x-1] == EMPTY) {
                        grid[y][x] = EMPTY;
                        grid[y+1][x-1] = SAND;
                    } else if (x + 1 < GRID_WIDTH && y + 1 < GRID_WIDTH && grid[y+1][x+1] == EMPTY) {
                        grid[y][x] = EMPTY;
                        grid[y+1][x+1] = SAND;
                    }
                } else {
                    // Derecha -> Izquierda
                    if (x + 1 < GRID_WIDTH && y + 1 < GRID_WIDTH && grid[y+1][x+1] == EMPTY) {
                        grid[y][x] = EMPTY;
                        grid[y+1][x+1] = SAND;
                    } else if (x > 0 && y + 1 < GRID_HEIGHT && grid[y+1][x-1] == EMPTY) {
                        grid[y][x] = EMPTY;
                        grid[y+1][x-1] = SAND;
                    }
                }
            }
        }
    }
}