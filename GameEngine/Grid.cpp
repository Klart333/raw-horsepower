const char* coinImagePath{"img/coin.png"};

#include "Dependencies.h"
#include "Spawner.h"
#include "Grid.h"
#include "Cell.h"
#include <ctime>
#include <set>

Grid::Grid()
{
    TileArray = std::vector<Tile*>(36);
    TileArray[0 ] = new Tile("0s", "0s", "0s", "0s", "img/WFC/00_Open.png",               0, 8); 
    TileArray[4 ] = new Tile("1s", "1s", "1s", "1s", "img/WFC/01_Wall.png",               0, 6);
    TileArray[8 ] = new Tile("2" , "1s", "2f", "0s", "img/WFC/02_SideWall.png",           0, 6);
    TileArray[12] = new Tile("2" , "2f", "0s", "0s", "img/WFC/03_WallCorner.png",         0, 5);
    TileArray[16] = new Tile("2" , "1s", "1s", "2f", "img/WFC/04_DumbCorner.png",         0, 5);
    TileArray[20] = new Tile("0s", "3s", "0s", "0s", "img/WFC/06_WallSuperCorner.png",    0, 3);  
    TileArray[24] = new Tile("3s", "0s", "3s", "0s", "img/WFC/07_DoubleWall.png",         0, 1); 
    TileArray[28] = new Tile("3s", "3s", "3s", "3s", "img/WFC/08_SuperSuperCorner.png",   0, 1);
    TileArray[32] = new Tile("2f", "3s", "2" , "1s", "img/WFC/09_PartialSuperCorner.png", 0, 2);

    for (int i = 0; i <= 8 * 4; i+= 4)
    {
        TileArray[i + 3] = new Tile(TileArray[i]->SideKeys[1], TileArray[i]->SideKeys[2], TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->ImagePath, 90 , TileArray[i]->Weight);
        TileArray[i + 2] = new Tile(TileArray[i]->SideKeys[2], TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->SideKeys[1], TileArray[i]->ImagePath, 180, TileArray[i]->Weight);
        TileArray[i + 1] = new Tile(TileArray[i]->SideKeys[3], TileArray[i]->SideKeys[0], TileArray[i]->SideKeys[1], TileArray[i]->SideKeys[2], TileArray[i]->ImagePath, 270, TileArray[i]->Weight);
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
}

bool Grid::Iterate()
{
    if (collapsedCount >= GridX * GridY)
    {
        return true;
    }
    
    const Vector2Int index = GetLowestEntropy();

    CollapseTile(index.X, index.Y);
    SetCell(index.X, index.Y, NotTheGrid[index.X][index.Y]->CollapsedTile);

    Propogate();

    if (collapsedCount >= GridX * GridY)
    {
        // Clear memory

        TileArray.clear();
    }

    return false;
}

Vector2Int Grid::GetLowestEntropy() const
{
    int smallest = 1024;
    Vector2Int index = Vector2Int();
    for (int x = 0; x < GridX; x++)
    {
        for (int y = 0; y < GridY; y++)
        {
            const int size = NotTheGrid[x][y]->CellPossibilities.size();

            if (NotTheGrid[x][y]->Collapsed || size >= 36)
            {
                continue;
            }

            float entropy = 0;
            int totalWeight = 0;
            for (const auto& CellPossibilitie : NotTheGrid[x][y]->CellPossibilities)
            {
                totalWeight += CellPossibilitie->Weight;
            }

            for (const auto& CellPossibilitie : NotTheGrid[x][y]->CellPossibilities)
            {
                entropy += 1.0f - ((CellPossibilitie->Weight - 1.0f) / totalWeight);

            }

            // Remove entropy for being in the center
            entropy += abs(x - GridX / 2.0f) / 12;
            entropy += abs(y - GridY / 2.0f) / 12;
            
            //for (const auto& CellPossibilitie : NotTheGrid[x][y]->CellPossibilities)
            //{
            //    entropy -= CellPossibilitie->Weight / size;
            //}
            
            if (entropy < smallest)
            {
                smallest = entropy;
                index.X = x;
                index.Y = y;
                continue;
            }

            if (entropy == smallest && rand() % 100 > 95)
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

    std::srand(std::time(nullptr) + (x + 11) * 73 + y * 103); // use current time as seed for random generator (can't only use time because its too fast lol)
    int totalWeight = 0;
    for (const auto& CellPossibilitie : NotTheGrid[x][y]->CellPossibilities)
    {
        totalWeight += CellPossibilitie->Weight;
    }

    Tile* tile = nullptr;
    int randIndex = std::rand() % totalWeight;
    for (const auto& CellPossibilitie : NotTheGrid[x][y]->CellPossibilities)
    {
        randIndex -= CellPossibilitie->Weight;
        if (randIndex <= 0)
        {
            tile = CellPossibilitie;
            break;
        }
    }
    
    NotTheGrid[x][y]->CollapsedTile = tile;
    
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

    std::unique_ptr<Image> img = Dependencies::instance()->Spawner->get_image(Tile->ImagePath, 0, Tile->Angle);
    const bool walkable = Tile->ImagePath == "img/WFC/00_Open.png";
    const bool coin = walkable && rand() % 100 > 90;
    std::unique_ptr<Image> coinImage = nullptr;
    if (coin)
    {
        coinImage = Dependencies::instance()->Spawner->get_image(coinImagePath, 0, 0);
    }
    TheGrid[x][y] = new Cell(walkable, coin, std::move(img), std::move(coinImage), x, y);

    collapsedCount++;
    CellStack.push(Vector2Int(x, y));
}

void Grid::Propogate()
{
    while (!CellStack.empty())
    {
        Vector2Int cellIndex = CellStack.top();
        CellStack.pop();

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

    std::set<std::string> ValidKeys = std::set<std::string>();

    for (const auto CellPossibilitie : changedCell->CellPossibilities)
    {
        // Left
        if (direction.X == -1)
        {
            ValidKeys.emplace(CellPossibilitie->SideKeys[1]);
        }

        // Right
        if (direction.X == 1)
        {
            ValidKeys.emplace(CellPossibilitie->SideKeys[3]);
        }

        // Down
        if (direction.Y == 1)
        {
            ValidKeys.emplace(CellPossibilitie->SideKeys[2]);
        }
        
        // Up
        if (direction.Y == -1)
        {
            ValidKeys.emplace(CellPossibilitie->SideKeys[0]);
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

    bool onlyOpenTileAvailable = false;// I hate this part
    if (ValidKeys.size() == 1 && ValidKeys.contains("0s")) // If the only valid connection is 0s
    {
        for (const auto element : changedCell->CellPossibilities)
        {
            if (element->ImagePath != "img/WFC/00_Open.png") 
            {
                onlyOpenTileAvailable = true;
            }
        }
    }

    for (int i = count - 1; i >= 0; i--)
    {
        if (!CheckValidSocket(NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities[i]->SideKeys[sideIndex], ValidKeys))
        {
            NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.erase(NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities.begin() + i);
            changed = true;
            continue;
        }

        if (onlyOpenTileAvailable && NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities[i]->ImagePath == "img/WFC/00_Open.png")
        {
            NotTheGrid[cellIndex.X][cellIndex.Y]->CellPossibilities[i]->Weight = 15;
            continue;
        }
    }
    
    return changed;
}

bool Grid::CheckValidSocket(const std::string& key, const std::set<std::string>& validKeys)
{
    if (key.length() == 1)
    {
        const std::string keyf = key + 'f';
        return validKeys.contains(keyf);
    }

    if (key[1] == 's') // Ex. 0s
    {
        return validKeys.contains(key);
    }

    if (key[1] == 'f') // Ex. 0f
    {
        return validKeys.contains(key.substr(0, 1));
    }
    
    return false;
}