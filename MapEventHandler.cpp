#include "MapEventHandler.h"


/*-----------------------------------------------*/
MapEventHandler::MapEventHandler()
{
}
/*-----------------------------------------------*/
MapEventHandler::~MapEventHandler()
{
}
/*-----------------------------------------------*/
void MapEventHandler::notify(Event* event)
{
   /* PURPOSE: EventListener callback function
      RECEIVES: event - Event from the eventQueue
      RETURNS:
      REMARKS:
   */

   if (event->type == Event::ET_LEVEL_LOAD)
   {
      // Check that level exists
      if (event->checkStrKey("level"))
      {

         std::unordered_map<std::string, TileLevel>::iterator itr = levels->find(event->strParams.find("level")->second);
         std::unordered_map<std::string, TileLevel>::iterator end = levels->end();

         if (itr != end)
         {

            // Save current position
            std::string name = (*currentLevel)->name;
            Vec pos;
            pos.x = player->x;
            pos.y = player->y;

            locations[name] = pos;

            // Set currentLevel
            (*currentLevel) = &levels->find(event->strParams.find("level")->second)->second;
            name = (*currentLevel)->name;

            // Load position
            if (event->checkNumKey("x") && event->checkNumKey("y"))
            {
               pos.x = (int)event->numParams.find("x")->second;
               pos.y = (int)event->numParams.find("y")->second;
            }
            else
            {
               std::unordered_map<std::string, Vec>::iterator itr = locations.find(name);
               std::unordered_map<std::string, Vec>::iterator end = locations.end();

               if (itr != end)
                  pos = itr->second;
               else
               {
                  pos.x = (*currentLevel)->startX;
                  pos.y = (*currentLevel)->startY;
               }
            }

            // Calculate player direction
            int xSpeed = 0;
            int ySpeed = 0;

            if (player->speedX > 0)
               xSpeed = 1;
            else if (player->speedX < 0)
               xSpeed = -1;

            if (player->speedY > 0)
               ySpeed = 1;
            else if (player->speedY < 0)
               ySpeed = -1;

            // Set position with a little bit extra to clear collider
            player->posX = pos.x + xSpeed;
            player->posY = pos.y + ySpeed;
         }
      }
   }
}
/*-----------------------------------------------*/
void MapEventHandler::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Map related listeners with the eventQueue
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   eventQueue->addEventListener(Event::ET_LEVEL_LOAD, this);
}
/*-----------------------------------------------*/
