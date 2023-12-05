#pragma once

#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "Vector2Int.h"

struct Cell;

struct Tile
{
    Tile(): ImagePath(nullptr)
    {
    }

    std::string SideKeys[4]{};
    int Angle = 0;
    const char* ImagePath;

    Tile(const std::string up, const std::string& left, const std::string& down, const std::string& right, const char* path, const int angle)
    {
        SideKeys[0] = up;
        SideKeys[1] = left;
        SideKeys[2] = down;
        SideKeys[3] = right;
        
        Angle = angle;

        ImagePath = path;
    }
};

struct TileCell
{
    std::vector<Tile*> CellPossibilities{};
    bool Collapsed = false;

    Tile* CollapsedTile = nullptr;
    
    TileCell(std::vector<Tile*> tileArray)
    {
        CellPossibilities = std::move(tileArray);
        
        Collapsed = false;
    }
};

constexpr int GridX = 16;
constexpr int GridY = 9;

class Grid
{
    int collapsedCount = 0;
    std::vector<Tile*> TileArray;

    std::stack<Vector2Int> CellStack;

public:
    
    TileCell* NotTheGrid[GridX][GridY]{};
    Cell* TheGrid[GridX][GridY]{};
    Grid();

    void Iterate();
    [[nodiscard]] Vector2Int GetLowestEntropy() const;
    void CollapseTile(int x, int y) const;
    void SetCell(int x, int y, Tile* Tile);
    void Propogate();
    static std::vector<Vector2Int> ValidDirections(const Vector2Int& index);
    bool Constrain(const TileCell* changedCell, const Vector2Int& cellIndex, const Vector2Int& direction) const;
    static bool CheckValidSocket(const std::string& key, const std::vector<std::string>& validKeys);

    static bool ContainsKey(const std::vector<std::string>& array, const std::string& key);
    void GenerateGrid();
};
