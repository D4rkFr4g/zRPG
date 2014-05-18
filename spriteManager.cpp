#include "spriteManager.h"
#include "MapManager.h"


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
   initVillagerA();
   initVillagerB();
   initVillagerC();
   initChests();

   // Setup map structure so they are not null
   // Should probably send the filnames and load them that way in one place
   levelSprites["dungeon_1"];
   levelSprites["overworld"];

}
/*-----------------------------------------------*/
void spriteManager::saveLevelSprites(std::string levelName)
{
   /* PURPOSE:		Saves all the sprites for the current level
      RECEIVES:	levelName - name of the level which sprites come from
      RETURNS:
      REMARKS:
   */

   std::unordered_map<std::string, std::vector<Sprite*>>::iterator itr = levelSprites.find(levelName);
   std::unordered_map<std::string, std::vector<Sprite*>>::iterator end = levelSprites.end();

   if (itr != end)
   {
      // Clear out levelSprites to make room for new sprites
      levelSprites.find(levelName)->second.clear();

      // Save level sprites for later
      for (int i = 0; i < (int)spriteBuckets->size(); i++)
      {
         for (int j = 0; j < (int)(*spriteBuckets)[i].size(); j++)
            levelSprites[levelName].push_back((*spriteBuckets)[i][j]);
      }
   }
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
         Sprite* sprite = (*sprites)[i];
         
         int bucket = bucketManager::whichBucket(sprite->x, sprite->y);
         
         if (bucket < 0)
            bucket = 0;
         else if (bucket >= spriteBuckets->size() - 1)
            bucket = spriteBuckets->size() - 1;
         (*spriteBuckets)[bucket].push_back(sprite);
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
   std::vector<Sprite*> tiles = MapManager::getCollidableTileType("overworld", enumLibrary::COLLISION::BATTLE_EASY);

   // Load the Initial chickens
   for (int i = 0; i < initialChickens; i++)
   {
      Texture* tex = textureLoader::getTexture("cucco");
  
      int choice = rand() % tiles.size();
      int x = tiles[choice]->x;
      int y = tiles[choice]->y;

      Chicken* chicken = new Chicken();
      chicken->updatePosition(x, y);

      // Set Chicken direction
      chicken->setRandomMovement();

      levelSprites["overworld"].push_back(chicken);
   }
}
/*-----------------------------------------------*/
void spriteManager::initVillagerA()
{
	/* PURPOSE:		Loads the Villager A sprite in the designated level
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	//int initialVillagerA = 1;

	VillagerA* villager = new VillagerA();
	villager->updatePosition(1846,870);
   villager->name = "Bridge Guard";
   villager->collider.h += 70;
	levelSprites["overworld"].push_back(villager);

}
/*-----------------------------------------------*/
void spriteManager::initVillagerB()
{
	/* PURPOSE:		Loads the Villager B sprite in the designated level
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	VillagerB* villager = new VillagerB();
	villager->updatePosition(665, 580);
	levelSprites["overworld"].push_back(villager);

}
/*-----------------------------------------------*/
void spriteManager::initVillagerC()
{
	/* PURPOSE:		Loads the Villager C sprite in the designated level
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

	VillagerC* villager = new VillagerC();
	villager->updatePosition(1090, 415);
	levelSprites["overworld"].push_back(villager);

}
/*-----------------------------------------------*/
void spriteManager::initChests()
{
	/* PURPOSE:		Loads the treasure chest sprites in the designated level
	RECEIVES:
	RETURNS:
	REMARKS:
	*/

   struct ChestPos
   {
      std::string levelName;
      std::string item;
      int x;
      int y;
      int qty;

      ChestPos(std::string _levelName, std::string _item, int _qty, int _x, int _y)
      {
         levelName = _levelName;
         x = _x;
         y = _y;
         item = _item;
         qty = _qty;
      }
   };

   std::vector<ChestPos> chests;

   chests.push_back(ChestPos("overworld", "Rupees", 300, 304, 80));
   chests.push_back(ChestPos("overworld", "Red Potion", 5, 2176, 304));
   chests.push_back(ChestPos("overworld", "Green Potion", 5, 2976, 128));
   chests.push_back(ChestPos("overworld", "Green Potion", 5, 304, 1872));
   chests.push_back(ChestPos("dungeon_1", "sword", 1, 480, 416));

   for (int i = 0; i < (int)chests.size(); i++)
   {
      Chest* chest = new Chest();
      chest->updatePosition(chests[i].x, chests[i].y);
      chest->itemName = chests[i].item;
      chest->qty = chests[i].qty;
      levelSprites[chests[i].levelName].push_back(chest);
   }
}