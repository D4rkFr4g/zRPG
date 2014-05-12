#pragma once
#include "Animation.h"

class AnimationData
{
public:
	AnimationData(void);
	AnimationData(Animation def, int timeToNextFrame, bool isRepeating);
	~AnimationData(void);

	// Functions
	void resetElapsedTime();
	void advanceFrame();
	void updateTime(int ms);
   bool timeToSendEvent();

	// Variables
	Animation def;
	int currentFrame;
	int timeToNextFrame;
   int eventFrame;
	int elapsedTime;
	bool isRepeating;
};

