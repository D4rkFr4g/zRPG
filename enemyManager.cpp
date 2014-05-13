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
   //Texture* tex = &(*textures)["chicken"];
   //BattleSprite enemy = BattleSprite(&tex->texture, 500,100,tex->width, tex->height, 0, 0, 0.5, 1);
   //enemy.isAnimated = false; // TODO Remove once animations are setup
   //enemy.name = "chicken";
   //enemy.level = 1;
   
   Texture* tex = &(*textures)["chicken_battle"];
   BattleSprite enemy = BattleSprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   enemy.isAnimated = false; // TODO Remove once animations are setup
   enemy.name = "chicken";
   enemy.level = 1;
   enemy.isColliderDrawn = true;

   //// Setup animations
   //float uSize = 0.5;
   //float vSize = 1;

   //// Animations
   //int numFrames = 1;
   //int timeToNextFrame = 100;

   ////// Idle Animation
   //AnimationFrame* frames_idle = new AnimationFrame[numFrames];
   //frames_idle[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //Animation animation_idle = Animation("Idle", frames_idle, numFrames);
   //enemy.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 11;
   //AnimationFrame* frames_attack = new AnimationFrame[numFrames];
   //frames_attack[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[1] = AnimationFrame(0 * uSize, 10 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[2] = AnimationFrame(0 * uSize, 9 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[3] = AnimationFrame(0 * uSize, 8 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[4] = AnimationFrame(0 * uSize, 7 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[5] = AnimationFrame(0 * uSize, 6 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[6] = AnimationFrame(0 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[7] = AnimationFrame(0 * uSize, 4 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[8] = AnimationFrame(0 * uSize, 3 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[9] = AnimationFrame(0 * uSize, 2 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[10] = AnimationFrame(0 * uSize, 1 * vSize, 1 * uSize, 1 * vSize);
   //frames_attack[11] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //Animation animation_attack = Animation("Attack", frames_attack, numFrames);
   //AnimationData animData = AnimationData(animation_attack, timeToNextFrame, false);
   //animData.eventFrame = 7;
   //enemy.animations[animation_attack.name] = animData;

   //// Damaged Animation
   //numFrames = 12;
   //AnimationFrame* frames_damaged = new AnimationFrame[numFrames];
   //frames_damaged[0] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   //frames_damaged[1] = AnimationFrame(0 * uSize, 12 * vSize, 1 * uSize, 1 * vSize);
   //frames_damaged[2] = AnimationFrame(0 * uSize, 13 * vSize, 1 * uSize, 1 * vSize);
   //frames_damaged[3] = frames_damaged[0];
   //frames_damaged[4] = frames_damaged[1];
   //frames_damaged[5] = frames_damaged[2];
   //frames_damaged[6] = frames_damaged[0];
   //frames_damaged[7] = frames_damaged[1];
   //frames_damaged[8] = frames_damaged[2];
   //frames_damaged[9] = frames_damaged[0];
   //frames_damaged[10] = frames_damaged[1];
   //frames_damaged[11] = frames_damaged[2];
   //Animation animation_damaged = Animation("Damaged", frames_damaged, numFrames);
   //animData = AnimationData(animation_damaged, timeToNextFrame, false);
   //enemy.animations[animation_damaged.name] = animData;

   //enemy.setAnimation("Idle");
   
   (*enemies)[BATTLE_EASY].push_back(enemy);

   ////Medium enemy
   //tex = &(*textures)["guard_battle"];
   //enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   //enemy.isAnimated = false; // TODO Remove once animations are setup
   //enemy.name = "guard";
   //enemy.level = 5;

   //// Setup animations
   //uSize = tex->uSize;
   //vSize = tex->vSize;

   //// Animations
   //numFrames = 1;
   //timeToNextFrame = 100;

   ////// Idle Animation
   //frames_idle = new AnimationFrame[numFrames];
   ////frames_idle[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //animation_idle = Animation("Idle", frames_idle, numFrames);
   //enemy.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames_attack = new AnimationFrame[numFrames];
   ////frames_attack[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   //
   //animation_attack = Animation("Attack", frames_attack, numFrames);
   //animData = AnimationData(animation_attack, timeToNextFrame, false);
   //animData.eventFrame = 13;
   //enemy.animations[animation_attack.name] = animData;

   //enemy.setAnimation("Idle");

   //(*enemies)[BATTLE_MEDIUM].push_back(enemy);

   ////Hard enemy
   //tex = &(*textures)["knight_battle"];
   //enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, tex->uSize, tex->vSize);
   //enemy.isAnimated = false; //TODO Remove once animations are setup
   //enemy.name = "knight";
   //enemy.level = 10;

   //// Setup animations
   //uSize = tex->uSize;
   //vSize = tex->vSize;

   //// Animations
   //numFrames = 1;
   //timeToNextFrame = 100;

   ////// Idle Animation
   //frames_idle = new AnimationFrame[numFrames];
   ////frames_idle[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //animation_idle = Animation("Idle", frames_idle, numFrames);
   //enemy.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames_attack = new AnimationFrame[numFrames];
   ////frames_attack[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   //animation_attack = Animation("Attack", frames_attack, numFrames);
   //animData = AnimationData(animation_attack, timeToNextFrame, false);
   //animData.eventFrame = 13;
   //enemy.animations[animation_attack.name] = animData;

   //enemy.setAnimation("Idle");

   //(*enemies)[BATTLE_HARD].push_back(enemy);
   //
   ////Boss enemy
   //tex = &(*textures)["ganon_battle"];
   //enemy = BattleSprite(&tex->texture, 500, 100, tex->width, tex->height, 0, 0, 1, 1);
   //enemy.isAnimated = false; //TODO Remove once animations are setup
   //enemy.name = "Ganon";
   //enemy.level = 11;
   //
   //// Setup animations
   //uSize = tex->uSize;
   //vSize = tex->vSize;

   //// Animations
   //numFrames = 1;
   //timeToNextFrame = 100;

   ////// Idle Animation
   //frames_idle = new AnimationFrame[numFrames];
   ////frames_idle[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   //animation_idle = Animation("Idle", frames_idle, numFrames);
   //enemy.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, false);

   //// Attack Animation
   //numFrames = 20;
   //frames_attack = new AnimationFrame[numFrames];
   ////frames_attack[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);

   //animation_attack = Animation("Attack", frames_attack, numFrames);
   //animData = AnimationData(animation_attack, timeToNextFrame, false);
   //animData.eventFrame = 13;
   //enemy.animations[animation_attack.name] = animData;

   //enemy.setAnimation("Idle");

   //(*enemies)[BATTLE_HARD].push_back(enemy);
}
/*-----------------------------------------------*/
void enemyManager::updateEnemy(BattleSprite* enemy)
{
   // Enemy state changes go here
}
/*-----------------------------------------------*/