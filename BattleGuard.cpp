#include "BattleGuard.h"


/*-----------------------------------------------*/
BattleGuard::BattleGuard()
{
   Texture* tex = textureLoader::getTexture("guard_battle");
   BattleSprite enemy = BattleSprite(&tex->texture, 0, 100, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   *this = BattleGuard((BattleGuard&)enemy);
   isAnimated = false; // TODO Remove once animations are setup
   name = "guard";
   level = 5;
   maxSpeed = 10;

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
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Idle", frames, numFrames);
   animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   // Attack Animation
   numFrames = 12;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   frames[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(0 * uSize, 10 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(0 * uSize, 9 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(0 * uSize, 8 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(0 * uSize, 7 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(0 * uSize, 6 * vSize, 1 * uSize, 1 * vSize);
   frames[6] = AnimationFrame(0 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[7] = AnimationFrame(0 * uSize, 4 * vSize, 1 * uSize, 1 * vSize);
   frames[8] = AnimationFrame(0 * uSize, 3 * vSize, 1 * uSize, 1 * vSize);
   frames[9] = AnimationFrame(0 * uSize, 2 * vSize, 1 * uSize, 1 * vSize);
   frames[10] = AnimationFrame(0 * uSize, 1 * vSize, 1 * uSize, 1 * vSize);
   frames[11] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 7;
   animations[animation.name] = animData;

   // Damaged Animation
   numFrames = 13;
   timeToNextFrame = 30;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(0 * uSize, 12 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(0 * uSize, 13 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(0 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = frames[0];
   frames[5] = frames[1];
   frames[6] = frames[2];
   frames[7] = frames[3];
   frames[8] = frames[0];
   frames[9] = frames[1];
   frames[10] = frames[2];
   frames[11] = frames[3];
   frames[12] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Damaged", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animations[animation.name] = animData;

   // Flee Animation
   numFrames = 5;
   timeToNextFrame = 1000;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Flee", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
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
   if (isAlive)
   {
      // Battle States
      // Idle State
      if (state == STATE_IDLE)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;

            isDefending = false;
         }

         // Check for new Transition
         if (0)
            state = STATE_PLAYER;
      }
      // Attack Player State
      if (state == STATE_PLAYER)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         // Check for new Transition
         if (0)
            state = STATE_PLAYER;
      }
      // Item State
      else if (state == STATE_ITEMS)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         // Check for new Transition
         if (0)
            state = STATE_PLAYER;
      }
      // Flee State
      else if (state == STATE_FLEE)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         // Check for new Transition
         if (0)
            state = STATE_PLAYER;
      }
      // Defend State
      else if (state == STATE_DEFEND)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         // Check for new Transition
         if (0)
            state = STATE_PLAYER;
      }
   }
}
/*-----------------------------------------------*/
void BattleGuard::update(int ms)
{
   BattleSprite::update(ms);
}
/*-----------------------------------------------*/
void BattleGuard::takeTurn()
{
   AI();
}
/*-----------------------------------------------*/
BattleGuard* BattleGuard::clone() const
{
   return new BattleGuard(*this);
}
/*-----------------------------------------------*/