#include "spriteManager.h"


std::unordered_map<std::string, std::vector<Sprite*>> spriteManager::levelSprites;
std::vector<std::vector<Sprite*>>* spriteManager::spriteBuckets;
std::unordered_map<std::string, Texture>* spriteManager::textures;
int *spriteManager::maxScreenWidth, *spriteManager::maxScreenHeight;

/*-----------------------------------------------*/
spriteManager::spriteManager()
{
}
/*-----------------------------------------------*/
spriteManager::~spriteManager()
{
}
/*-----------------------------------------------*/
void spriteManager::init(std::vector<std::vector<Sprite*>>* g_spriteBuckets, std::unordered_map<std::string, Texture>* g_textures, int* g_maxScreenWidth, int* g_maxScreenHeight)
{
   /* PURPOSE:		Setups all sprites to be used in Engine
      RECEIVES:	spriteBuckets - vector to be filled for a particular level
      RETURNS:
      REMARKS:
   */

   spriteBuckets = g_spriteBuckets;
   textures = g_textures;
   maxScreenWidth = g_maxScreenHeight;
   maxScreenHeight = g_maxScreenHeight;

   initChickens();
}
/*-----------------------------------------------*/
void spriteManager::loadLevelSprites(std::string levelName)
{
   /* PURPOSE:		Loads all the sprites for the current level
      RECEIVES:	levelName - name of the level which sprites come from
      RETURNS:
      REMARKS:
   */

   std::unordered_map<std::string, std::vector<Sprite*>>::iterator itr = levelSprites.find(levelName);
   std::unordered_map<std::string, std::vector<Sprite*>>::iterator end = levelSprites.end();
   
   if (itr != end)
   {
      // Clear out buckets to make room for new sprites
      for (int i = 0; i < (int)spriteBuckets->size(); i++)
         (*spriteBuckets)[i].clear();

      std::vector<Sprite*>* sprites = &levelSprites[levelName];

      for (int i = 0; i < (int)levelSprites[levelName].size(); i++)
      {
         // Load all into first bucket since next update will sort them to the correct buckets
         Sprite* sprite = (*sprites)[i];
         (*spriteBuckets)[bucketManager::whichBucket(sprite->x, sprite->y)].push_back(sprite);
      }
   }
}
/*-----------------------------------------------*/
void spriteManager::initChickens()
{
   /* PURPOSE:		Initialize all chickens to be used in game
      RECEIVES:	spriteBuckets - vector to be filled for a particular level
      RETURNS:
      REMARKS:
   */

   int initialChickens = 20;

   // Load the Initial chickens
   for (int i = 0; i < initialChickens; i++)
   {
      Texture* tex = textureLoader::getTexture("chicken");
      int x = rand() % (*maxScreenWidth - tex->cellWidth);
      int y = rand() % (*maxScreenHeight - tex->cellHeight);

      Chicken* chicken = new Chicken();
      chicken->updatePosition(x, y);

      // Set Chicken direction
      chicken->setRandomMovement();

      levelSprites["overworld"].push_back(chicken);
   }
}
/*-----------------------------------------------*/