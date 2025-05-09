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
  void FixBlockPosition();
  void LockBlock();
  bool BlockFits();
  void ResetGame();
  void UpdateScore(int clearedRows, int moveDown);

public:
  Game();
  Block getNextBlock();
  Block GetRandomBlock();
  vector<Block> GetBlocks();
  Grid grid;
  void Draw();
  float GetSpeed();
  void Update();
  void MoveBlockL();
  void MoveBlockR();
  void MoveBlockD();
  bool isGameOver;
  int score;
};