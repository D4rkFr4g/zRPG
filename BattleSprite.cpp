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
   magic = maxMagic;
   initStats(1, 1, 1, 1, 1);

   uuid = uuidManager::newUUID();
}
/*-----------------------------------------------*/
BattleSprite::~BattleSprite()
{
   if (eventQueue)
      (*eventQueue)->removeEventListener(this);
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

   int defense = 5 * stats["CON"];

   if (isCrit)
      defense *= 2;

   if (isDefending)
      defense *= 2;

   health -= (damage - defense);

   isDefending = false;
}
/*-----------------------------------------------*/
void BattleSprite::sendDamage(std::string uuid)
{
   bool isCrit = (rand() % 10) == 0;

   int damage = 10 * stats["STR"];
   if (isCrit)
      damage *= 2;

   Event ev = Event(Event::ET_DAMAGE, "subject", uuid);
   ev.strParams["damage"] = damage;
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
            applyDamage(event->numParams.find("damage")->second);
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

   this->eventQueue = &eventQueue;
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
   AnimatedSprite::update(ms);

   if (curAnimation.def.name.compare("attack") == 0 && curAnimation.timeToSendEvent())
   {
      sendDamage(targetUUID);
      targetUUID = "";
   }
}