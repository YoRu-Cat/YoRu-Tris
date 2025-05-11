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
  rowCleared = 0;
  // Initialize the grid with zeros
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
      int Offset = (GetScreenHeight() - (rows * cellHeight)) / 2;
      int cellVal = grid[i][j];

      // Calculate cell position
      float x = j * cellWidth + Offset;
      float y = i * cellHeight + Offset;

      if (cellVal > 0)
      {
        // Draw cell glow effect
        Color glowColor = ColorAlpha(colors[cellVal], 0.3f);
        DrawRectangle(x - 2, y - 2, cellWidth + 4, cellHeight + 4, glowColor);

        // Draw gradient cell
        Color darkColor = ColorBrightness(colors[cellVal], -0.3f);
        DrawRectangleGradientV(x, y, cellWidth - 1, cellHeight - 1, colors[cellVal], darkColor);

        // Draw cell highlights
        DrawRectangleLinesEx({x, y, (float)cellWidth - 1, (float)cellHeight - 1}, 1, WHITE);
      }
      else
      {
        // Draw empty cell with subtle grid pattern
        Color gridColor = ColorAlpha(LIGHTGRAY, 0.2f);
        DrawRectangleLinesEx({x, y, (float)cellWidth - 1, (float)cellHeight - 1}, 1, gridColor);
      }
    }
  }

  // Draw decorative border
  int gridWidth = cols * cellWidth;
  int gridHeight = rows * cellHeight;
  int Offset = (GetScreenHeight() - gridHeight) / 2;

  // Outer glow
  DrawRectangleLinesEx({(float)Offset - 6, (float)Offset - 6, (float)gridWidth + 12, (float)gridHeight + 12}, 2, ColorAlpha(RAYWHITE, 0.3f));
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
      rowCleared++;
    }
    else if (clearedRows > 0)
    {
      moveRowDown(r, clearedRows); // Move the row down
    }
  }
  return clearedRows; // Return the number of cleared rows
}
