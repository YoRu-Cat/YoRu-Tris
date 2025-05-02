#include "Block.h"
#include <raylib.h>
using namespace std;

Block::Block()
{
    size = 30;
    rotation = 0;
    colors = GetColors();
    rowsOffset = 0;
    colsOffset = 0;
}

void Block::Draw()
{
    vector<Position> currentBlock = GetCurrentBlock();
    for (Position pos : currentBlock)
    {
        int Offset = (GetScreenHeight() - (30 * size)) / 2;
        DrawRectangle(pos.col * size + Offset, pos.row * size + Offset, size - 1, size - 1, colors[id]);
    }
}

void Block::Rotate()
{
    rotation = (rotation + 1) % block.size();
}

void Block::Move(int rows, int cols)
{
    rowsOffset += rows;
    colsOffset += cols;
}

vector<Position> Block::GetCurrentBlock()
{
    vector<Position> currentBlock = block[rotation];
    vector<Position> movedBlock;
    for (Position pos : currentBlock)
    {
        Position movedPos = Position(pos.row + rowsOffset, pos.col + colsOffset);
        movedBlock.push_back(movedPos);
    }
    return movedBlock;
}
