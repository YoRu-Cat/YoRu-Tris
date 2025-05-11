// filepath: c:\Users\YoRu\OneDrive\Desktop\YoRutris\src\Anim.cpp
#include "Anim.h"

Animation::Animation(const char *imagePath, int frames, float framesPerSecond)
{
  image = LoadImageAnim(imagePath, &numFrames);
  texture = LoadTextureFromImage(image);

  // Use the provided frames parameter if it's valid, otherwise use numFrames from LoadImageAnim
  if (frames > 0)
    numFrames = frames;

  currentFrame = 0;
  frameDuration = 1.0f / framesPerSecond;
  frameAccumulator = 0.0f;
  loopAnimation = true;
  scale = 1.0f;

  sourceRec = {0, 0, (float)image.width / numFrames, (float)image.height};
}

Animation::~Animation()
{
  UnloadTexture(texture);
  UnloadImage(image);
}

void Animation::Update(float deltaTime)
{
  // Update animation with delta time for smoother transitions
  frameAccumulator += deltaTime;

  if (frameAccumulator >= frameDuration)
  {
    currentFrame++;

    if (currentFrame >= numFrames)
    {
      if (loopAnimation)
        currentFrame = 0; // Loop back to the first frame
      else
        currentFrame = numFrames - 1; // Stay on last frame
    }

    // Update texture with current frame data
    unsigned int nextFrameDataOffset = image.width * image.height * 4 * currentFrame;
    UpdateTexture(texture, ((unsigned char *)image.data) + nextFrameDataOffset);

    frameAccumulator -= frameDuration;
  }
}

void Animation::Draw(float posX, float posY)
{
  DrawTextureEx(texture, {posX, posY}, 0.0f, scale, WHITE);
}

void Animation::GetTexture(Texture2D &tex)
{
  tex = texture;
}

void Animation::SetFramesPerSecond(float fps)
{
  if (fps > 0)
    frameDuration = 1.0f / fps;
}

void Animation::SetLooping(bool loop)
{
  loopAnimation = loop;
}

void Animation::Reset()
{
  currentFrame = 0;
  frameAccumulator = 0.0f;

  // Reset texture to first frame
  if (image.data != nullptr)
  {
    UpdateTexture(texture, image.data);
  }
}
void Animation::DrawFrame()
{
  // Get screen dimensions
  float screenWidth = (float)GetScreenWidth();
  float screenHeight = (float)GetScreenHeight();

  // Calculate the width of a single frame
  float frameWidth = (float)image.width / numFrames;
  float frameHeight = (float)image.height;

  // Calculate scale to fit the screen while maintaining aspect ratio
  // Using a divisor to reduce the size (adjust this value as needed)
  float divisor = 1.0f; // Higher values = smaller animation

  float scaleX = screenWidth / (frameWidth * divisor);
  float scaleY = screenHeight / (frameHeight * divisor);

  // Use the smaller scale to ensure the animation fits on screen
  float newScale = fminf(scaleX, scaleY);

  // Calculate position to center the animation
  float posX = (screenWidth - frameWidth * newScale) * 0.0f;
  float posY = (screenHeight - frameHeight * newScale) * 0.5f;

  // Draw the texture centered and scaled
  DrawTextureEx(texture, {posX, posY}, 0.0f, newScale, WHITE);
}