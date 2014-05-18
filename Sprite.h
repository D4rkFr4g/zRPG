#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "DrawUtils.h"
#include "AABB.h"

class Sprite
{
public:
	// Constructors
	Sprite();
	Sprite(GLuint* texture, int width, int height);
	Sprite(GLuint* texture, int x, int y, int width, int height);
	Sprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
   Sprite(GLuint* texture, int x, int y, int offsetX, int offsetY, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
	virtual ~Sprite(void);

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
   std::string name;
	int width, height;
	int x, y;
   int offsetX, offsetY;
	int colliderXOffset, colliderYOffset;
	GLfloat tu, tv;
	GLfloat tSizeX, tSizeY;
	float speedX, speedY;
   float maxSpeed;
	float posX, posY;
	bool isFlippedX;
	bool isFlippedY;
	AABB collider;
	AABB prevCollider;
   bool hasCollided;
	float prevPosX, prevPosY;
	int type;
   bool isColliderDrawn;

private:
	void initialize(GLuint* texture, int x, int y, int offsetX, int offsetY, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
};

