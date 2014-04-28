#pragma once
#include "AnimatedSprite.h"

class PlayerSprite :
	public AnimatedSprite
{
public:
	PlayerSprite(void);
	PlayerSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY, int health);
	~PlayerSprite(void);

	// Functions

	// Variables
	bool isAlive;
	int health;
	int score;
	int state;
	int prevState;
	int jumpTicks;
	int jumpTicksRemaining;
	float jumpSpeed;
	bool isJumping;
};

