#include "BattleSprite.h"


/*-----------------------------------------------*/
BattleSprite::BattleSprite()
{
}
/*-----------------------------------------------*/
BattleSprite::BattleSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY) 
: AnimatedSprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
   /*Strength = damage modifier
      Constitution = hit points
      Dexterity = accuracy
      Intelligence == magic points
      Luck == Luck points*/

   xpToNextLevel.reserve(10);
   level = 1;
   maxHealth = 10 * stats["CON"];
   health = maxHealth;
}
/*-----------------------------------------------*/
BattleSprite::~BattleSprite()
{
}
/*-----------------------------------------------*/
void BattleSprite::initStats(int STR, int CON, int DEX, int INT, int LCK)
{
   stats["STR"] = STR;
   stats["CON"] = CON;
   stats["DEX"] = DEX;
   stats["INT"] = INT;
   stats["LCK"] = LCK;
}