#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void) : Sprite()
{
}
/*-----------------------------------------------*/
AnimatedSprite::AnimatedSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
	: Sprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	this->curAnimation = AnimationData();
	this->isAnimated = true;
	this->maxSpeedX = 0;
	this->maxSpeedY = 0;
}
/*-----------------------------------------------*/
AnimatedSprite::~AnimatedSprite(void)
{
}
/*-----------------------------------------------*/
void AnimatedSprite::update(int ms)
{
	/* PURPOSE:		Updates sprite based on elapsed time and current speeds 
		RECEIVES:	ms - milliseconds since last frame 
		RETURNS:		 
		REMARKS:		 
	*/

	// Store previous position information
	prevPosX = posX;
	prevPosY = posY;

	// Update Position
   float time = (float)ms / 1000;
	float deltaX = time * speedX;
	float deltaY = time * speedY;
	posX += deltaX;
	posY += deltaY;
	x = (int) floor(posX);
	y = (int) floor(posY); // Bottom left coord adjustment
	
	// Update Animation
	curAnimation.updateTime(ms);
	int currentFrame = curAnimation.currentFrame;
   if (isAnimated)
      setCurrentFrame(currentFrame);

	// Update Colliders
	prevCollider.x = collider.x;
	prevCollider.y = collider.y;
	collider.x = this->x + colliderXOffset;
	collider.y = this->y + colliderYOffset;
}
/*-----------------------------------------------*/
void AnimatedSprite::setAnimation(std::string animation)
{
	/* PURPOSE:		Sets the current animation of the sprite 
		RECEIVES:	animation - String name of animation 
		RETURNS:		 
		REMARKS:		string must be in map or an error will be thrown 
						 
	*/

	curAnimation = animations[animation];
	tu = curAnimation.def.frames[0].tu;
	tv = curAnimation.def.frames[0].tv;
	tSizeX = curAnimation.def.frames[0].tWidth;
	tSizeY = curAnimation.def.frames[0].tHeight;
   curAnimation.isFinished = false;
}
/*-----------------------------------------------*/
void AnimatedSprite::setCurrentFrame(int index)
{
   /* PURPOSE:		Sets the animations current frame to the specified frame
      RECEIVES:	index - the frame number to be set
      RETURNS:
      REMARKS:
   */

   AnimationFrame frame = curAnimation.def.frames[index];

   tu = frame.tu;
   tv = frame.tv;
   tSizeX = frame.tWidth;
   tSizeY = frame.tHeight;
}
/*-----------------------------------------------*/