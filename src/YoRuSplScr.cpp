#include "raylib.h"
#include "YoRuSplScr.h"
#include <cmath>

const int MAX_FRAME_DELAY = 60;
const int MIN_FRAME_DELAY = 1;

SplashScreen::SplashScreen(const char *gifPath, int frames, float displayTime, float framesPerSecond)
{
  image = LoadImageAnim(gifPath, &numFrames);
  texture = LoadTextureFromImage(image);

  currentFrame = 0;
  frameDuration = 1.0f / framesPerSecond;
  frameAccumulator = 0.0f;
  isComplete = false;
  animationComplete = false;
  duration = displayTime;
  timer = 0.0f;

  sourceRec = {0, 0, (float)image.width, (float)image.height};
  AdjustToScreenSize();
}

SplashScreen::~SplashScreen()
{
  UnloadTexture(texture);
  UnloadImage(image);
}

bool SplashScreen::Update(float deltaTime)
{
  timer += deltaTime;

  // Update animation with delta time for smoother transitions
  if (!animationComplete)
  {
    frameAccumulator += deltaTime;

    if (frameAccumulator >= frameDuration)
    {
      currentFrame++;

      if (currentFrame >= numFrames)
      {
        currentFrame = numFrames - 1;
        animationComplete = true;
      }
      else
      {
        unsigned int nextFrameDataOffset = image.width * image.height * 4 * currentFrame;
        UpdateTexture(texture, ((unsigned char *)image.data) + nextFrameDataOffset);
      }

      frameAccumulator -= frameDuration;
    }
  }

  // Check if splash screen duration is over
  if (timer >= duration)
  {
    isComplete = true;
  }

  return isComplete;
}

void SplashScreen::Draw()
{
  float posX = (GetScreenWidth() - (image.width * scale)) / 2;
  float posY = (GetScreenHeight() - (image.height * scale)) / 2;

  DrawTextureEx(texture, {posX, posY}, 0.0f, scale, WHITE);
}

void SplashScreen::AdjustToScreenSize()
{
  scale = 1.0f; // Keep the original scale of the image
}

void SplashScreen::SetFramesPerSecond(float fps)
{
  if (fps > 0)
    frameDuration = 1.0f / fps;
}
void SplashScreen::Reset()
{
  // Mark the splash screen as complete to close it
  isComplete = true;

  // Clear the texture data to create a blank screen
  // This will effectively hide the splash screen image
  Color blankColor = {0, 0, 0, 0}; // Transparent black
  Image blankImage = GenImageColor(image.width, image.height, blankColor);
  UpdateTexture(texture, blankImage.data);
  UnloadImage(blankImage);

  // Reset other state variables
  timer = 0.0f;
  currentFrame = 0;
  animationComplete = true;
}
