#include "Sprite.h"


Sprite::Sprite(void)
{
	initialize(0, 0, 0, 0, 0, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int width, int height)
{
	initialize(texture, 0, 0, width, height, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int x, int y, int width, int height)
{
	initialize(texture, x, y, width, height, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
{
	initialize(texture, x, y, width, height, tu, tv, tSizeX, tSizeY);
}
/*-----------------------------------------------*/
Sprite::~Sprite(void)
{
}
/*-----------------------------------------------*/
void Sprite::initialize(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
{
	/* PURPOSE:		Initalizes variables for constructor 
		RECEIVES:	texture - OpenGL texture to use for drawing
						x - Horizontal position of sprite
						y - Vertical position of sprite
						width - Width of sprite
						height - Height of sprite
						tu - Horizontal position in texture
						tv - Vertical position in texture
						tSizeX - Width of texture mapping
						tSizeY - Height of texture mapping
		RETURNS:		 
		REMARKS:		 
	*/

	this->texture = texture;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->tu = tu;
	this->tv = tv;
	this->tSizeX = tSizeX;
	this->tSizeY = tSizeY;
	posX = (float)x;
	posY = (float)y;
	this->isFlippedX = false;
	this->isFlippedY = false;
	collider = AABB(x, y, width, height);
	prevCollider = AABB(x, y, width, height);
	speedX = 0;
	speedY = 0;
	type = 0;
	prevPosX = 0;
	prevPosY = 0;
	colliderXOffset = 0;
	colliderYOffset = 0;
   isColliderDrawn = false;
}
/*-----------------------------------------------*/
void Sprite::draw(void)
{
	/* PURPOSE:		Draw object using full texture 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	glDrawSprite(texture, x, y, width, height);
}
/*-----------------------------------------------*/
void Sprite::draw(int camX, int camY)
{
	/* PURPOSE:		Draw sprite based on camera offset 
		RECEIVES:	camX - Horizontal position of camera
						camY - Vertical position of camera
		RETURNS:		 
		REMARKS:		 
	*/

	glDrawSprite(texture, x - camX, y - camY, width, height);
   
   if (isColliderDrawn)
      drawCollider(camX, camY);
}
/*-----------------------------------------------*/
void Sprite::drawUV(int camX, int camY)
{
	/* PURPOSE:		Draw sprite based on camera offset and specific uv coordinates 
		RECEIVES:	camX - Horizontal position of camera
						camY - Vertical position of camera
		RETURNS:		 
		REMARKS:		 
	*/

	GLfloat u = tu;
	GLfloat v = tv;
	GLfloat uSize = tSizeX;
	GLfloat vSize = tSizeY;

	if (isFlippedX)
	{
		u += uSize;
		uSize *= -1;
	}
	if (isFlippedY)
	{
		v += vSize;
		vSize *= -1;
	}

	glDrawSprite(texture, x - camX, y - camY, width, height, u, v, uSize, vSize);
   
   if (isColliderDrawn)
      drawCollider(camX, camY);
}
/*-----------------------------------------------*/
void Sprite::update(int ms)
{
}
/*-----------------------------------------------*/
void Sprite::setSpeed(float speedX, float speedY)
{
	/* PURPOSE:		Sets the speed of the sprite 
		RECEIVES:	speedX - Horizontal speed 
						speedY - Vertical speed
		RETURNS:		 
		REMARKS:		 
	*/

	this->speedX = speedX;
	this->speedY = speedY;
}
/*-----------------------------------------------*/
void Sprite::flipX()
{	
	/* PURPOSE:		Toggles whether sprite is facing left or right 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	isFlippedX = !isFlippedX;
}
/*-----------------------------------------------*/
void Sprite::flipY()
{	
	/* PURPOSE:		Toggles whether sprite is facing up or down
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	isFlippedY = !isFlippedY;
}
/*-----------------------------------------------*/
void Sprite::print()
{
	/* PURPOSE:		Prints x and y position of sprite 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	using namespace std;
	cout << "x = " << x << "\t y = " << y << endl;
}
/*-----------------------------------------------*/
void Sprite::drawCollider(int camX, int camY)
{
	/* PURPOSE:		Draws the collider around the sprite based on camera offset 
		RECEIVES:	camX - Horizontal position of camera
						camY - Vertical position of camera
		RETURNS:		 
		REMARKS:		 
	*/

	float myColor[] = {1,0,0,0.5};
	std::vector<float> color (myColor, myColor + sizeof(myColor) / sizeof(float));;
 	glDrawCollider(collider.x - camX, collider.y- camY, collider.w, collider.h, color);
}
/*-----------------------------------------------*/
void Sprite::setCollider(AABB *box)
{
	/* PURPOSE:		Sets up the collider of the sprite 
		RECEIVES:	box - Pointer to AABB collider box
		RETURNS:		
		REMARKS:		 
	*/

	collider = *box;
	prevCollider = AABB(box->x, box->y, box->w, box->h);
}