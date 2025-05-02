#pragma once
#include <raylib.h>
#include <vector>
using namespace std;

class Grid
{
private:
  int rows;
  int cols;
  int cellWidth;
  int cellHeight;
  vector<Color> colors;

public:
  Grid();
  void Initialize();
  void Draw();
  bool CheckCollision(int r, int c);
  bool isEmpty(int r, int c);
  int grid[30][30];
};