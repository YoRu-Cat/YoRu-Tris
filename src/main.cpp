#include "raylib.h"
#include <cmath>
#include <string>
#include "YoRuSplScr.h"
#include "Game.h"
using namespace std;

double lastTime = 0.0;
bool Trigger(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastTime >= interval)
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	// Initialization
	int displayWidth = GetMonitorWidth(0);
	int displayHeight = GetMonitorHeight(0);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
	InitWindow(displayWidth, displayHeight, "YoRu Screen");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

	Game game = Game();
	string scoreText = "Score: ";
	string nextText = "Next: ";
	string gameOverText = "Game Over!";
	SplashScreen splash("resources/YoRu_n.gif", 10, 6.0f, 10.0f);
	// Color dBlu = {44, 44, 127, 255};

	// Main game loop
	while (!WindowShouldClose())
	{
		static bool check = false;
		float deltaTime = GetFrameTime();
		// Update splash screen
		if (splash.Update(deltaTime))
		{
			// Don't break the loop, just reset the splash screen
			splash.Reset(); // Reset splash screen when complete
		}
		game.Update();
		if (check && !game.isGameOver && Trigger(game.GetSpeed()))
		{
			game.MoveBlockD(); // Move the block down every 0.15 seconds
		}

		BeginDrawing();
		ClearBackground(BLACK);

		// Create a boolean to track game state

		// Update the game state based on user input
		if (splash.IsComplete())
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				check = true;
			}
		}

		// Draw the appropriate screen
		if (!splash.IsComplete())
		{
			splash.Draw();
		}
		else if (check && !game.isGameOver)
		{
			UpdateMusicStream(game.music);
			ClearBackground(dBlu);
			// Draw the score in the top-right corner with a stylish design
			int gridWidth, gridHeight;
			game.grid.GetGridWidth(gridWidth, gridHeight);

			Vector2 textSize = MeasureTextEx(font, scoreText.c_str(), 64, 2);
			float padding = 200.0f;

			// Calculate the position to draw the score text
			float xPos = (GetScreenWidth() + gridWidth) / 2 - textSize.x / 2 - 100.0f; // Centered on the grid's right wall
			float yPos = padding;																											 // Align the text to the top of the screen with padding

			// Draw the score text
			DrawTextEx(font, scoreText.c_str(), {xPos, yPos}, 64, 2, WHITE);
			// Draw the "Next" text below the score
			DrawTextEx(font, nextText.c_str(), {xPos, yPos + textSize.y + 50.0f}, 64, 2, WHITE);
			// Draw a rectangle to display the score
			Rectangle scoreRect = {xPos + textSize.x + 10.0f, yPos, 400.0f, textSize.y};
			DrawRectangleRounded(scoreRect, 0, 6, Fade(dGry, 0.5f)); // Semi-transparent gray

			// Draw an outline for the scoreRect with a margin of 2 pixels and 3 pixels thick
			Rectangle scoreOutlineRect = {scoreRect.x - 2, scoreRect.y - 2, scoreRect.width + 4, scoreRect.height + 4};
			DrawRectangleRoundedLines(scoreOutlineRect, 0, 6, 3, Fade(dGry, 0.5f));
			// Draw a larger rectangle beside the "Next" text

			Rectangle nextRect = {scoreRect.x, scoreRect.y + scoreRect.height + 30.0f, scoreRect.width, scoreRect.height + 50.0f};
			DrawRectangleRounded(nextRect, 0, 6, Fade(dGry, 0.5f));

			// Draw an outline with a margin of 2 pixels and 3 pixels thick
			Rectangle outlineRect = {nextRect.x - 2, nextRect.y - 2, nextRect.width + 4, nextRect.height + 4};
			DrawRectangleRoundedLines(outlineRect, 0, 6, 3, Fade(dGry, 0.5f));

			// Draw the next block in the middle of the nextRect box
			game.getNextBlock().Move(0, 0);			 // Reset the block position
			game.getNextBlock().Draw(1100, 235); // Draw the next block inside the rectangle
			// Semi-transparent white
			// Draw the score inside the rectangle
			string scoreValue = to_string(game.score);
			Vector2 scoreValueSize = MeasureTextEx(font, scoreValue.c_str(), 64, 2);
			DrawTextEx(font, scoreValue.c_str(), {scoreRect.x + (scoreRect.width - scoreValueSize.x) / 2, scoreRect.y + (scoreRect.height - scoreValueSize.y) / 2}, 64, 2, WHITE);
			game.Draw();
			if (game.isGameOver)
			{
				continue; // Skip the game over text if the game is not over
			}
		}
		else if (game.isGameOver)
		{
			ClearBackground(dBlu);
			Vector2 gameOverTextSize = MeasureTextEx(font, gameOverText.c_str(), 100, 2);
			DrawTextEx(font, gameOverText.c_str(), {(GetScreenWidth() - gameOverTextSize.x) / 2, (GetScreenHeight() - gameOverTextSize.y) / 2 - 40}, 100, 2, WHITE);

			const char *restartText = "Press ENTER to restart";
			Vector2 restartTextSize = MeasureTextEx(font, restartText, 40, 2);
			DrawText(restartText, (GetScreenWidth() - restartTextSize.x) / 2, (GetScreenHeight() + gameOverTextSize.y) / 2 + 20, 40, LIGHTGRAY);
		}
		else
		{
			ClearBackground(BLACK);
			DrawText("Welcome to YoRutris!", GetScreenWidth() / 2 - MeasureText("Welcome to YoRutris!", 100) / 2, GetScreenHeight() / 2 - 80, 100, WHITE);
			DrawText("Press ENTER to start", GetScreenWidth() / 2 - MeasureText("Press ENTER to start", 40) / 2, GetScreenHeight() / 2 + 40, 40, LIGHTGRAY);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
