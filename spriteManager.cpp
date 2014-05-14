#include "spriteManager.h"


std::unordered_map<std::string, std::vector<Sprite>> spriteManager::levelSprites;
std::vector<std::vector<Sprite*>>* spriteManager::spriteBuckets;
std::unordered_map<std::string, Sprite> spriteManager::spriteBase;
std::unordered_map<std::string, Texture>* spriteManager::textures;
/*-----------------------------------------------*/
spriteManager::spriteManager()
{
}
/*-----------------------------------------------*/
spriteManager::~spriteManager()
{
}
/*-----------------------------------------------*/
void spriteManager::init(std::vector<std::vector<Sprite*>>* spriteBuckets, std::unordered_map<std::string, Texture>* textures)
{
   /* PURPOSE:		Setups all sprites to be used in Engine
      RECEIVES:	spriteBuckets - vector to be filled for a particular level
      RETURNS:
      REMARKS:
   */

   this->spriteBuckets = spriteBuckets;
   this->textures = textures;
   initChickens();
   initGuards();
   initGanon();
   initChests();
   initPrincess();
}
/*-----------------------------------------------*/
void spriteManager::initChickens()
{
   /* PURPOSE:		Setups chicken sprites
      RECEIVES:	
      RETURNS:
      REMARKS:
   */

}
void spriteManager::initGuards()
{
   /* PURPOSE:		Setups Guard sprites
   RECEIVES:
   RETURNS:
   REMARKS:
   */


}
void spriteManager::initGanon()
{
   /* PURPOSE:		Setups Ganon sprites
   RECEIVES:
   RETURNS:
   REMARKS:
   */


}
void spriteManager::initChests()
{
   /* PURPOSE:		Setups Chest sprites
   RECEIVES:
   RETURNS:
   REMARKS:
   */


}
void spriteManager::initPrincess()
{
   /* PURPOSE:		Setups Princess sprites
   RECEIVES:
   RETURNS:
   REMARKS:
   */


}