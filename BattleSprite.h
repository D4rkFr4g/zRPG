#pragma once
#include <unordered_map>
#include <string>
#include "AnimatedSprite.h"


class BattleSprite :
   public AnimatedSprite
{
public:
   // Constructors
   BattleSprite();
   BattleSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
   virtual ~BattleSprite();

   // Functions
   void initStats(int STR, int CON, int DEX, int INT, int LCK);

   // Variables
   std::unordered_map<std::string, int> items;
   std::unordered_map<std::string, int> stats;
   std::vector<int> xpToNextLevel;
   int level;
   int xp;
   int health;
   int maxHealth;
};

