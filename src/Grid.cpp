#include "Grid.h"
#include "raylib.h"
#include "Colors.h"

Grid::Grid()
{
  rows = 30;
  cols = 30;
  cellWidth = 30;
  cellHeight = 30;
  Initialize();
  colors = GetColors();
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
  // Draw the grid cells
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Calculate the position of the cell
      int Offset = (GetScreenHeight() - (rows * cellHeight)) / 2;
      int cellVal = grid[i][j];
      DrawRectangle(j * cellWidth + Offset, i * cellHeight + Offset, cellWidth - 1, cellHeight - 1, colors[cellVal]);
    }
  }

  // Draw the border around the grid
  // int gridWidth = cols * cellWidth;
  // int gridHeight = rows * cellHeight;
  // int Offset = (GetScreenHeight() - gridHeight) / 2;

  // DrawRectangleLinesEx({(float)Offset - 3, (float)Offset - 3, (float)gridWidth + 6, (float)gridHeight + 6}, 3, LIGHTGRAY);
}