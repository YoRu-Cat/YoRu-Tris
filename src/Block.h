#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"
#include "Grid.h"
using namespace std;

class Block
{
private:
    int size;
    int rotation;
    vector<Color> colors;
    int rowsOffset;
    int colsOffset;

public:
    Block();
    void Move(int rows, int cols);
    bool IsValidPosition(int row, int col);
    vector<Position> GetCurrentBlock();
    void Draw();
    void Rotate();
    void UndoRotate();
    void PreviewLanding(vector<Position> &landingBlock, Grid &grid);
    int id;
    map<int, vector<Position>> block;
};