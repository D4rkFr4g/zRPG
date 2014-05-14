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
	virtual ~AnimatedSprite(void);
	
	// Functions
   virtual void update(int ms) override;
	void setAnimation(std::string animation);
	void updatePosition(float x , float y);
   void setCurrentFrame(int index);

	// Variables
	bool isAnimated;
	float maxSpeedX;
	float maxSpeedY;
	AnimationData curAnimation;
	std::map<std::string, AnimationData> animations;
};

