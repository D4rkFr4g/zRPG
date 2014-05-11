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

   level = 1;
   maxHealth = 100;
   maxMagic = 10;
   health = maxHealth;
   magic = maxMagic;
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