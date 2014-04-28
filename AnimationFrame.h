#pragma once

class AnimationFrame
{
public:
	AnimationFrame(void);
	AnimationFrame(float tu, float tv, float tWidth, float tHeight);
	~AnimationFrame(void);
	
	// Variables
	float tu, tv;
	float tWidth, tHeight;
};

