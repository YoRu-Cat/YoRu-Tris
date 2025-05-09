#pragma once
#include <vector>
#include "Position.h"
#include "Colors.h"
#include "Grid.h"
using namespace std;

class Block
{
private:
    int rotation;
    vector<Color> colors;
    int rowsOffset;
    int colsOffset;

public:
    Block();
    void Move(int rows, int cols);
    bool IsValidPosition(int row, int col);
    vector<Position> GetCurrentBlock();
    void Draw(int offX, int offY);
    void Rotate();
    void UndoRotate();
    void PreviewLanding(vector<Position> &landingBlock, Grid &grid);
    int id;
    int size;
    vector<vector<Position>> block; // Replaced map with vector of vectors
};
