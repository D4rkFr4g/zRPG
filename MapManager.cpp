#include "MapManager.h"

std::unordered_map<std::string, TileLevel>* MapManager::levels;
Camera* MapManager::camera;
int* MapManager::windowWidth;
int* MapManager::windowHeight;
int* MapManager::windowMaxWidth;
int* MapManager::windowMaxHeight;
EventQueue* MapManager::eventQueue;
/*-----------------------------------------------*/
MapManager::MapManager()
{
}
/*-----------------------------------------------*/
MapManager::~MapManager()
{
}
/*-----------------------------------------------*/
void MapManager::notify(Event* event)
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
            // Save all sprites
            spriteManager::saveLevelSprites(name);

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
                  
                  int colliderNegativeYOffset = player->colliderYOffset + player->collider.h;
                  pos.y = (*currentLevel)->startY - colliderNegativeYOffset;
               }
            }

            // Set new map size
            *windowMaxWidth = ((*currentLevel)->width * (*currentLevel)->tilesWidth);
            *windowMaxHeight = ((*currentLevel)->height * (*currentLevel)->tilesHeight);

            // Calculate player direction
            int xSpeed = 0;
            int ySpeed = 0;

            if (player->speedX > 0)
               xSpeed = 3;
            else if (player->speedX < 0)
               xSpeed = -3;
            if (player->speedY > 0)
               ySpeed = 3;
            else if (player->speedY < 0)
               ySpeed = -3;

            // Set position with a little bit extra to clear collider
            player->updatePosition(pos.x + xSpeed, pos.y + ySpeed);

            // Load sprites for the level
            bucketManager::updateBucketSize();
            spriteManager::loadLevelSprites(name);

            // Update camera for new level
            camera->maxX = *windowMaxWidth - *windowWidth;
            camera->maxY = *windowMaxHeight - *windowHeight;
         }
      }
   }

   if (event->type == Event::ET_LEVEL_MUSIC && !event->checkStrKey("level"))
   {
      // Listen for messages to load music from Objects that don't know what level it is.
      eventQueue->queueEvent(Event(Event::ET_LEVEL_MUSIC, "level", (*currentLevel)->name));
   }

   if (event->type == Event::ET_RESTART)
   {
      std::string name = (*currentLevel)->name;
      
      Vec pos;
      pos.x = player->x;
      pos.y = player->y;

      // Save all sprites
      spriteManager::saveLevelSprites(name);

      // Set currentLevel
      (*currentLevel) = &levels->find("overworld")->second;
      name = (*currentLevel)->name;

      pos.x = (*currentLevel)->startX;

      int colliderNegativeYOffset = player->colliderYOffset + player->collider.h;
      pos.y = (*currentLevel)->startY - colliderNegativeYOffset;
         
      // Set new map size
      *windowMaxWidth = ((*currentLevel)->width * (*currentLevel)->tilesWidth);
      *windowMaxHeight = ((*currentLevel)->height * (*currentLevel)->tilesHeight);

      // Set position with a little bit extra to clear collider
      player->updatePosition(pos.x, pos.y);

      // Load sprites for the level
      bucketManager::updateBucketSize();
      spriteManager::loadLevelSprites(name);

      // Update camera for new level
      camera->maxX = *windowMaxWidth - *windowWidth;
      camera->maxY = *windowMaxHeight - *windowHeight;

      eventQueue->queueEvent(Event(Event::ET_LEVEL_MUSIC, "level", (*currentLevel)->name));
   }
}
/*-----------------------------------------------*/
void MapManager::registerListeners(EventQueue* eventQueue)
{
   /* PURPOSE: Registers all relevant Map related listeners with the eventQueue
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   eventQueue->addEventListener(Event::ET_LEVEL_LOAD, this);
   eventQueue->addEventListener(Event::ET_LEVEL_MUSIC, this);
   eventQueue->addEventListener(Event::ET_RESTART, this);

}
/*-----------------------------------------------*/
std::vector<Sprite*> MapManager::getCollidableTileType(std::string levelName, int tileType)
{
   std::vector<Sprite*> tiles;
   std::unordered_map<std::string, TileLevel>::iterator itr = levels->find(levelName);
   std::unordered_map<std::string, TileLevel>::iterator end = levels->end();

   if (itr != end)
   {
      TileLevel* level = &levels->find(levelName)->second;
      for (int i = 0; i < (int)level->collidableTiles.size(); i++)
      {
         int index = level->collidableTiles[i];
         Sprite* tile = &level->tileArray[index];
         int type = tile->type;
         if (type == tileType)
         {
            tiles.push_back(tile);
         }
      }
   }
   else
      tiles.assign(1, &Sprite());

   return tiles;
}
/*-----------------------------------------------*/