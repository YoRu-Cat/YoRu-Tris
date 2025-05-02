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
  bool isRowFull(int r);
  void clearRow(int r);
  void moveRowDown(int r, int n);

public:
  Grid();
  void Initialize();
  void Draw();
  bool CheckCollision(int r, int c);
  bool isEmpty(int r, int c);
  int ClearFullRows();
  void GetGridWidth(int &width, int &height);
  int grid[30][30];
};