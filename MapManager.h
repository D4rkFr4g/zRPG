#pragma once
#include <string>
#include <unordered_map>
#include "EventListener.h"
#include "EventQueue.h"
#include "TileLevel.h"
#include "PlayerSprite.h"
#include "spriteManager.h"

class MapManager : public EventListener
{
protected:

private:
   struct Vec
   {
      int x;
      int y;
   };

   std::unordered_map<std::string, Vec> locations;

public:
   MapManager();
   ~MapManager();

   // Functions
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);
   static std::vector<Sprite*> getCollidableTileType(std::string levelName, int tileType);

   // Variables
   PlayerSprite* player;
   TileLevel** currentLevel;
   static std::unordered_map<std::string, TileLevel>* levels;
   static Camera* camera;
   static int* windowWidth;
   static int* windowHeight;
   static EventQueue* eventQueue;
};

