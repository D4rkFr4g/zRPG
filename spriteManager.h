#pragma once
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Texture.h"

class spriteManager
{
protected:
   spriteManager();

private:
   void initChickens();
   void initGuards();
   void initGanon();
   void initChests();
   void initPrincess();

public:
   ~spriteManager();
   void init(std::vector<std::vector<Sprite*>>* spriteBuckets, std::unordered_map<std::string, Texture>* textures);
   


   // Variables
  static std::unordered_map<std::string, std::vector<Sprite>> levelSprites;
  static std::unordered_map<std::string, Sprite> spriteBase;
  static std::vector<std::vector<Sprite*>>* spriteBuckets;
  static std::unordered_map<std::string, Texture>* textures;
};

