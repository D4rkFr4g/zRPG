#pragma once
#include <string>
#include <unordered_map>
#include "EventListener.h"
#include "EventQueue.h"
#include "TileLevel.h"
#include "PlayerSprite.h"

class MapEventHandler : public EventListener
{
protected:

private:

public:
   MapEventHandler();
   ~MapEventHandler();

   struct Vec
   {
      int x;
      int y;
   };

   // Functions
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);

   // Variables
   PlayerSprite* player;
   TileLevel** currentLevel;
   std::unordered_map<std::string, TileLevel>* levels;
   std::unordered_map<std::string, Vec> locations;
};

