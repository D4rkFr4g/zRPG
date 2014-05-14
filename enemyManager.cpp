#include "enemyManager.h"

std::unordered_map<int, std::vector<BattleSprite*>>* enemyManager::enemies;

/*-----------------------------------------------*/
enemyManager::enemyManager()
{
}
/*-----------------------------------------------*/
enemyManager::~enemyManager()
{
}
/*-----------------------------------------------*/
void enemyManager::init(std::unordered_map<std::string, Texture>* _textures, std::unordered_map<int, std::vector<BattleSprite*>>* _enemies)
{
   // Initialize all enemies
   enemies = _enemies;

   (*enemies)[BATTLE_EASY].push_back(new BattleChicken());
   (*enemies)[BATTLE_MEDIUM].push_back(new BattleGuard());
   (*enemies)[BATTLE_HARD].push_back(new BattleKnight());
   (*enemies)[BATTLE_HARD].push_back(new BattleGanon());
}
/*-----------------------------------------------*/
void enemyManager::updateEnemy(BattleSprite* enemy)
{
   // Enemy state changes go here

   // Might not need this now.
}
/*-----------------------------------------------*/