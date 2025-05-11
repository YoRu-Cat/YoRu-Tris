// Anim.h
#ifndef ANIM_H
#define ANIM_H

#include "raylib.h"
#include "raymath.h"
#include <cmath>

class Animation
{
private:
  Image image;
  Texture2D texture;
  Rectangle sourceRec;
  int numFrames;
  int currentFrame;
  float frameDuration;
  float frameAccumulator;
  bool loopAnimation;
  float scale;

public:
  Animation(const char *imagePath, int frames, float framesPerSecond);
  ~Animation();

  void Update(float deltaTime);
  void Draw(float posX, float posY);
  void GetTexture(Texture2D &tex);

  void SetFramesPerSecond(float fps);
  void SetLooping(bool loop);
  void Reset();

  void DrawFrame();

  int GetCurrentFrame() const { return currentFrame; }
  int GetFrameCount() const { return numFrames; }
  float GetScale() const { return scale; }
  void SetScale(float newScale) { scale = newScale; }
  bool IsValid() const { return texture.id != 0; }
};

#endif // ANIM_H
