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
  Block GetRandomBlock();
  vector<Block> GetBlocks();
  void MoveBlockL();
  void MoveBlockR();

public:
  Game();
  Block getNextBlock();
  void Draw();
  float GetSpeed();
  void Update();
  Grid grid;
  void MoveBlockD();
  bool isGameOver;
  int score;
};