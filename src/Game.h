#pragma once
#include "Grid.h"
#include "Block.h"
#include "LeaderBoard.h"
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
  Sound rotate;
  Sound clear;
  Sound gameOverSound;
  int level;
  bool scoreSaved = false; // New member variable

public:
  Game();
  ~Game();
  int GetLevel();
  Block getNextBlock();
  void Draw();
  float GetSpeed();
  bool GetScoreSaved();
  void SetScoreSaved(bool saved); // Setter for scoreSaved
  void Update();
  Grid grid;
  void MoveBlockD();
  int GetClearedLines();
  bool isGameOver;
  int score;
  Music music;
};