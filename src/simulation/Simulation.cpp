#include "Simulation.h"
#include <cstdlib>
#include <ctime>
#include <utility>

Simulation::Simulation()
{
    srand(time(NULL));

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            grid[i][j] = EMPTY;
        }
    }
}

void Simulation::SetCell(Vector2 position, Element element, bool overwrite)
{
    int x = (int)position.x / CELL_SIZE;
    int y = (int)position.y / CELL_SIZE;

    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return;

    if (!overwrite && grid[y][x] != EMPTY) return;

    grid[y][x] = element;
}

Element Simulation::GetCell(int x, int y)
{
    return grid[y][x];
}

void Simulation::Update()
{
    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        bool leftToRight = rand() % 2 == 0;
        for (int x = (leftToRight ? 0 : GRID_WIDTH - 1); (leftToRight ? x < GRID_WIDTH : x >= 0); (leftToRight ? x++ : x--))
        {
            if (grid[y][x] == SAND)
            {
                UpdateSandAt(x, y);
            }
            else if (grid[y][x] == WATER)
            {
                UpdateWaterAt(x, y);
            }
        }
    }
}

void Simulation::UpdateSandAt(int x, int y)
{
    // Abajo
    if (y + 1 < GRID_HEIGHT && (grid[y + 1][x] == EMPTY || grid[y + 1][x] == WATER))
    {
        std::swap(grid[y][x], grid[y + 1][x]);
        return;
    }

    bool canLeftDown  = (x > 0 && y + 1 < GRID_HEIGHT && grid[y + 1][x - 1] == EMPTY);
    bool canRightDown = (x + 1 < GRID_WIDTH && y + 1 < GRID_HEIGHT && grid[y + 1][x + 1] == EMPTY);

    // Ambos lados posibles → ahí sí azar
    if (canLeftDown && canRightDown)
    {
        if (rand() % 2 == 0)
        {
            std::swap(grid[y][x], grid[y + 1][x - 1]);
        }
        else
        {
            std::swap(grid[y][x], grid[y + 1][x + 1]);
        }
    }
    else if (canLeftDown)
    {
        std::swap(grid[y][x], grid[y + 1][x - 1]);
    }
    else if (canRightDown)
    {
        std::swap(grid[y][x], grid[y + 1][x + 1]);
    }
}

void Simulation::UpdateWaterAt(int x, int y)
{
    // 1. CAER
    if (y + 1 < GRID_HEIGHT && grid[y + 1][x] == EMPTY)
    {
        std::swap(grid[y][x], grid[y + 1][x]);
        return;
    }

    // 2. FLOW LATERAL (buscar espacio)
    int dir = (rand() % 2 == 0) ? -1 : 1;
    const int MAX_FLOW = 8;

    for (int i = 1; i <= MAX_FLOW; i++)
    {
        int nx = x + dir * i;

        // Si sale de los límites o encuentra una pared → frena
        if (nx < 0 || nx >= GRID_WIDTH || grid[y][nx] != EMPTY) 
            break; 

        // Si puede caer desde ahí → moverse
        if (y + 1 < GRID_HEIGHT && grid[y + 1][nx] == EMPTY)
        {
            std::swap(grid[y][x], grid[y][nx]);
            return; // Terminamos aquí si encontró un precipicio
        }
    }

    // 3. MOVIMIENTO LATERAL SIMPLE (suavizado para terreno plano)
    // Intentamos ir hacia 'dir'. Si está bloqueado, intentamos el lado opuesto.
    int nx = x + dir;
    if (nx >= 0 && nx < GRID_WIDTH && grid[y][nx] == EMPTY) 
        std::swap(grid[y][x], grid[y][nx]);
    else if (x - dir >= 0 && x - dir < GRID_WIDTH && grid[y][x - dir] == EMPTY)
        std::swap(grid[y][x], grid[y][x - dir]);
}

void Simulation::Clear()
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = EMPTY;
        }
    }
}