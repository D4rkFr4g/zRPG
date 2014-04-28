#pragma once
#include <string>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation(void);
	Animation(std::string name, AnimationFrame* frames, int numFrames);
	~Animation(void);

	// Variables
	std::string name;
	AnimationFrame* frames;
	int numFrames;
};

