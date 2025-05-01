#include "Grid.h"
#include "raylib.h"

Grid::Grid()
{
  rows = 30;
  cols = 30;
  cellWidth = 30;
  cellHeight = 30;
  Initialize();
}

void Grid::Initialize()
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      grid[i][j] = 0;
    }
  }
}

void Grid::Draw()
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      int verticalOffset = (GetScreenHeight() - (rows * cellHeight)) / 2;
      if (grid[i][j] == 1)
      {
        DrawRectangle(j * cellWidth + verticalOffset, i * cellHeight + verticalOffset, cellWidth, cellHeight, WHITE);
      }
      else
      {
        DrawRectangleLines(j * cellWidth + verticalOffset, i * cellHeight + verticalOffset, cellWidth, cellHeight, BLACK);
      }
    }
  }
}