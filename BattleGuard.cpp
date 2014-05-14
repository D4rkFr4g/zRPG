#include "BattleGuard.h"


/*-----------------------------------------------*/
BattleGuard::BattleGuard()
{
   Texture* tex = textureLoader::getTexture("guard_battle");
   BattleSprite enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   *this = BattleGuard((BattleGuard&)enemy);
   isAnimated = false; // TODO Remove once animations are setup
   name = "guard";
   level = 5;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;
   std::vector<AnimationFrame> frames;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   // Idle Animation
   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Idle", frames, numFrames);
   animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   // Attack Animation
   numFrames = 20;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   //frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   //animData.eventFrame = 13;
   animations[animation.name] = animData;

   setAnimation("Idle");
}
/*-----------------------------------------------*/
BattleGuard::~BattleGuard()
{
}
/*-----------------------------------------------*/
void BattleGuard::AI()
{

}
/*-----------------------------------------------*/
void BattleGuard::update(int ms)
{
   BattleSprite::update(ms);
   AI();
}
/*-----------------------------------------------*/
