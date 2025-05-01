#ifndef YORUSPLSCR_H
#define YORUSPLSCR_H

class SplashScreen
{
private:
	Image image;
	Texture2D texture;
	int currentFrame;
	float frameAccumulator;
	float frameDuration;
	int numFrames;
	bool isComplete;
	float duration;
	float timer;
	float scale;
	Rectangle sourceRec;
	bool animationComplete;

public:
	SplashScreen(const char *gifPath, int frames, float displayTime = 3.0f, float framesPerSecond = 10.0f);
	~SplashScreen();

	bool Update(float deltaTime);
	void Draw();
	void AdjustToScreenSize();
	void SetFramesPerSecond(float fps);

	bool IsComplete() const { return isComplete; }
	void Reset();
};

// Implementation

#endif // YORUSPLSCR_H