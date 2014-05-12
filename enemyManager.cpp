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

   //Easy enemy
   Texture* texE = &(*textures)["chicken"];
   BattleSprite easyEnemy = BattleSprite(&texE->texture, 500,100,texE->width, texE->height, 0, 0, 0.5, 1);
   easyEnemy.isAnimated = false; // TODO Remove once animations are setup
   easyEnemy.isFlippedX = true;
   
   easyEnemy.initStats(1, 1, 1, 1, 1);
   easyEnemy.name = "chicken";
   
   (*enemies)[BATTLE_EASY].push_back(easyEnemy);
   easyEnemy.level = 5;

   //Medium enemy
   Texture* texM = &(*textures)["guard"];
   BattleSprite mediumEnemy = BattleSprite(&texM->texture, 500, 100, texM->width, texM->height, 0, 0, 1, 1);
   mediumEnemy.isAnimated = false; // TODO Remove once animations are setup
   mediumEnemy.isFlippedX = false;

   mediumEnemy.initStats(5, 5, 5, 5, 5);
   mediumEnemy.name = "guard";

   (*enemies)[BATTLE_MEDIUM].push_back(mediumEnemy);
   mediumEnemy.level = 10;

   //Hard enemy
   Texture* texH = &(*textures)["knight"];
   BattleSprite hardEnemy = BattleSprite(&texH->texture, 500, 100, texH->width, texH->height, 0, 0, 1, 1);
   hardEnemy.isAnimated = false; //TODO Remove once animations are setup
   hardEnemy.isFlippedX = false;

   hardEnemy.initStats(10, 10, 10, 10, 10);
   hardEnemy.name = "knight";
   
   (*enemies)[BATTLE_HARD].push_back(hardEnemy);
   hardEnemy.level = 11;
   //(*enemies)[BATTLE_BOSS].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::updateEnemy(BattleSprite* enemy)
{
   // Enemy state changes go here
}
/*-----------------------------------------------*/