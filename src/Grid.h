#pragma once
class Grid
{
private:
  int rows;
  int cols;
  int cellWidth;
  int cellHeight;

public:
  Grid();
  void Initialize();
  void Draw();
  int grid[30][30];
};