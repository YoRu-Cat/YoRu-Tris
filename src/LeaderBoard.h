#pragma once
#include <vector>
#include <fstream>
#include <raylib.h>
#include <string>

using namespace std;

struct ScoreEntry
{
  string playerName;
  int score;
  int level;
};

class LeaderBoard
{
private:
  vector<ScoreEntry> highScores;
  const string SAVE_FILE = "highscores.txt";
  const int MAX_ENTRIES = 10;

public:
  LeaderBoard();
  ~LeaderBoard();

  void DrawLB();
  void addScore(const string &playerName, int score, int level);
  void saveToFile();
  void loadFromFile();
  vector<ScoreEntry> getHighScores() const;
  void clearScores();
};
