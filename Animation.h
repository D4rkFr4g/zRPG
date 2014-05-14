#pragma once
#include <string>
#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation(void);
	Animation(std::string name, std::vector<AnimationFrame> frames, int numFrames);
	~Animation(void);

	// Variables
	std::string name;
	std::vector<AnimationFrame> frames;
	int numFrames;
};

