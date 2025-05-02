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
    rotation++;
    if (rotation == (int)block.size()) // If rotation exceeds the size, reset to 0
    {
        rotation = 0;
    }
}

void Block::UndoRotate()
{
    rotation--;
    if (rotation == -1) // If rotation is negative, reset to the last index
    {
        rotation = block.size() - 1;
    }
}

void Block::Move(int rows, int cols)
{
    rowsOffset += rows;
    colsOffset += cols;

    if (!IsValidPosition(rowsOffset, colsOffset))
    {
        rowsOffset -= rows;
        colsOffset -= cols;
    }
}
bool Block::IsValidPosition(int row, int col)
{
    return (row >= 0 && row < 30 && col >= 0 && col < 30); // Assuming grid size is 30x30
}
void Block::PreviewLanding(vector<Position> &landingBlock, Grid &grid)
{
    vector<Position> currentBlock = GetCurrentBlock();
    landingBlock = currentBlock; // Start with the current block positions
    int maxDrop = 0;

    // Calculate the maximum drop distance
    while (true)
    {
        bool canDrop = true;
        for (Position pos : landingBlock)
        {
            if (!IsValidPosition(pos.row + 1, pos.col) || !grid.isEmpty(pos.row + 1, pos.col))
            {
                canDrop = false;
                break;
            }
        }
        if (!canDrop)
        {
            break;
        }
        for (Position &pos : landingBlock)
        {
            pos.row += 1; // Move the block down by one row
        }
        maxDrop++;
    }

    // Draw a white outline around the landing block
    for (Position pos : landingBlock)
    {
        int Offset = (GetScreenHeight() - (30 * size)) / 2;
        DrawRectangle(pos.col * size + Offset + size / 4, pos.row * size + Offset + size / 4, size / 2, size / 2, Fade(WHITE, 0.5f));
    }
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
