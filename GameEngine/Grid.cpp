#include <ctime>
#include "Grid.h"
#include "Cell.h"
#include "Dependencies.h"
#include "Spawner.h"

Grid::Grid()
{
    TileArray = std::vector<Tile*>(32);
    TileArray[0 ] = new Tile("0s", "0s", "0s", "0s", "img/WFC/0_Open.png",             0); 
    TileArray[4 ] = new Tile("1s", "1s", "1s", "1s", "img/WFC/1_Wall.png",             0);
    TileArray[8 ] = new Tile("2" , "1s", "2f", "0s", "img/WFC/2_SideWall.png",         0);
    TileArray[12] = new Tile("2" , "2f", "0s", "0s", "img/WFC/3_WallCorner.png",       0);
    TileArray[16] = new Tile("2" , "1s", "1s", "2f", "img/WFC/4_DumbCorner.png",       0);
    TileArray[20] = new Tile("0s", "3s", "0s", "0s", "img/WFC/6_WallSuperCorner.png",  0);  
    TileArray[24] = new Tile("3s", "0s", "3s", "0s", "img/WFC/7_DoubleWall.png",       0); 
    TileArray[28] = new Tile("3s", "3s", "3s", "3s", "img/WFC/8_SuperSuperCorner.png", 0);

    for (int i = 0; i <= 7 * 4; i+= 4)
    {
        TileArray[i + 3] = new Tile(TileArray[i]->SideKeys[1], TileArray[i]->SideKeys[2], TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->ImagePath, 90);
        TileArray[i + 2] = new Tile(TileArray[i]->SideKeys[2], TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->SideKeys[1], TileArray[i]->ImagePath, 180);
        TileArray[i + 1] = new Tile(TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->SideKeys[1], TileArray[i]->SideKeys[2], TileArray[i]->ImagePath, 270 );
    }

    for (int x = 0; x < GridX; x++)
    {
        for (int y = 0; y < GridY; y++)
        {
            NotTheGrid[x][y] = new TileCell(TileArray);
        }
    }
}

void Grid::GenerateGrid()
{
    const int middleIndexX = floor(GridX / 2);
    const int middleIndexY = floor(GridY / 2);

    // Left Lane
    SetCell(middleIndexX - 1, middleIndexY + 1, TileArray[16]);
    SetCell(middleIndexX - 1, middleIndexY, TileArray[8]);
    SetCell(middleIndexX - 1, middleIndexY - 1, TileArray[12 + 1]); // + 3 = 3 * 90 degrees

    // Middle Lane
    SetCell(middleIndexX, middleIndexY + 1, TileArray[8 + 1]);
    SetCell(middleIndexX, middleIndexY, TileArray[0]);
    SetCell(middleIndexX, middleIndexY - 1, TileArray[0]);

    SetCell(middleIndexX + 1, middleIndexY + 1, TileArray[16 + 1]);
    SetCell(middleIndexX + 1, middleIndexY, TileArray[8 + 2]);
    SetCell(middleIndexX + 1, middleIndexY - 1, TileArray[12 + 2]);

    Propogate();

    if (collapsedCount < GridX * GridY)
    {
        Iterate();
    }
}


void Grid::Iterate()
{
    if (collapsedCount >= GridX * GridY)
    {
        return;
    }
    
    const Vector2Int index = GetLowestEntropy();

    CollapseTile(index.X, index.Y);
    SetCell(index.X, index.Y, NotTheGrid[index.X][index.Y]->CollapsedTile);

    Propogate();
}

Vector2Int Grid::GetLowestEntropy() const
{
    int smallest = 100;
    Vector2Int index = Vector2Int();
    for (int x = 0; x < GridX; x++)
    {
        for (int y = 0; y < GridY; y++)
        {
            if (NotTheGrid[x][y]->Collapsed)
            {
                continue;
            }
            
            if (NotTheGrid[x][y]->CellPossibilities.size() < smallest)
            {
                smallest = NotTheGrid[x][y]->CellPossibilities.size();
                index.X = x;
                index.Y = y;
                continue;
            }

            if (NotTheGrid[x][y]->CellPossibilities.size() == smallest && rand() % 100 > 95)
            {
                index.X = x;
                index.Y = y;
            }
        }
    }

    return index;
}

void Grid::CollapseTile(const int x, const int y) const
{
    if (NotTheGrid[x][y]->CellPossibilities.empty())
    {
        NotTheGrid[x][y]->Collapsed = true;
        NotTheGrid[x][y]->CollapsedTile = TileArray[4];
        NotTheGrid[x][y]->CellPossibilities.clear();
        NotTheGrid[x][y]->CellPossibilities.push_back(NotTheGrid[x][y]->CollapsedTile);

        printf("Failed \n");
        return;
    }
    
    NotTheGrid[x][y]->Collapsed = true;
    
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    const int randIndex = std::rand() % NotTheGrid[x][y]->CellPossibilities.size();
    NotTheGrid[x][y]->CollapsedTile = NotTheGrid[x][y]->CellPossibilities[randIndex];
    
    NotTheGrid[x][y]->CellPossibilities.clear();
    NotTheGrid[x][y]->CellPossibilities.push_back(NotTheGrid[x][y]->CollapsedTile);
}

void Grid::SetCell(const int x, const int y, Tile* Tile) // Could implement flyweight here
{
    if (!NotTheGrid[x][y]->Collapsed)
    {
        NotTheGrid[x][y]->Collapsed = true;
        NotTheGrid[x][y]->CollapsedTile = Tile;
        
        NotTheGrid[x][y]->CellPossibilities.clear();
        NotTheGrid[x][y]->CellPossibilities.push_back(NotTheGrid[x][y]->CollapsedTile);
    }
    
    const Image* img = Dependencies::instance()->Spawner->get_image(Tile->ImagePath, 0, Tile->Angle);
    TheGrid[x][y] = new Cell(false, img, x, y);

    collapsedCount++;
    CellStack.push(Vector2Int(x, y));
}

void Grid::Propogate()
{
    while (!CellStack.empty())
    {
        const Vector2Int cellIndex = CellStack.top();

        const TileCell* changedCell = NotTheGrid[cellIndex.X][cellIndex.Y];

        const std::vector<Vector2Int> validDirs = ValidDirections(cellIndex);

        for (int i = 0; i < validDirs.size(); i++)
        {
            const Vector2Int neighbourIndex = Vector2Int(cellIndex.X + validDirs[i].X, cellIndex.Y + validDirs[i].Y);

            if (Constrain(changedCell, neighbourIndex, validDirs[i]))
            {
                CellStack.push(neighbourIndex);
            }
        }

        CellStack.pop();
    }
}

std::vector<Vector2Int> Grid::ValidDirections(const Vector2Int& index)
{
    std::vector<Vector2Int> directions = std::vector<Vector2Int>();

    // Left
    if (index.X > 0)
    {
        directions.emplace_back(-1, 0);
    }

    // Right
    if (index.X < GridX - 1)
    {
        directions.emplace_back(1, 0);
    }

    // Up
    if (index.Y > 0)
    {
        directions.emplace_back(0, -1);
    }

    // Down
    if (index.Y < GridY - 1)
    {
        directions.emplace_back(0, 1);
    }

    return directions;
}

bool Grid::Constrain(const TileCell* changedCell, const Vector2Int& cellIndex, const Vector2Int& direction) const
{
    if (NotTheGrid[cellIndex.X][cellIndex.Y]->Collapsed)
    {
        return false;
    }
    
    // Direction is from the changedCell to the cellIndex

    std::vector<std::string> ValidKeys = std::vector<std::string>();

    for (const auto CellPossibilitie : changedCell->CellPossibilities)
    {
        // Left
        if (direction.X == -1)
        {
            ValidKeys.emplace_back(CellPossibilitie->SideKeys[1]);
        }

        // Right
        if (direction.X == 1)
        {
            ValidKeys.emplace_back(CellPossibilitie->SideKeys[3]);
        }

        // Down
        if (direction.Y == 1)
        {
            ValidKeys.emplace_back(CellPossibilitie->SideKeys[2]);
        }
        
        // Up
        if (direction.Y == -1)
        {
            ValidKeys.emplace_back(CellPossibilitie->SideKeys[0]);
        }
    }

    const int count = NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.size();
    bool changed = false;
    int sideIndex = -1;
    // Right
    if (direction.X == -1)
        sideIndex = 3;

    // Left
    if (direction.X == 1)
        sideIndex = 1;

    // Up
    if (direction.Y == 1)
        sideIndex = 0;

    // Down
    if (direction.Y == -1)
        sideIndex = 2;

    for (int i = count - 1; i >= 0; i--)
    {
        if (!CheckValidSocket(NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities[i]->SideKeys[sideIndex], ValidKeys))
        {
            NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.erase(NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.begin() + i);
            changed = true;
            continue;
        }

        //if (changedCell->Collapsed && ValidKeys[0] == "0s" && changedCell->CollapsedTile->ImagePath != "img/WFC/0_Open.png")
        //{
        //    if (NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities[i]->ImagePath != "img/WFC/0_Open.png")
        //    {
        //        NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.erase(NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.begin() + i);
        //        changed = true;
        //        continue;
        //    }
        //}
    }
    
    return changed;
}

bool Grid::CheckValidSocket(const std::string& key, const std::vector<std::string>& validKeys)
{
    if (key.length() == 1)
    {
        const std::string keyf = key + 'f';
        return ContainsKey(validKeys, keyf);
    }

    if (key[1] == 's') // Ex. 0s
    {
        return ContainsKey(validKeys, key);
    }

    if (key[1] == 'f') // Ex. 0f
    {
        return ContainsKey(validKeys, key.substr(0, 1));
    }
    
    return false;
}

bool Grid::ContainsKey(const std::vector<std::string>& array, const std::string& key)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] == key)
        {
            return true;
        }
    }

    return false;
}