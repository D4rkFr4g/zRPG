#include "BattleKnight.h"


/*-----------------------------------------------*/
BattleKnight::BattleKnight()
{
   Texture* tex = textureLoader::getTexture("knight_battle");
   BattleSprite enemy = BattleSprite(&tex->texture, 0, 100, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   *this = BattleKnight((BattleKnight&)enemy);
   //isAnimated = false; //TODO Remove once animations are setup
   name = "knight";
   level = 10;
   maxSpeed = 100;
   healFactor = 0.15;
   health = 200;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;

   // Idle Animation
   std::vector<AnimationFrame> frames;
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
   frames[3] = frames[0];
   frames[4] = frames[1];
   frames[5] = frames[2];
   frames[6] = frames[0];
   frames[7] = frames[1];
   frames[8] = frames[2];
   frames[9] = frames[0];
   frames[10] = frames[1];
   frames[11] = frames[2];
   frames[12] = frames[0];
   animation = Animation("Damaged", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animations[animation.name] = animData;

   // Flee Animation
   numFrames = 1;
   timeToNextFrame = 1000;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Flee", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animations[animation.name] = animData;

   // Death Animation
   numFrames = 1;
   timeToNextFrame = 1000;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 16 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Death", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animations[animation.name] = animData;

   setAnimation("Idle");
}
/*-----------------------------------------------*/
BattleKnight::~BattleKnight()
{
	if (eventQueue)
		eventQueue->removeEventListener(this);
}
/*-----------------------------------------------*/
void BattleKnight::AI()
{
   float alpha = (float)health / maxHealth;
   bool isCriticalHealth = alpha < 0.2;

   int chance = rand() % 100;

   // Flee
   if (rand() % 10 == 0 && isCriticalHealth)
      state = STATE_FLEE;
   // Attack
   else if (chance < 90)
      state = STATE_ATTACK;
   // Defend
   else if (chance >= 90)
      state = STATE_DEFEND;
}
/*-----------------------------------------------*/
void BattleKnight::update(int ms)
{
   BattleSprite::update(ms);
}
/*-----------------------------------------------*/
//void BattleKnight::takeTurn()
//{
//   if (isAlive)
//   {
//      // Battle States
//      // Idle State
//      if (state == STATE_IDLE)
//      {
//         // Handle State Transition
//         if (state != prevState)
//         {
//            prevState = state;
//
//            isDefending = false;
//         }
//
//         // Determine next state
//         AI();
//      }
//      // Attack State
//      if (state == STATE_ATTACK)
//      {
//         // Handle State Transition
//         if (state != prevState)
//         {
//            prevState = state;
//
//            setAnimation("Attack");
//         }
//      }
//      // Item State
//      else if (state == STATE_ITEMS)
//      {
//         // Handle State Transition
//         if (state != prevState)
//         {
//            prevState = state;
//         }
//
//         health += (int)floor(maxHealth * 0.15);
//         setAnimation("Heal");
//      }
//      // Flee State
//      else if (state == STATE_FLEE)
//      {
//         // Handle State Transition
//         if (state != prevState)
//         {
//            prevState = state;
//
//            isFlippedX = true;
//            speedX = maxSpeed;
//            updatePosition(width, y);
//         }
//
//         setAnimation("Flee");
//      }
//      // Defend State
//      else if (state == STATE_DEFEND)
//      {
//         // Handle State Transition
//         if (state != prevState)
//         {
//            prevState = state;
//         }
//
//         setAnimation("Defend");
//      }
//   }
//}
/*-----------------------------------------------*/
BattleKnight* BattleKnight::clone() const
{
   return new BattleKnight(*this);
}
/*-----------------------------------------------*/