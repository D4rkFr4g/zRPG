#include "enemyManager.h"


/*-----------------------------------------------*/
enemyManager::enemyManager()
{
}
/*-----------------------------------------------*/
enemyManager::~enemyManager()
{
}
/*-----------------------------------------------*/
void enemyManager::init(std::unordered_map<std::string, Texture>* textures, std::unordered_map<int, std::vector<BattleSprite>>* enemies)
{
   // Initialize all enemies

   // Load all enemies into map by type
   Texture* tex = &(*textures)["chicken"];
   BattleSprite enemy = BattleSprite(&tex->texture, 500,100,tex->width, tex->height,0,0, 0.5, 1);
   enemy.isAnimated = false; // TODO Remove once animations are setup
   enemy.isFlippedX = true;
   
   // Create enemy stats
   enemy.initStats(1, 1, 1, 1, 1);
   
   (*enemies)[BATTLE_EASY].push_back(enemy);
   enemy.level = 5;
   (*enemies)[BATTLE_MEDIUM].push_back(enemy);
   enemy.level = 10;
   (*enemies)[BATTLE_HARD].push_back(enemy);
   enemy.level = 11;
   (*enemies)[BATTLE_BOSS].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::updateEnemy(BattleSprite* enemy)
{
   // Enemy state changes go here
}
/*-----------------------------------------------*/