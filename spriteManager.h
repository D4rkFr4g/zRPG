#pragma once
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"
#include "Chicken.h"
#include "VillagerA.h"
#include "VillagerB.h"
#include "VillagerC.h"
#include "Chest.h"
#include "Ganon.h"
#include "Zelda.h"
#include "bucketManager.h"
#include "MapManager.h"
#include "enumLibrary.h"

class spriteManager
{
protected:
   spriteManager();

private:


public:
   ~spriteManager();
   static void init(std::vector<std::vector<Sprite*>>* spriteBuckets, std::unordered_map<std::string, Texture>* textures, int* maxScreenWidth, int* maxScreenHeight);
   static void saveLevelSprites(std::string levelName);
   static void loadLevelSprites(std::string levelName);
   static void initChickens();
   static void initVillagerA();
   static void initVillagerB();
   static void initVillagerC();
   static void initChests();
   static void initGanon();
   static void initZelda();

   // Variables
  static std::unordered_map<std::string, std::vector<Sprite*>> levelSprites;
  static std::vector<std::vector<Sprite*>>* spriteBuckets;
  static std::unordered_map<std::string, Texture>* textures;
  static int *maxScreenWidth, *maxScreenHeight;
};

