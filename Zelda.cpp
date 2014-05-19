#include "Zelda.h"


Zelda::Zelda()
{
	Texture* tex = textureLoader::getTexture("friendly_npcs");
	AnimatedSprite sprite = AnimatedSprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0 * tex->uSize, 4 * tex->vSize, 1 * tex->uSize, 1 * tex->vSize);
	*this = Zelda((Zelda&)sprite);
	type = 1;
	name = "Zelda";
	isAnimated = false;

	//Setup Collider
	int xOffset = 18;
	int yOffset = 10;
	int width = 28;
	int height = 45;
	float uSize = 1;
	float vSize = 1;
	colliderXOffset = xOffset;
	colliderYOffset = yOffset;
	setCollider(&AABB(x + xOffset, y + yOffset, width, height));
	maxSpeed = 50;
	isColliderDrawn = false;

	// Walking Animation
	int numFrames = 1;
	int timeToNextFrame = 300;
	std::vector<AnimationFrame> frames;
	frames.assign(numFrames, AnimationFrame());

	frames[0] = AnimationFrame(0, 4, uSize, vSize);
	//frames[1] = AnimationFrame(1, 0, uSize, vSize);
	Animation animation_walking = Animation("Walking", frames, numFrames);
	animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

	// Idle Animation
	numFrames = 1;
	frames.clear();
	frames.assign(numFrames, AnimationFrame());

	frames[0] = AnimationFrame(0, 4, uSize, vSize);
	Animation animation_idle = Animation("Idle", frames, numFrames);
	animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

	//setAnimation("Walking");
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
	Event ev = Event(Event::ET_COLLISION_START, "dialog", "villager_secret");
	eventQueue->queueEvent(ev);
}
/*-----------------------------------------------*/