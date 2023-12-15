#pragma once

#include <set>
#include <stack>
#include <string>
#include <vector>
#include "Vector2Int.h"

struct Cell;

struct Tile
{
    Tile(): ImagePath(nullptr)
    {
    }

    // Both just used for debuging
    struct SDL_Rect* StupidRect{};
    struct SDL_Texture* StupidImage{};

    std::string SideKeys[4]{};
    const char* ImagePath;
    
    int Weight = 0;
    int Angle = 0;

    Tile(const std::string up, const std::string& left, const std::string& down, const std::string& right, const char* path, const int angle, const int weight)
    {
        SideKeys[0] = up;
        SideKeys[1] = left;
        SideKeys[2] = down;
        SideKeys[3] = right;
        
        Angle = angle;
        Weight = weight;
        
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

constexpr int GridX = 80;
constexpr int GridY = 45;

class Grid
{
    int collapsedCount = 0;
    std::vector<Tile*> TileArray;

    std::stack<Vector2Int> CellStack;

public:
    
    TileCell* NotTheGrid[GridX][GridY]{};
    Cell* TheGrid[GridX][GridY]{};
    Grid();

    bool Iterate();
    [[nodiscard]] Vector2Int GetLowestEntropy() const;
    void CollapseTile(int x, int y) const;
    void SetCell(int x, int y, Tile* Tile);
    void Propogate();
    static std::vector<Vector2Int> ValidDirections(const Vector2Int& index);
    bool Constrain(const TileCell* changedCell, const Vector2Int& cellIndex, const Vector2Int& direction) const;
    static bool CheckValidSocket(const std::string& key, const std::set<std::string>& validKeys);
    void GenerateGrid();
};
