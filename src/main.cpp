#include "raylib.h"
#include <cmath>
#include <string>
#include "YoRuSplScr.h"
#include "Game.h"
#include "Anim.h" // Add this include for the Animation class
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

	// Create background animation
	Animation backgroundAnim("./Media/5.gif", 35, 10.0f); // Adjust path, frames, and fps as needed
	backgroundAnim.SetLooping(true);											// Scale to fit screen width - adjust divisor based on your animation's native size

	LeaderBoard leaderboard;
	static bool showLeaderboard = false;

	Game game = Game();
	string scoreText = "Score: ";
	string nextText = "Next: ";
	string gameOverText = "Game Over!";
	string linesText = "Lines: ";
	string yourScoreText = "Your Score: ";

	SplashScreen splash("resources/YoRu_n.gif", 10, 6.0f, 10.0f);
	// Color dBlu = {44, 44, 127, 255};

	// Main game loop
	while (!WindowShouldClose())
	{
		static bool check = false;
		float deltaTime = GetFrameTime();

		// Update animation
		backgroundAnim.Update(deltaTime);

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
			UpdateMusicStream(game.music); // Draw animated background instead of solid color
			if (!backgroundAnim.IsValid())
			{
				// Animation failed to load - draw a fallback color
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
			}
			else
			{
				backgroundAnim.DrawFrame();
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
			}

			// Draw the score in the top-right corner
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
			DrawRectangleRounded(scoreRect, 0, 6, Fade(RAYWHITE, 0.6f)); // Semi-transparent gray

			// Draw an outline for the scoreRect with a margin of 2 pixels and 3 pixels thick
			Rectangle scoreOutlineRect = {scoreRect.x - 2, scoreRect.y - 2, scoreRect.width + 4, scoreRect.height + 4};
			DrawRectangleRoundedLines(scoreOutlineRect, 0, 6, 3, Fade(RAYWHITE, 0.6f));
			// Draw a larger rectangle beside the "Next" text

			Rectangle nextRect = {scoreRect.x, scoreRect.y + scoreRect.height + 30.0f, scoreRect.width, scoreRect.height + 50.0f};
			DrawRectangleRounded(nextRect, 0, 6, Fade(RAYWHITE, 0.6f));

			// Draw an outline with a margin of 2 pixels and 3 pixels thick
			Rectangle outlineRect = {nextRect.x - 2, nextRect.y - 2, nextRect.width + 4, nextRect.height + 4};
			DrawRectangleRoundedLines(outlineRect, 0, 6, 3, Fade(RAYWHITE, 0.6f));

			// Draw the next block in the middle of the nextRect box
			game.getNextBlock().Move(0, 0);			 // Reset the block position
			game.getNextBlock().Draw(1100, 235); // Draw the next block inside the rectangle
			// Semi-transparent white
			// Draw the score inside the rectangle
			string scoreValue = to_string(game.score);
			Vector2 scoreValueSize = MeasureTextEx(font, scoreValue.c_str(), 64, 2);
			DrawTextEx(font, scoreValue.c_str(), {scoreRect.x + (scoreRect.width - scoreValueSize.x) / 2, scoreRect.y + (scoreRect.height - scoreValueSize.y) / 2}, 64, 2, dGry);

			// Draw the lines cleared text
			Rectangle linesRect = {scoreRect.x, nextRect.y + nextRect.height + 30.0f, scoreRect.width, scoreRect.height};
			DrawRectangleRounded(linesRect, 0, 6, Fade(RAYWHITE, 0.6f));

			// Draw the outline
			Rectangle linesOutlineRect = {linesRect.x - 2, linesRect.y - 2, linesRect.width + 4, linesRect.height + 4};
			DrawRectangleRoundedLines(linesOutlineRect, 0, 6, 3, Fade(RAYWHITE, 0.6f));

			// Draw the "Lines" text
			DrawTextEx(font, linesText.c_str(), {xPos, linesRect.y}, 64, 2, WHITE);

			// Draw the lines count inside the rectangle
			string linesClearedText = to_string(game.grid.rowCleared);
			Vector2 linesClearedTextSize = MeasureTextEx(font, linesClearedText.c_str(), 64, 2);
			DrawTextEx(font, linesClearedText.c_str(), {linesRect.x + (linesRect.width - linesClearedTextSize.x) / 2, linesRect.y + (linesRect.height - linesClearedTextSize.y) / 2}, 64, 2, dGry);

			// Draw the level box
			Rectangle levelRect = {scoreRect.x, linesRect.y + linesRect.height + 30.0f, scoreRect.width, scoreRect.height};
			DrawRectangleRounded(levelRect, 0, 6, Fade(RAYWHITE, 0.6f));

			// Draw the level outline
			Rectangle levelOutlineRect = {levelRect.x - 2, levelRect.y - 2, levelRect.width + 4, levelRect.height + 4};
			DrawRectangleRoundedLines(levelOutlineRect, 0, 6, 3, Fade(RAYWHITE, 0.6f));

			// Draw the "Level" text
			DrawTextEx(font, "Level:", {xPos, levelRect.y}, 64, 2, WHITE);

			// Draw the level number inside the rectangle
			string levelText = to_string(game.GetLevel());
			Vector2 levelTextSize = MeasureTextEx(font, levelText.c_str(), 64, 2);
			DrawTextEx(font, levelText.c_str(), {levelRect.x + (levelRect.width - levelTextSize.x) / 2, levelRect.y + (levelRect.height - levelTextSize.y) / 2}, 64, 2, dGry);

			game.Draw();
			if (game.isGameOver)
			{
				continue; // Skip the game over text if the game is not over
			}
		}
		else if (game.isGameOver)
		{
			// Draw game over screen
			backgroundAnim.DrawFrame();
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));

			// Only save the score once
			if (!game.GetScoreSaved())
			{
				// Save score to leaderboard
				leaderboard.addScore("Player", game.score, game.GetLevel());
				game.SetScoreSaved(true);
			}

			// Draw game over text and score
			Vector2 gameOverSize = MeasureTextEx(font, gameOverText.c_str(), 100, 2);
			DrawTextEx(font, gameOverText.c_str(), {(float)(GetScreenWidth() - gameOverSize.x) / 2, (float)(GetScreenHeight() / 2 - 100)}, 100, 2, WHITE);

			// Draw the score
			string finalScore = yourScoreText + to_string(game.score);
			Vector2 scoreSize = MeasureTextEx(font, finalScore.c_str(), 64, 2);
			DrawTextEx(font, finalScore.c_str(), {(float)(GetScreenWidth() - scoreSize.x) / 2, (float)(GetScreenHeight() / 2 + 50)}, 64, 2, WHITE);

			// Draw restart prompt
			DrawText("Press Enter to restart", GetScreenWidth() / 2 - MeasureText("Press Enter to restart", 40) / 2, GetScreenHeight() / 2 + 150, 40, WHITE);
		}
		else if (showLeaderboard == true)
		{
			// Draw animated background with a darkened overlay
			backgroundAnim.DrawFrame();
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
			// Draw the leaderboard
			leaderboard.loadFromFile();
			leaderboard.DrawLB();
			if (IsKeyPressed(KEY_ENTER))
			{
				showLeaderboard = false; // Hide the leaderboard when Enter is pressed
			}
		}
		else
		{
			// Draw animated background with a darkened overlay for the welcome screen
			backgroundAnim.DrawFrame();
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));

			float centerY = GetScreenHeight() / 2;
			float startY = centerY - 300; // Start higher up to center everything

			// Title and start text
			DrawText("Welcome to YoRutris!", GetScreenWidth() / 2 - MeasureText("Welcome to YoRutris!", 100) / 2, startY, 100, WHITE);
			DrawText("Press ENTER to start", GetScreenWidth() / 2 - MeasureText("Press ENTER to start", 40) / 2, startY + 120, 40, LIGHTGRAY);

			// Leaderboard button
			// Common function to check if mouse is hovering over a rectangle
			auto isMouseOverRect = [](Rectangle rect)
			{
				Vector2 mousePos = GetMousePosition();
				return CheckCollisionPointRec(mousePos, rect);
			};

			// Leaderboard button
			Rectangle leaderboardRect = {(float)(GetScreenWidth() / 2 - 200), startY + 200, 400.0f, 64.0f};
			Color leaderboardColor = isMouseOverRect(leaderboardRect) ? Fade(LIGHTGRAY, 0.6f) : Fade(RAYWHITE, 0.6f);
			DrawRectangleRounded(leaderboardRect, 0, 6, leaderboardColor);
			Rectangle outlineRect = {leaderboardRect.x - 2, leaderboardRect.y - 2, leaderboardRect.width + 4, leaderboardRect.height + 4};
			DrawRectangleRoundedLines(outlineRect, 0, 6, 3, Fade(RAYWHITE, 0.6f));
			const char *leaderboardText = "Leaderboard";
			Vector2 textSize = MeasureTextEx(font, leaderboardText, 64, 2);
			DrawTextEx(font, leaderboardText, {leaderboardRect.x + (leaderboardRect.width - textSize.x) / 2, leaderboardRect.y + (leaderboardRect.height - textSize.y) / 2}, 64, 2, dGry);
			// Handle leaderboard button click
			if (isMouseOverRect(leaderboardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				// Add a state variable at the top of the file with other globals
				showLeaderboard = true; // Set the state when button is clicked
			}
			// Themes button
			Rectangle themesRect = {(float)(GetScreenWidth() / 2 - 200), startY + 300, 400.0f, 64.0f};
			Color themesColor = isMouseOverRect(themesRect) ? Fade(LIGHTGRAY, 0.6f) : Fade(RAYWHITE, 0.6f);
			DrawRectangleRounded(themesRect, 0, 6, themesColor);
			DrawRectangleRoundedLines({themesRect.x - 2, themesRect.y - 2, themesRect.width + 4, themesRect.height + 4}, 0, 6, 3, Fade(RAYWHITE, 0.6f));
			const char *themesText = "Themes";
			Vector2 themesSize = MeasureTextEx(font, themesText, 64, 2);
			DrawTextEx(font, themesText, {themesRect.x + (themesRect.width - themesSize.x) / 2, themesRect.y + (themesRect.height - themesSize.y) / 2}, 64, 2, dGry);

			// Settings button
			Rectangle settingsRect = {(float)(GetScreenWidth() / 2 - 200), startY + 400, 400.0f, 64.0f};
			Color settingsColor = isMouseOverRect(settingsRect) ? Fade(LIGHTGRAY, 0.6f) : Fade(RAYWHITE, 0.6f);
			DrawRectangleRounded(settingsRect, 0, 6, settingsColor);
			DrawRectangleRoundedLines({settingsRect.x - 2, settingsRect.y - 2, settingsRect.width + 4, settingsRect.height + 4}, 0, 6, 3, Fade(RAYWHITE, 0.6f));
			const char *settingsText = "Settings";
			Vector2 settingsSize = MeasureTextEx(font, settingsText, 64, 2);
			DrawTextEx(font, settingsText, {settingsRect.x + (settingsRect.width - settingsSize.x) / 2, settingsRect.y + (settingsRect.height - settingsSize.y) / 2}, 64, 2, dGry);

			// Exit button
			Rectangle exitRect = {(float)(GetScreenWidth() / 2 - 200), startY + 500, 400.0f, 64.0f};
			Color exitColor = isMouseOverRect(exitRect) ? Fade(LIGHTGRAY, 0.6f) : Fade(RAYWHITE, 0.6f);
			DrawRectangleRounded(exitRect, 0, 6, exitColor);
			DrawRectangleRoundedLines({exitRect.x - 2, exitRect.y - 2, exitRect.width + 4, exitRect.height + 4}, 0, 6, 3, Fade(RAYWHITE, 0.6f));
			const char *exitText = "Exit";
			Vector2 exitSize = MeasureTextEx(font, exitText, 64, 2);
			DrawTextEx(font, exitText, {exitRect.x + (exitRect.width - exitSize.x) / 2, exitRect.y + (exitRect.height - exitSize.y) / 2}, 64, 2, dGry);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
