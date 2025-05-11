#include "LeaderBoard.h"
#include <fstream>

LeaderBoard::LeaderBoard()
{
  loadFromFile();
}

LeaderBoard::~LeaderBoard()
{
  saveToFile();
}

void LeaderBoard::DrawLB()
{
  vector<ScoreEntry> scores = getHighScores();
  // Draw a border around the leaderboard
  DrawRectangleLinesEx({(float)(GetScreenWidth() / 2 - 400), (float)(GetScreenHeight() / 2 - 400), 800.0f, 700.0f}, 5.0f, WHITE);

  // Draw the title
  DrawText("Leaderboard", GetScreenWidth() / 2 - MeasureText("Leaderboard", 100) / 2, GetScreenHeight() / 2 - 360, 100, WHITE);

  // Draw decorative line
  DrawLine(GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 260, GetScreenWidth() / 2 + 300, GetScreenHeight() / 2 - 260, WHITE);

  // Draw "Top 5 Scores" header
  DrawText("Top 5 Scores:", GetScreenWidth() / 2 - MeasureText("Top 5 Scores:", 80) / 2, GetScreenHeight() / 2 - 200, 80, WHITE);

  // Draw scores
  for (size_t i = 0; i < min(scores.size(), size_t(5)); i++)
  {
    string scoreText = scores[i].playerName + ": " + to_string(scores[i].score);
    DrawText(scoreText.c_str(), GetScreenWidth() / 2 - MeasureText(scoreText.c_str(), 70) / 2, GetScreenHeight() / 2 - 100 + i * 80, 70, WHITE);
  }
}

void LeaderBoard::addScore(const string &playerName, int score, int level)
{
  // Check if this exact score is already in the leaderboard
  for (const auto &entry : highScores)
  {
    if (entry.playerName == playerName && entry.score == score && entry.level == level)
    {
      return; // Skip adding duplicate score
    }
  }

  // Add the score if it's not a duplicate
  ScoreEntry entry{playerName, score, level};
  highScores.push_back(entry);

  // Simple bubble sort implementation (easier to understand than sort)
  for (size_t i = 0; i < highScores.size(); i++)
  {
    for (size_t j = 0; j < highScores.size() - 1; j++)
    {
      if (highScores[j].score < highScores[j + 1].score)
      {
        // Swap entries
        ScoreEntry temp = highScores[j];
        highScores[j] = highScores[j + 1];
        highScores[j + 1] = temp;
      }
    }
  }

  // Keep only top MAX_ENTRIES scores
  if (highScores.size() > static_cast<size_t>(MAX_ENTRIES))
  {
    // Remove excess entries
    while (highScores.size() > static_cast<size_t>(MAX_ENTRIES))
    {
      highScores.pop_back();
    }
  }

  // Save to file immediately after adding a score
  saveToFile();
}

void LeaderBoard::loadFromFile()
{
  ifstream file("scores.txt");
  if (!file.is_open())
    return;

  string name;
  int score, level;
  while (file >> name >> score >> level)
  {
    addScore(name, score, level);
  }
  file.close();
}

vector<ScoreEntry> LeaderBoard::getHighScores() const
{
  return highScores;
}

void LeaderBoard::clearScores()
{
  highScores.clear();
  ofstream file("scores.txt", ios::trunc); // Open file in truncate mode
  if (file.is_open())
  {
    file.close();
  }
}

void LeaderBoard::saveToFile()
{
  ofstream file("scores.txt", ios::trunc); // Open in truncate mode
  if (!file.is_open())
    return;

  // Write all scores
  for (const auto &entry : highScores)
  {
    file << entry.playerName << " " << entry.score << " " << entry.level << "\n";
  }
  file.close();
}
