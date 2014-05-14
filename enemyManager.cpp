#include "enemyManager.h"

std::unordered_map<std::string, Texture>* enemyManager::textures;
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
   textures = _textures;
   enemies = _enemies;

   (*enemies)[BATTLE_EASY].push_back(new BattleChicken());

   initGuards();
   initKnights();
   initGanon();
}
/*-----------------------------------------------*/
void enemyManager::initGuards()
{
   //Medium enemy
   Texture* tex = &(*textures)["guard_battle"];
   BattleSprite* enemy = new BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   enemy->isAnimated = false; // TODO Remove once animations are setup
   enemy->name = "guard";
   enemy->level = 5;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;
   std::vector<AnimationFrame> frames;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   // Idle Animation
   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Idle", frames, numFrames);
   enemy->animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   // Attack Animation
   numFrames = 20;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   //frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   //animData.eventFrame = 13;
   enemy->animations[animation.name] = animData;

   enemy->setAnimation("Idle");


   ////Medium enemy
   //Texture* tex = &(*textures)["guard_battle"];
   //BattleSprite* enemy = new BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   //enemy.isAnimated = false; // TODO Remove once animations are setup
   //enemy.name = "guard";
   //enemy.level = 5;

   //// Setup animations
   //float uSize = tex->uSize;
   //float vSize = tex->vSize;
   //std::vector<AnimationFrame> frames;

   //// Animations
   //int numFrames = 1;
   //int timeToNextFrame = 100;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());

   //// Idle Animation
   //frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //Animation animation = Animation("Idle", frames, numFrames);
   //enemy.animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());
   ////frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   //animation = Animation("Attack", frames, numFrames);
   //AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   ////animData.eventFrame = 13;
   //enemy.animations[animation.name] = animData;

   //enemy.setAnimation("Idle");

   (*enemies)[BATTLE_MEDIUM].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::initKnights()
{
   //Hard enemy
   Texture* tex = &(*textures)["knight_battle"];
   BattleSprite* enemy = new BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   enemy->isAnimated = false; //TODO Remove once animations are setup
   enemy->name = "knight";
   enemy->level = 10;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;
   std::vector<AnimationFrame> frames;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   //// Idle Animation
   //frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Idle", frames, numFrames);
   enemy->animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   // Attack Animation
   numFrames = 20;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   //frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   //animData.eventFrame = 13;
   enemy->animations[animation.name] = animData;

   enemy->setAnimation("Idle");

   ////Hard enemy
   //Texture* tex = &(*textures)["knight_battle"];
   //BattleSprite enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   //enemy.isAnimated = false; //TODO Remove once animations are setup
   //enemy.name = "knight";
   //enemy.level = 10;

   //// Setup animations
   //float uSize = tex->uSize;
   //float vSize = tex->vSize;
   //std::vector<AnimationFrame> frames;

   //// Animations
   //int numFrames = 1;
   //int timeToNextFrame = 100;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());

   ////// Idle Animation
   ////frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //Animation animation = Animation("Idle", frames, numFrames);
   //enemy.animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());
   ////frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   //animation = Animation("Attack", frames, numFrames);
   //AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   ////animData.eventFrame = 13;
   //enemy.animations[animation.name] = animData;

   //enemy.setAnimation("Idle");

   (*enemies)[BATTLE_HARD].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::initGanon()
{
   //Boss enemy
   Texture* tex = &(*textures)["ganon_battle"];
   BattleSprite* enemy = new BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, 1, 1);
   enemy->isAnimated = false; //TODO Remove once animations are setup
   enemy->name = "Ganon";
   enemy->level = 11;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;
   std::vector<AnimationFrame> frames;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   //// Idle Animation
   //frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Idle", frames, numFrames);
   enemy->animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   // Attack Animation
   numFrames = 20;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());
   //frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   //animData.eventFrame = 13;
   enemy->animations[animation.name] = animData;

   enemy->setAnimation("Idle");

   ////Boss enemy
   //Texture* tex = &(*textures)["ganon_battle"];
   //BattleSprite enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, 1, 1);
   //enemy.isAnimated = false; //TODO Remove once animations are setup
   //enemy.name = "Ganon";
   //enemy.level = 11;

   //// Setup animations
   //float uSize = tex->uSize;
   //float vSize = tex->vSize;
   //std::vector<AnimationFrame> frames;

   //// Animations
   //int numFrames = 1;
   //int timeToNextFrame = 100;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());

   ////// Idle Animation
   ////frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //Animation animation = Animation("Idle", frames, numFrames);
   //enemy.animations[animation.name] = AnimationData(animation, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames.clear();
   //frames.assign(numFrames, AnimationFrame());
   ////frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   //animation = Animation("Attack", frames, numFrames);
   //AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   ////animData.eventFrame = 13;
   //enemy.animations[animation.name] = animData;

   //enemy.setAnimation("Idle");

   (*enemies)[BATTLE_HARD].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::updateEnemy(BattleSprite* enemy)
{
   // Enemy state changes go here
}
/*-----------------------------------------------*/