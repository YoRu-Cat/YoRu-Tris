#include "raylib.h"
#include <cmath>
#include "YoRuSplScr.h"

int main()
{
	// Initialization
	int displayWidth = GetMonitorWidth(0);
	int displayHeight = GetMonitorHeight(0);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
	InitWindow(displayWidth, displayHeight, "YoRu Screen");
	SetTargetFPS(60);

	SplashScreen splash("resources/YoRu_n.gif", 10, 6.0f, 10.0f);

	// Main game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		// Handle window resizing
		if (IsWindowResized())
		{
			splash.AdjustToScreenSize();
		}

		// Handle keyboard input
		if (IsKeyPressed(KEY_RIGHT))
			splash.SetFramesPerSecond(20.0f);
		else if (IsKeyPressed(KEY_LEFT))
			splash.SetFramesPerSecond(10.0f);

		if (IsKeyPressed(KEY_F11) || IsKeyPressed(KEY_ESCAPE))
		{
			if (IsWindowFullscreen())
			{
				ToggleFullscreen();
				SetWindowSize(displayWidth / 2, displayHeight / 2);
			}
			else
			{
				ToggleFullscreen();
			}
			splash.AdjustToScreenSize();
		}

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
			ClearBackground(BLACK);
			// Draw large "COMING SOON" text centered on screen
			const char *message = "COMING SOON";
			const char *sub = "A Project by YoRu";

			// Calculate sizes and positions for perfect centering
			int fontSize = 120;
			int subFontSize = 40;
			int textWidth = MeasureText(message, fontSize);
			int subTextWidth = MeasureText(sub, subFontSize);

			// Center horizontally for both texts
			int posX = (GetScreenWidth() - textWidth) / 2;
			int posY = (GetScreenHeight() - fontSize) / 2;

			// Position subtitle with better spacing (20 pixels below main text)
			int subPosX = (GetScreenWidth() - subTextWidth) / 2;
			int subPosY = posY + fontSize + 20;

			// Draw both texts
			DrawText(message, posX, posY, fontSize, WHITE);
			DrawText(sub, subPosX, subPosY, subFontSize, LIGHTGRAY);
		}
		else
		{
			ClearBackground(BLACK);
			DrawText("Welcome to YoRutris!", GetScreenWidth() / 2 - MeasureText("Welcome to YoRutris!", 100) / 2,
							 GetScreenHeight() / 2 - 80, 100, WHITE);
			DrawText("Press ENTER to start", GetScreenWidth() / 2 - MeasureText("Press ENTER to start", 40) / 2,
							 GetScreenHeight() / 2 + 40, 40, LIGHTGRAY);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
