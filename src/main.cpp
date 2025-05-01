#include "raylib.h"
#include <cmath>
#include "YoRuSplScr.h"
#include "Grid.h"
#include "blocks.cpp"
#include "Block.h"

int main()
{
	// Initialization
	int displayWidth = GetMonitorWidth(0);
	int displayHeight = GetMonitorHeight(0);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
	InitWindow(displayWidth, displayHeight, "YoRu Screen");
	SetTargetFPS(60);

	SplashScreen splash("resources/YoRu_n.gif", 10, 6.0f, 10.0f);
	Color dBlu = {44, 44, 127, 255};
	Grid grid = Grid();
	OBlock lBlock = OBlock();
	// Main game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		// Update splash screen
		if (splash.Update(deltaTime))
		{
			// Don't break the loop, just reset the splash screen
			splash.Reset(); // Reset splash screen when complete
		}

		BeginDrawing();
		ClearBackground(BLACK);

		// Create a boolean to track game state
		static bool check = false;

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
		else if (check)
		{
			ClearBackground(dBlu);
			grid.Draw();
			lBlock.Draw();
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
