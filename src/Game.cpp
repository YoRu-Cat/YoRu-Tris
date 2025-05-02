#include "Game.h"
#include <random>
using namespace std;

Game::Game()
{
  grid = Grid();
  blocks = GetBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock(); // Initialize the current and next blocks
  isGameOver = false;
}

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
  vector<Position> landingBlock;
  currentBlock.PreviewLanding(landingBlock, grid); // Preview the landing position of the block
} // Draw the grid and the current block

void Game::Update()
{
  int keyPressed = GetKeyPressed();
  if (isGameOver && keyPressed == KEY_ENTER) // Restart the game if it's over and Enter is pressed
  {
    isGameOver = false; // Reset the game state
    ResetGame();
  }
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
  if (!isGameOver) // Check if the game is not over before moving
  {
    currentBlock.Move(0, -1); // Move the current block left by 1 column
    if (isBlockOut() || !BlockFits())
    {
      currentBlock.Move(0, 1); // Move back to the right if out of bounds
    }
  }
}

void Game::MoveBlockR()
{
  if (!isGameOver) // Check if the game is not over before moving
  {
    currentBlock.Move(0, 1); // Move the current block right by 1 column
    if (isBlockOut() || !BlockFits())
    {
      currentBlock.Move(0, -1); // Move back to the left if out of bounds
    }
  }
}

void Game::MoveBlockD()
{
  if (!isGameOver) // Check if the game is not over before moving
  {
    currentBlock.Move(1, 0); // Move the current block down by 1 row
    if (isBlockOut() || !BlockFits())
    {
      currentBlock.Move(-1, 0); // Move back up if out of bounds
      LockBlock();              // Lock the block in place
    }
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
  if (!isGameOver) // Check if the game is not over before rotating
  {
    currentBlock.Rotate(); // Rotate the current block
    if (isBlockOut() || !BlockFits())
    {
      currentBlock.UndoRotate(); // Undo the rotation if it doesn't fit
    }
  }
}

void Game::LockBlock()
{
  vector<Position> blockPositions = currentBlock.GetCurrentBlock();
  for (Position pos : blockPositions)
  {
    grid.grid[pos.row][pos.col] = currentBlock.id; // Lock the block in the grid
  }
  currentBlock = nextBlock; // Set the next block as the current block
  if (isBlockOut() || !BlockFits())
  {
    isGameOver = true; // Game over if the new block doesn't fit
  }
  nextBlock = GetRandomBlock(); // Get a new random block
  grid.ClearFullRows();         // Clear any full rows in the grid
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

void Game::ResetGame()
{
  grid.Initialize();               // Initialize the grid
  blocks = GetBlocks();            // Reset the blocks
  currentBlock = GetRandomBlock(); // Get a new random block
  nextBlock = GetRandomBlock();    // Get a new random block for the next piece
}
