#include "Grid.h"

#include "Cell.h"
#include "Dependencies.h"
#include "Spawner.h"

const char* cellBlackImagePath{ "img/black.png" };
const char* cellWhiteImagePath{ "img/white.png" };

Grid::Grid()
{
    
}

void Grid::GenerateGrid()
{
    for (int x = 0; x < GridX; x++)
    {
        for (int y = 0; y < GridY; y++)
        {
            const bool walkable = x % 2 == 0 || y == 5;
            const char* path = walkable ? cellWhiteImagePath : cellBlackImagePath;
            TheGrid[x][y] = new Cell(walkable, Dependencies::instance()->Spawner->get_image(path, 0), x, y);
        }
    }
}