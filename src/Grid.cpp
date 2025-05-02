#include "Grid.h"
#include "raylib.h"
#include "Colors.h"

bool Grid::isRowFull(int r)
{
  for (int c = 0; c < cols; c++)
  {
    if (grid[r][c] == 0)
    {
      return false; // Row is not full
    }
  }
  return true; // Row is full
}

void Grid::clearRow(int r)
{
  for (int c = 0; c < cols; c++)
  {
    grid[r][c] = 0; // Clear the row by setting all cells to 0
  }
}

void Grid::moveRowDown(int r, int n)
{
  for (int c = 0; c < cols; c++)
  {
    grid[r + n][c] = grid[r][c]; // Move the row down by n rows
    grid[r][c] = 0;              // Clear the original row
  }
}

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
  int gridWidth = cols * cellWidth;
  int gridHeight = rows * cellHeight;
  int Offset = (GetScreenHeight() - gridHeight) / 2;

  DrawRectangleLinesEx({(float)Offset - 4, (float)Offset - 4, (float)gridWidth + 8, (float)gridHeight + 8}, 3, dGry);
}

void Grid::GetGridWidth(int &width, int &height)
{
  width = cols * cellWidth;
  height = rows * cellHeight;
}

bool Grid::CheckCollision(int r, int c)
{
  if (r >= 0 && r < rows && c >= 0 && c < cols)
  {
    return false;
  }
  else
    return true;
}

bool Grid::isEmpty(int r, int c)
{
  if (grid[r][c] == 0)
  {
    return true; // Cell is empty
  }
  else
    return false; // Cell is occupied
}

int Grid::ClearFullRows()
{
  int clearedRows = 0;
  for (int r = rows - 1; r >= 0; r--)
  {
    if (isRowFull(r))
    {
      clearRow(r); // Clear the full row
      clearedRows++;
    }
    else if (clearedRows > 0)
    {
      moveRowDown(r, clearedRows); // Move the row down
    }
  }
  return clearedRows; // Return the number of cleared rows
}
