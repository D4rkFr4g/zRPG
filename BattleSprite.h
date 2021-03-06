#pragma once
#include <unordered_map>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "AnimatedSprite.h"
#include "EventListener.h"
#include "EventQueue.h"
#include "uuidManager.h"
#include "textureLoader.h"
#include "IClonable.h"


class BattleSprite :
   public AnimatedSprite, public EventListener, public IClonable
{
protected:
   EventQueue* eventQueue;

private:
   //Functions
   void applyDamage(int damage);
   void sendDamage(std::string uuid);
   void checkRemovable();

   // Variables
   std::string uuid;

public:
   // Constructors
   BattleSprite();
   BattleSprite(GLuint* texture, int x, int y, int texWidth, int texHeight, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
   
   // Enums
   enum BATTLE_STATE { STATE_IDLE, STATE_PLAYER, STATE_ACTION, STATE_ENEMY, STATE_ITEMS, STATE_FLEE, STATE_DEFEND, STATE_ATTACK };

   // Virtual Functions
   virtual ~BattleSprite();
   virtual void update(int ms) override;
   virtual void notify(Event* event) override;
   virtual void takeTurn();
   virtual void AI();
   virtual BattleSprite* clone() const override;

   //Functions
   void registerListeners(EventQueue* eventQueue);
   std::string getUUID();
   bool operator==(BattleSprite rhs);
   void getNewUUID();
   void initStats(int STR, int CON, int DEX, int INT, int LCK);
   bool isIdle();

   // Variables
   std::unordered_map<std::string, int> items;
   std::unordered_map<std::string, int> stats;
   int level;
   int xp;
   int health;
   int maxHealth;
   float healFactor;
   int magic;
   int maxMagic;
   int startX;
   int startY;
   int opponentY;
   std::string targetUUID;
   int targetLevel;
   std::string targetName;
   bool isDefending;
   bool isAlive;
   bool isRemovable;
   BATTLE_STATE state;
   BATTLE_STATE prevState;
};

