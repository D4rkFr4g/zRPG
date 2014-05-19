#include "PlayerSprite.h"


PlayerSprite::PlayerSprite(void) : AnimatedSprite()
{
}
/*-----------------------------------------------*/
PlayerSprite::PlayerSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY, int health)
	: AnimatedSprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	isAlive = true;
	this->health = health;
	score = 0;
	state = 0;
	prevState = -1;
	jumpTicks = 0;
	jumpTicksRemaining = 0;
	jumpSpeed = 0;
	isJumping = false;
   hasSword = false;
   isGanonDefeated = false;
   startX = x;
   startY = y;
   level = 1;
}
/*-----------------------------------------------*/
PlayerSprite::~PlayerSprite(void)
{
}
/*-----------------------------------------------*/
void PlayerSprite::initStats(int STR, int CON, int DEX, int INT, int LCK)
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
void PlayerSprite::updateCamera()
{
   /* PURPOSE:    Moves camera to current position of the player.
      RECEIVES:   
      RETURNS:
      REMARKS:
   */

   cam->follow(x, y, width, height);
}
/*-----------------------------------------------*/
void PlayerSprite::notify(Event* event)
{
   /* PURPOSE: EventListener callback function
   RECEIVES: event - Event from the eventQueue
   RETURNS:
   REMARKS:
   */

   if (event->type == Event::ET_ITEM)
   {
      if (event->checkStrKey("name"))
      {
         std::string name = event->strParams.find("name")->second;
         
         if (name.compare("sword") == 0)
            hasSword = true;
         else
         {
            int qty = 1;

            if (event->checkNumKey("qty"))
               qty = event->numParams.find("qty")->second;

            std::unordered_map<std::string, int>::iterator itr = items.find(name);
            std::unordered_map<std::string, int>::iterator end = items.end();

            // If it doesn't exist already add it.
            if (itr == end)
               items[name] = 0;

            items.find(name)->second += qty;
         }
      }
   }
}
/*-----------------------------------------------*/
void PlayerSprite::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Map related listeners with the eventQueue
   RECEIVES:
   RETURNS:
   REMARKS:
   */

   eventQueue->addEventListener(Event::ET_ITEM, this);
}
/*-----------------------------------------------*/