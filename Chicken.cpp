#include "Chicken.h"


Chicken::Chicken()
{
   Texture* tex = textureLoader::getTexture("cucco");
   AnimatedSprite sprite = AnimatedSprite(&tex->texture, 0, 0, tex->width, tex->height, 0, 0, 0.5, 1);
   *this = Chicken((Chicken&)sprite);
   type = 1;
   name = "cucco";

   //Setup Collider
   int xOffset = 20;
   int yOffset = 25;
   int width = 20;
   int height = 20;
   float uSize = 0.5;
   float vSize = 1;
   colliderXOffset = xOffset;
   colliderYOffset = yOffset;
   setCollider(&AABB(x + xOffset, y + yOffset, width, height));
   maxSpeed = 50;

   // Walking Animation
   int numFrames = 2;
   int timeToNextFrame = 300;
   std::vector<AnimationFrame> frames;
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0, 0, uSize, vSize);
   frames[1] = AnimationFrame(0.5, 0, uSize, vSize);
   Animation animation_walking = Animation("Walking", frames, numFrames);
   animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

   // Idle Animation
   numFrames = 1;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   
   frames[0] = AnimationFrame(0, 0, uSize, vSize);
   Animation animation_idle = Animation("Idle", frames, numFrames);
   animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);
   
   setAnimation("Walking");
}
/*-----------------------------------------------*/
Chicken::~Chicken()
{
}
/*-----------------------------------------------*/
void Chicken::update(int ms)
{
   /* PURPOSE:		Control chicken movements based on probabilities
      RECEIVES:	diff_time - milliseconds since last frame
      RETURNS:
      REMARKS:
   */

   AnimatedSprite::update(ms);
   AI();
}
/*-----------------------------------------------*/
void Chicken::AI()
{
   /* PURPOSE:		Modifies object based on artificial intelligence
      RECEIVES:	
      RETURNS:
      REMARKS:
   */

   float speedX = this->speedX;
   float speedY = this->speedY;

   // If stopped Restart Chicken Maybe
   if (speedX == 0 && speedY == 0)
   {
      int willRestart = rand() % 100;
      if (willRestart == 0)
      {
         // Set speed and animation
         speedX = randomSpeed();
         speedY = randomSpeed();
         setAnimation("Walking");
      }
   }
   else
   {
      // Randomly stop chickens
      int willStop = rand() % 250;
      if (willStop == 0)
      {
         speedX = 0;
         speedY = 0;
         setAnimation("Idle");
      }
   }

   setSpeed(speedX, speedY);
   updateDirection();
}
/*-----------------------------------------------*/
float Chicken::randomSpeed()
{
   /* PURPOSE:		returns a random speed the chicken can move
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
void Chicken::setRandomMovement()
{
   /* PURPOSE:		Sets a random speed for both x and y directions
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   setSpeed(randomSpeed(), randomSpeed());
   updateDirection();
}
/*-----------------------------------------------*/
void Chicken::updateDirection()
{
   /* PURPOSE:		Turns chicken so it faces the correct direction
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
void Chicken::onTrigger()
{
   eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "cucco"));
}
/*-----------------------------------------------*/