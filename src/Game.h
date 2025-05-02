#pragma once
#include "Grid.h"
#include "blocks.cpp"
using namespace std;
class Game
{

private:
  vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  bool isBlockOut();
  void RotateBlock();
  void LockBlock();
  bool BlockFits();
  void ResetGame();

public:
  Game();
  Block GetRandomBlock();
  vector<Block> GetBlocks();
  Grid grid;
  void Draw();
  void Update();
  void MoveBlockL();
  void MoveBlockR();
  void MoveBlockD();
  bool isGameOver = false;
};