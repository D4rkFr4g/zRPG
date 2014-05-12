#pragma once
#include <unordered_map>
#include <string>
#include <random>
#include <time.h>
#include "AnimatedSprite.h"
#include "EventListener.h"
#include "EventQueue.h"
#include "uuidManager.h"


class BattleSprite :
   public AnimatedSprite, public EventListener
{
private:
   //Functions
   void applyDamage(int damage);
   void sendDamage(std::string uuid);

   // Variables
   std::string uuid;
   EventQueue** eventQueue;

public:
   // Constructors
   BattleSprite();
   BattleSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
   virtual ~BattleSprite();
   virtual void update(int ms) override;
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);
   std::string getUUID();
   bool operator==(BattleSprite rhs);
   
   // Functions
   void initStats(int STR, int CON, int DEX, int INT, int LCK);

   // Variables
   std::unordered_map<std::string, int> items;
   std::unordered_map<std::string, int> stats;
   int level;
   int xp;
   int health;
   int maxHealth;
   int magic;
   int maxMagic;
   std::string targetUUID;
   bool isDefending;
};

