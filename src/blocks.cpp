#include "Block.h"
#include "Position.h"

class LBlock : public Block
{
public:
  LBlock()
  {
    id = 5;
    block[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)}; // L shape
    block[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)}; // L shape rotated
    block[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)}; // L shape rotated again
    block[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)}; // L shape rotated again
    Move(0, 13);                                                                 // Initialize offsets to 0
  }
};

class JBlock : public Block
{
public:
  JBlock()
  {
    id = 6;
    block[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)}; // J shape
    block[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)}; // J shape rotated
    block[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)}; // J shape rotated again
    block[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)}; // J shape rotated again
    Move(0, 13);                                                                 // Initialize offsets to 0
  }
};

class IBlock : public Block
{
public:
  IBlock()
  {
    id = 7;
    block[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)}; // I shape
    block[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)}; // I shape rotated
    block[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}; // I shape rotated again
    block[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)}; // I shape rotated again
    Move(-1, 13);                                                                // Initialize offsets to 0
  }
};

class OBlock : public Block
{
public:
  OBlock()
  {
    id = 8;
    block[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}; // O shape
    block[1] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}; // O shape rotated (same as original)
    block[2] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}; // O shape rotated again (same as original)
    block[3] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}; // O shape rotated again (same as original)
    Move(0, 14);                                                                 // Initialize offsets to 0
  }
};

class TBlock : public Block
{
public:
  TBlock()
  {
    id = 9;
    block[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)}; // T shape
    block[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)}; // T shape rotated
    block[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)}; // T shape rotated again
    block[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)}; // T shape rotated again
    Move(0, 13);                                                                 // Initialize offsets to 0
  }
};

class SBlock : public Block
{
public:
  SBlock()
  {
    id = 10;
    block[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)}; // S shape
    block[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)}; // S shape rotated
    block[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)}; // S shape rotated again
    block[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)}; // S shape rotated again
    Move(0, 13);
  }
};

class ZBlock : public Block
{
public:
  ZBlock()
  {
    id = 11;
    block[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)}; // Z shape
    block[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)}; // Z shape rotated
    block[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)}; // Z shape rotated again
    block[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)}; // Z shape rotated again
    Move(0, 13);                                                                 // Initialize offsets to 0
  }
};

class CBlock : public Block
{
public:
  CBlock()
  {
    id = 3;
    block[0] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 2)}; // C shape
    block[1] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)}; // C shape rotated
    block[2] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 2), Position(2, 0)}; // C shape rotated again
    block[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)}; // C shape rotated again
    Move(0, 13);
  }
};

class VBlock : public Block
{
public:
  VBlock()
  {
    id = 4;
    block[0] = {Position(0, 0), Position(1, 0), Position(1, 1)}; // V shape
    block[1] = {Position(0, 1), Position(1, 1), Position(2, 1)}; // V shape rotated
    block[2] = {Position(0, 0), Position(0, 1), Position(0, 2)}; // V shape rotated again
    block[3] = {Position(0, 0), Position(1, 0), Position(2, 0)}; // V shape rotated again (vertical orientation)
    Move(0, 13);                                                 // Initialize offsets to 0
  }
};

class IIBlock : public Block
{
public:
  IIBlock()
  {
    id = 12;
    block[0] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)}; // II shape
    block[1] = {Position(0, 0), Position(1, 0), Position(2, 0), Position(0, 1), Position(1, 1), Position(2, 1)}; // II shape rotated
    block[2] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)}; // II shape rotated again (same as original)
    block[3] = {Position(0, 0), Position(1, 0), Position(2, 0), Position(0, 1), Position(1, 1), Position(2, 1)}; // II shape rotated again (same as rotation 1)
    Move(0, 13);                                                                                                 // Initialize offsets to 0
  }
};