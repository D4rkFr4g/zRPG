#include "Zelda.h"


Zelda::Zelda()
{
	Texture* tex = textureLoader::getTexture("zelda");
	AnimatedSprite sprite = AnimatedSprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0 * tex->uSize, 0 * tex->vSize, tex->uSize, tex->vSize);
	*this = Zelda((Zelda&)sprite);
	type = 14;
	name = "Zelda";
	isAnimated = false;

	//Setup Collider
	int xOffset = 0;
	int yOffset = 10;
	int width = 64;
	int height = 45;
	float uSize = tex->uSize;
	float vSize = tex->vSize;
	colliderXOffset = xOffset;
	colliderYOffset = yOffset;
	setCollider(&AABB(x + xOffset, y + yOffset, width, height));
	maxSpeed = 50;
	isColliderDrawn = false;

	// Laying down  Animation
	int numFrames = 1;
	int timeToNextFrame = 300;
	std::vector<AnimationFrame> frames;
	frames.assign(numFrames, AnimationFrame());

	frames[0] = AnimationFrame(0 * uSize, 0 * vSize, uSize, vSize);
	Animation animation_walking = Animation("Sleeping", frames, numFrames);
	animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

	// Standing Idle Animation
	numFrames = 1;
	frames.clear();
	frames.assign(numFrames, AnimationFrame());

	frames[0] = AnimationFrame(1 * uSize, 0 * vSize, uSize, vSize);
	Animation animation_idle = Animation("Idle", frames, numFrames);
	animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

	setAnimation("Idle");
}
/*-----------------------------------------------*/
Zelda::~Zelda()
{
}
/*-----------------------------------------------*/
void Zelda::update(int ms)
{
	/* PURPOSE:		Control character movements based on probabilities
	RECEIVES:	diff_time - milliseconds since last frame
	RETURNS:
	REMARKS:
	*/

	AnimatedSprite::update(ms);
	//AI();
}
/*-----------------------------------------------*/

void Zelda::AI()
{
	/* PURPOSE:		Modifies object based on artificial intelligence
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	float speedX = this->speedX;
	float speedY = this->speedY;

	// If stopped Restart Character Maybe
	if (speedX == 0 && speedY == 0)
	{
		int willRestart = rand() % 100;
		if (willRestart == 0)
		{
			// Set speed and animation
			speedX = randomSpeed();
			speedY = randomSpeed();
			setAnimation("Walking");

			updateDirection(speedX, speedY);
		}
	}
	else
	{
		// Randomly stop characters
		int willStop = rand() % 250;
		if (willStop == 0)
		{
			speedX = 0;
			speedY = 0;
			setAnimation("Idle");
		}
	}

	setSpeed(speedX, speedY);
}
/*-----------------------------------------------*/
float Zelda::randomSpeed()
{
	/* PURPOSE:		returns a random speed the character can move
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	int speed = rand() % 2;
	int negation = rand() % 2;
	if (negation)
		speed *= -1;
	return (float)speed * maxSpeed;
}
/*-----------------------------------------------*/
void Zelda::setRandomMovement()
{
	/* PURPOSE:		Sets a random speed for both x and y directions
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	setSpeed(randomSpeed(), randomSpeed());
}
/*-----------------------------------------------*/
void Zelda::updateDirection(float speedX, float speedY)
{
	/* PURPOSE:		Turns character so it faces the correct direction
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	if (speedX < 0)
		isFlippedX = true;
	else if (speedX > 0)
		isFlippedX = false;
}
/*-----------------------------------------------*/
void Zelda::onTrigger()
{
}
/*-----------------------------------------------*/
void Zelda::onCollision()
{
   setAnimation("Idle");
}
/*-----------------------------------------------*/