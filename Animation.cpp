#include "Animation.h"


Animation::Animation(void)
{
}
/*-----------------------------------------------*/
Animation::Animation(std::string name, AnimationFrame* frames, int numFrames)
{
	this->name = name;
	this->frames = frames;
	this->numFrames = numFrames;
}
/*-----------------------------------------------*/
Animation::~Animation(void)
{
}
