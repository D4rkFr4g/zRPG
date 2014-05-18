#include "BattleSprite.h"


/*-----------------------------------------------*/
BattleSprite::BattleSprite()
{
   eventQueue = NULL;
}
/*-----------------------------------------------*/
BattleSprite::BattleSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
: AnimatedSprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
   /*Strength = damage modifier
      Constitution = hit points
      Dexterity = accuracy
      Intelligence == magic points
      Luck == Luck points*/

   srand(time(NULL));
   eventQueue = NULL;

   level = 1;
   maxHealth = 100;
   maxMagic = 10;
   health = maxHealth;
   isAlive = true;
   magic = maxMagic;
   isDefending = false;
   initStats(1, 1, 1, 1, 1);
   startX = x;
   startY = y;
   state = STATE_IDLE;
   prevState = STATE_DEFEND;
   isRemovable = false;

   uuid = uuidManager::newUUID();
}
/*-----------------------------------------------*/
BattleSprite::~BattleSprite()
{
   if (eventQueue)
      eventQueue->removeEventListener(this);
}
/*-----------------------------------------------*/
void BattleSprite::initStats(int STR, int CON, int DEX, int INT, int LCK)
{
   /* PURPOSE:    initializes Stats to given values
      RECEIVES:   STR - Strength value
      CON - Constitution value
      DEX - Dexterity value
      INT - Intelligence value
      LCK - Luck value
      RETURNS:
      REMARKS:
      */

   stats["STR"] = STR;
   stats["CON"] = CON;
   stats["DEX"] = DEX;
   stats["INT"] = INT;
   stats["LCK"] = LCK;
}
/*-----------------------------------------------*/
void BattleSprite::applyDamage(int damage)
{
   /* PURPOSE: Applies damage based on sprite stats
      RECEIVES: damage - amount of attack against sprite
      RETURNS:
      REMARKS:
      */

   bool isCrit = (rand() % 10) == 0;

   int defense = 2 * stats["CON"];

   if (isCrit)
      defense *= 2;

   if (isDefending)
      defense *= 2;

   health -= (damage - defense);
   setAnimation("Damaged");

   if (health <= 0)
   {
      isAlive = false;
      eventQueue->queueEvent(Event(Event::ET_DEATH, "subject", name));
   }

   //isDefending = false; // Good for one attack or the rest of turn?
}
/*-----------------------------------------------*/
void BattleSprite::sendDamage(std::string uuid)
{
   bool isCrit = (rand() % 10) == 0;

   int damage = 10 * stats["STR"];
   if (isCrit)
   {
      float critMultiplier = ((stats["INT"] * 5) + 5) / 100;
      damage += floor(damage * critMultiplier);
   }
   // Accuracy Check
   if (rand() % max(targetLevel - stats["ACC"], 0) == 0)
   {
      Event ev = Event(Event::ET_DAMAGE, "subject", uuid);
      ev.strParams["name"] = targetName;
      ev.numParams["damage"] = damage;
      eventQueue->queueEvent(ev);
   }
   else
   {
      eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "deflected"));
   }
}
/*-----------------------------------------------*/
void BattleSprite::notify(Event* event)
{
   /* PURPOSE: EventListener callback function
   RECEIVES: event - Event from the eventQueue
   RETURNS:
   REMARKS:
   */

   if (event->type == Event::ET_DAMAGE)
   {
      if (event->checkStrParam("subject", uuid))
      {
         if (event->checkNumKey("damage"))
         {
            applyDamage(event->numParams.find("damage")->second);
         }
      }
   }
}
/*-----------------------------------------------*/
void BattleSprite::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Map related listeners with the eventQueue
   RECEIVES:
   RETURNS:
   REMARKS:
   */

   this->eventQueue = eventQueue;
   eventQueue->addEventListener(Event::ET_DAMAGE, this);
}
/*-----------------------------------------------*/
std::string BattleSprite::getUUID()
{
   /* PURPOSE: Getter for uuid of object
      RECEIVES:
      RETURNS: string representing uuid of object
      REMARKS:
      */

   return uuid;
}
/*-----------------------------------------------*/
void BattleSprite::update(int ms)
{
   /* PURPOSE:    Updates position and animation and other event based tasks
      RECEIVES:   ms - time since last frame in milliseconds
      RETURNS:
      REMARKS:
      */

   AnimatedSprite::update(ms);

   // This should not be like this need to convert Link to it's own class.
   if (name.compare("Link") != 0)
   {
      // Determine when turn is over
      if (state != STATE_IDLE && isIdle() && state != STATE_FLEE)
         state = STATE_IDLE;

      // Move to correct yPosition
      if (state == STATE_ATTACK)
         updatePosition(x, opponentY);
      // Move back to yPosition
      else if (state == STATE_IDLE)
         updatePosition(x, startY);
   }

   // Setup timing for attack sounds
   int targetFrame = 0;
   if (name.compare("Link") == 0)
      targetFrame = 8;
   else if (name.compare("Ganon") == 0)
      targetFrame = 4;
   else
      targetFrame = 4;

   if (curAnimation.def.name.compare("Attack") == 0 &&
      curAnimation.currentFrame == targetFrame && curAnimation.elapsedTime == 0)
   {
      eventQueue->queueEvent(Event(Event::ET_ATTACK, "name", name));
   }

   if (curAnimation.def.name.compare("Attack") == 0 && curAnimation.timeToSendEvent() &&
      curAnimation.elapsedTime == 0)
   {
      sendDamage(targetUUID);
   }

   //Reapply Defend animation if attacked
   if (isDefending && curAnimation.def.name.compare("Defend") != 0 && curAnimation.isFinished)
      setAnimation("Defend");

   checkRemovable();
}
/*-----------------------------------------------*/
void BattleSprite::AI()
{

}
/*-----------------------------------------------*/
void BattleSprite::takeTurn()
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

         // Determine next state
         AI();
      }
      // Attack State
      if (state == STATE_ATTACK)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;

            setAnimation("Attack");
         }
      }
      // Item State
      else if (state == STATE_ITEMS)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         health += (int)floor(maxHealth * healFactor);
         setAnimation("Heal");
      }
      // Flee State
      else if (state == STATE_FLEE)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;

            isFlippedX = true;
            speedX = maxSpeed;
            updatePosition(width, y);
         }

         setAnimation("Flee");
      }
      // Defend State
      else if (state == STATE_DEFEND)
      {
         // Handle State Transition
         if (state != prevState)
         {
            prevState = state;
         }

         setAnimation("Defend");
      }
   }
}
/*-----------------------------------------------*/
void BattleSprite::checkRemovable()
{
   if (!isAlive && curAnimation.isFinished)
      isRemovable = true;
}
/*-----------------------------------------------*/
void BattleSprite::getNewUUID()
{
   /* PURPOSE:    requests for new UUID
      RECEIVES:
      RETURNS:    string representing uuid of object
      REMARKS:    Used when copying the object
      */

   uuid = uuidManager::newUUID();
}
/*-----------------------------------------------*/
bool BattleSprite::operator==(BattleSprite other)
{
   if (this->uuid == other.uuid)
      return true;
   else
      return false;

}
/*-----------------------------------------------*/
bool BattleSprite::isIdle()
{
   return curAnimation.isFinished;
}
/*-----------------------------------------------*/
BattleSprite* BattleSprite::clone() const
{
   return new BattleSprite(*this);
}
