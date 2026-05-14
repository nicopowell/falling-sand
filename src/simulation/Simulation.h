#pragma once
#include "raylib.h"
#include "../core/Constants.h"
#include "Element.h"

class Simulation {
private:
    Element grid[GRID_HEIGHT][GRID_WIDTH];

public:
    Simulation();
    void SetCell(Vector2 position, Element element, bool overwrite = false);
    Element GetCell(int x, int y);
    void Update();
    void Clear();
};