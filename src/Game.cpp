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
  score = 0;                                   // Initialize the score
  InitAudioDevice();                           // Initialize audio device
  music = LoadMusicStream("Sounds/music.mp3"); // Load the music stream
  PlayMusicStream(music);
  rotate = LoadSound("Sounds/rotate.wav"); // Play the music stream
  clear = LoadSound("Sounds/clear.wav");   // Play the clear sound
}
Game::~Game()
{
  UnloadSound(rotate);      // Unload the sound
  UnloadSound(clear);       // Unload the sound
  UnloadMusicStream(music); // Unload the music stream
  CloseAudioDevice();       // Close the audio device
  // Clean up other resources if needed
}
Block Game::getNextBlock()
{
  return nextBlock; // Return the next block
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
  currentBlock.Draw(0, 0);

  vector<Position> landingBlock;
  currentBlock.PreviewLanding(landingBlock, grid); // Preview the landing position of the block
} // Draw the grid and the current block

float Game::GetSpeed()
{
  // Gradually increase speed as the score increments
  return max(0.12f, 0.5f - (score * 0.0004f)); // Start with a slower speed and decrease linearly with score, with a minimum speed of 0.1f
}

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

  // Check if the block is at its final position
  if (currentBlock.IsAtFinalPosition(grid))
  {
    LockBlock(); // Lock the block in place
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
    else
    {
      FixBlockPosition(); // Fix the block's position if necessary
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
    else
    {
      FixBlockPosition(); // Fix the block's position if necessary
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
    else
    {
      FixBlockPosition(); // Fix the block's position if necessary
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
    else
    {
      FixBlockPosition(); // Fix the block's position if necessary
      PlaySound(rotate);  // Play the rotation sound
    }
  }
}
void Game::FixBlockPosition()
{
  vector<Position> blockPositions = currentBlock.GetCurrentBlock();
  int minCol = 0;

  // Find the leftmost column of the block
  for (Position pos : blockPositions)
  {
    if (pos.col < minCol)
    {
      minCol = pos.col;
    }
  }

  // If the block is out of bounds on the left, shift it to the right
  if (minCol < 0)
  {
    currentBlock.Move(0, -minCol);
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
  if (currentBlock.IsAtFinalPosition(grid) || !BlockFits())
  {
    isGameOver = true; // Game over if the new block doesn't fit
  }
  nextBlock = GetRandomBlock();           // Get a new random block
  int rowsCleared = grid.ClearFullRows(); // Clear any full rows in the grid
  if (rowsCleared > 0)
  {
    PlaySound(clear); // Play the clear sound
  }
  UpdateScore(rowsCleared, 1);
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
  isGameOver = false;              // Reset the game over state
  score = 0;                       // Reset the score
}

void Game::UpdateScore(int clearedRows, int moveDown)
{
  switch (clearedRows)
  {
  case 1:
    score += 100;
    break;
  case 2:
    score += 300;
    break;
  case 3:
    score += 500;
    break;
  case 4:
    score += 1000;
    break;
  default:
    break;
  }
  if (moveDown > 0)
  {
    score += moveDown * 10; // Add bonus points for moving down
  }
}
