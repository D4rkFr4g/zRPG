#pragma once
#include <unordered_map>
#include <string>
#include <utility>

class Event
{
public:
   enum EventType
   {
      ET_COLLISION_START,
      ET_COLLISION_END,
      ET_COLLISION_PROJECTILE,
      ET_HEALTH_DOWN,
      ET_HEALTH_UP,
      ET_LEVEL_END,
      ET_LEVEL_BEGIN,
      ET_DEATH,
      ET_RESTART
   };

   // Constructors
   Event(void);
   Event(EventType et);
   Event(EventType et, std::string key, std::string value);
   Event(EventType et, std::string key, float value);
   ~Event(void);

   // Functions
   bool checkStrParam(std::string key, std::string value);
   bool checkNumParam(std::string key, float value);

   // Variables
   EventType type;
   std::unordered_map<std::string, std::string> strParams;
   std::unordered_map<std::string, float> numParams;
};