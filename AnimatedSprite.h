#pragma once
#include <map>
#include "sprite.h"
#include "AnimationData.h"

class AnimatedSprite :
	public Sprite
{
public:
	// Constructors
	AnimatedSprite(void);
	AnimatedSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
	~AnimatedSprite(void);
	
	// Functions
	void update(int ms);
	void setAnimation(std::string animation);
	void updatePosition(float x , float y);

	// Variables
	bool isAnimated;
	float maxSpeedX;
	float maxSpeedY;
	AnimationData curAnimation;
	std::map<std::string, AnimationData> animations;
};

