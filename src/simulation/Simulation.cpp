#include "Simulation.h"
#include <cstdlib>
#include <ctime>

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

void Simulation::UpdateSand()
{
    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        bool leftToRight = rand() % 2 == 0;
        for (int x = (leftToRight ? 0 : GRID_WIDTH - 1); (leftToRight ? x < GRID_WIDTH : x >= 0); (leftToRight ? x++ : x--))
        {
            if (grid[y][x] == SAND)
            {
                // Abajo
                if (y + 1 < GRID_HEIGHT && (grid[y + 1][x] == EMPTY || grid[y + 1][x] == WATER))
                {
                    Element aux = grid[y][x];
                    grid[y][x] = grid[y + 1][x];
                    grid[y + 1][x] = aux;
                    continue;
                }

                bool canLeftDown  = (x > 0 && y + 1 < GRID_HEIGHT && grid[y + 1][x - 1] == EMPTY);
                bool canRightDown = (x + 1 < GRID_WIDTH && y + 1 < GRID_HEIGHT && grid[y + 1][x + 1] == EMPTY);

                // Ambos lados posibles → ahí sí azar
                if (canLeftDown && canRightDown)
                {
                    if (rand() % 2 == 0)
                    {
                        grid[y][x] = EMPTY;
                        grid[y + 1][x - 1] = SAND;
                    }
                    else
                    {
                        grid[y][x] = EMPTY;
                        grid[y + 1][x + 1] = SAND;
                    }
                }
                else if (canLeftDown)
                {
                    grid[y][x] = EMPTY;
                    grid[y + 1][x - 1] = SAND;
                }
                else if (canRightDown)
                {
                    grid[y][x] = EMPTY;
                    grid[y + 1][x + 1] = SAND;
                }
            }
        }
    }
}

void Simulation::UpdateWater()
{
    bool leftToRight = rand() % 2 == 0;

    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = (leftToRight ? 0 : GRID_WIDTH - 1);
            (leftToRight ? x < GRID_WIDTH : x >= 0);
            (leftToRight ? x++ : x--))
        {
            if (grid[y][x] != WATER) continue;

            // 1. CAER
            if (y + 1 < GRID_HEIGHT && grid[y + 1][x] == EMPTY)
            {
                grid[y][x] = EMPTY;
                grid[y + 1][x] = WATER;
                continue;
            }

            // 2. FLOW LATERAL (buscar espacio)
            int dir = (rand() % 2 == 0) ? -1 : 1;
            const int MAX_FLOW = 8;

            bool moved = false;

            for (int i = 1; i <= MAX_FLOW; i++)
            {
                int nx = x + dir * i;

                if (nx < 0 || nx >= GRID_WIDTH) break;

                // Si encuentra una pared → frena
                if (grid[y][nx] != EMPTY) break;

                // Si puede caer desde ahí → moverse
                if (y + 1 < GRID_HEIGHT && grid[y + 1][nx] == EMPTY)
                {
                    grid[y][x] = EMPTY;
                    grid[y][nx] = WATER;
                    moved = true;
                    break;
                }
            }

            if (moved) continue;

            // 3. MOVIMIENTO LATERAL SIMPLE (suavizado)
            bool canLeft = (x > 0 && grid[y][x - 1] == EMPTY);
            bool canRight = (x + 1 < GRID_WIDTH && grid[y][x + 1] == EMPTY);

            if (canLeft && !canRight)
            {
                grid[y][x] = EMPTY;
                grid[y][x - 1] = WATER;
            }
            else if (canRight && !canLeft)
            {
                grid[y][x] = EMPTY;
                grid[y][x + 1] = WATER;
            }
            else if (canLeft && canRight)
            {
                // Reducimos vibración
                if (rand() % 3 == 0)
                {
                    if (rand() % 2 == 0)
                    {
                        grid[y][x] = EMPTY;
                        grid[y][x - 1] = WATER;
                    }
                    else
                    {
                        grid[y][x] = EMPTY;
                        grid[y][x + 1] = WATER;
                    }
                }
            }
        }
    }
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