#include "Game.h"
#include <random>
using namespace std;

Game::Game()
{
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock(); // Initialize the current and next blocks
} // Initialize the blocks vector with all block types

Block Game::GetRandomBlock()
{
  // Randomly select a block from the blocks vector
  if (blocks.empty())
  {
    blocks = GetBlocks(); // Reset the blocks if empty
  }

  random_device rd;                                       // Obtain a random number from hardware
  mt19937 eng(rd());                                      // Seed the generator
  uniform_int_distribution<> distr(0, blocks.size() - 1); // Define the range

  int randomIndex = distr(eng);
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex); // Remove the block from the vector
  return block;
}

vector<Block> Game::GetBlocks()
{
  return {LBlock(), TBlock(), IBlock(), OBlock(), SBlock(), ZBlock(), JBlock()};
}

void Game::Draw()
{
  // Draw the grid and the current block
  grid.Draw();
  currentBlock.Draw();
} // Draw the grid and the current block

void Game::Update()
{
  int keyPressed = GetKeyPressed();
  switch (keyPressed)
  {
  case KEY_LEFT:
    MoveBlockL(); // Move the block left
    break;
  case KEY_RIGHT:
    MoveBlockR(); // Move the block right
    break;
  case KEY_DOWN:
    MoveBlockD(); // Move the block down
    break;
  case KEY_UP:
    RotateBlock(); // Rotate the block
    break;
  default:
    break; // No action for other keys
  }
}

void Game::MoveBlockL()
{
  currentBlock.Move(0, -1); // Move the current block left by 1 column
  if (isBlockOut() || !BlockFits())
  {
    currentBlock.Move(0, 1); // Move back to the right if out of bounds
  }
}

void Game::MoveBlockR()
{
  currentBlock.Move(0, 1); // Move the current block right by 1 column
  if (isBlockOut() || !BlockFits())
  {
    currentBlock.Move(0, -1); // Move back to the left if out of bounds or doesn't fit
  }
}

void Game::MoveBlockD()
{
  currentBlock.Move(1, 0); // Move the current block down by 1 row
  if (isBlockOut() || !BlockFits())
  {
    currentBlock.Move(-1, 0); // Move back up if out of bounds or doesn't fit
    LockBlock();              // Lock the block in place
  }
}

bool Game::isBlockOut()
{
  vector<Position> blockPositions = currentBlock.GetCurrentBlock();
  for (Position pos : blockPositions)
  {
    if (grid.CheckCollision(pos.row, pos.col))
    {
      return true; // Block is out of bounds
    }
  }
  return false; // Block is within bounds
}

void Game::RotateBlock()
{
  currentBlock.Rotate(); // Rotate the current block
  if (isBlockOut() || !BlockFits())
  {
    currentBlock.Rotate(); // Rotate back if out of bounds
    currentBlock.Rotate(); // Rotate back again to the original position
    currentBlock.Rotate(); // Rotate back again to the original position
  }
}

void Game::LockBlock()
{
  vector<Position> blockPositions = currentBlock.GetCurrentBlock();
  for (Position pos : blockPositions)
  {
    grid.grid[pos.row][pos.col] = currentBlock.id; // Lock the block in the grid
  }
  currentBlock = nextBlock;     // Set the next block as the current block
  nextBlock = GetRandomBlock(); // Get a new random block
  if (isBlockOut())
  {
    // Game over condition
    // Handle game over logic here (e.g., reset the game, show a message, etc.)
  }
}

bool Game::BlockFits()
{
  vector<Position> blockPositions = currentBlock.GetCurrentBlock();
  for (Position pos : blockPositions)
  {
    if (grid.CheckCollision(pos.row, pos.col) || !grid.isEmpty(pos.row, pos.col))
    {
      return false; // Block does not fit in the grid
    }
  }
  return true; // Block fits in the grid
}
