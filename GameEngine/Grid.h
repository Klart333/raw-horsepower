#pragma once

struct Cell;


constexpr int GridX = 16;
constexpr int GridY = 9;

class Grid
{
public:
    Cell* TheGrid[GridX][GridY]{};
    Grid();
    
    void GenerateGrid();
};

