#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"
using namespace std;

class Block
{
private:
    int size;
    int rotation;
    vector<Color> colors;

public:
    Block();
    void Draw();
    int id;
    map<int, vector<Position>> block;
};