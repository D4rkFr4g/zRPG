#pragma once
#include <unordered_map>
#include "BattleSprite.h"
#include "Texture.h"
#include "BattleChicken.h"


class enemyManager
{
protected:
   enemyManager();

public:
   // Constructors
   ~enemyManager();

   // Enum
   enum BATTLE_TYPE { BATTLE_EASY = 6, BATTLE_MEDIUM, BATTLE_HARD, BATTLE_BOSS };

   // Functions
   static void init(std::unordered_map<std::string, Texture>* textures, std::unordered_map<int, std::vector<BattleSprite*>>* enemies);
   static void updateEnemy(BattleSprite* enemy);
   static void initChickens();
   static void initGuards();
   static void initKnights();
   static void initGanon();

   // Variables
   static std::unordered_map<std::string, Texture>* textures;
   static std::unordered_map<int, std::vector<BattleSprite*>>* enemies;
};

