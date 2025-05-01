#include "Block.h"
#include <raylib.h>
using namespace std;

Block::Block()
{
    size = 30;
    rotation = 0;
    colors = GetColors();
}

void Block::Draw()
{
    vector<Position> currentBlock = block[rotation];
    for (Position pos : currentBlock)
    {
        int Offset = (GetScreenHeight() - (30 * size)) / 2;
        DrawRectangle(pos.col * size + Offset, pos.row * size + Offset, size - 1, size - 1, colors[id]);
    }
}