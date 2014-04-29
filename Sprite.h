#pragma once
#include <GL/glew.h>
#include <iostream>
#include "DrawUtils.h"
#include "AABB.h"

class Sprite
{
public:
	// Constructors
	Sprite(void);
	Sprite(GLuint* texture, int width, int height);
	Sprite(GLuint* texture, int x, int y, int width, int height);
	Sprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
	~Sprite(void);

	//Functions
	void draw(void);
	void draw(int camX, int camY);
	void drawUV(int camX, int camY);
	virtual void update(int ms);
	virtual void setSpeed(float speedX, float speedY);
	void flipX();
	void flipY();
	void print();
	void drawCollider(int camX, int camY);
	void setCollider(AABB *box);

	// Variables
	GLuint* texture;
	int width, height;
	int x, y;
	int colliderXOffset, colliderYOffset;
	GLfloat tu, tv;
	GLfloat tSizeX, tSizeY;
	float speedX, speedY;
	float posX, posY;
	bool isFlippedX;
	bool isFlippedY;
	AABB collider;
	AABB prevCollider;
	float prevPosX, prevPosY;
	int type;
   bool isColliderDrawn;

private:
	void initialize(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
};

