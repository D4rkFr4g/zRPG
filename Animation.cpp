#include "Animation.h"


Animation::Animation(void)
{
}
/*-----------------------------------------------*/
Animation::Animation(std::string name, std::vector<AnimationFrame> frames, int numFrames)
{
	this->name = name;
	this->frames = frames;
	this->numFrames = numFrames;
}
/*-----------------------------------------------*/
Animation::~Animation(void)
{
}
