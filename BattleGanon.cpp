#include "BattleGanon.h"


/*-----------------------------------------------*/
BattleGanon::BattleGanon()
{
   Texture* tex = textureLoader::getTexture("ganon_battle");
   BattleSprite enemy = BattleSprite(&tex->texture, 0, 100, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   *this = BattleGanon((BattleGanon&)enemy);
   isAnimated = false; //TODO Remove once animations are setup
   name = "Ganon";
   level = 11;
   maxSpeed = 0;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;
   std::vector<AnimationFrame> frames;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   //// Idle Animation
   //frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
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

   // Flee Animation
   numFrames = 5;
   timeToNextFrame = 1000;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Flee", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animations[animation.name] = animData;

   //setAnimation("Idle");
}
/*-----------------------------------------------*/
BattleGanon::~BattleGanon()
{
}
/*-----------------------------------------------*/
void BattleGanon::AI()
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
void BattleGanon::update(int ms)
{
   BattleSprite::update(ms);
}
/*-----------------------------------------------*/
void BattleGanon::takeTurn()
{
   AI();
}
/*-----------------------------------------------*/
BattleGanon* BattleGanon::clone() const
{
   return new BattleGanon(*this);
}
/*-----------------------------------------------*/