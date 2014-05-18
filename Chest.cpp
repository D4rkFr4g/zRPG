#include "Chest.h"

Chest::Chest()
{
   Texture* tex = textureLoader::getTexture("friendly_npcs");
   Sprite sprite = Sprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   *this = Chest((Chest&)sprite);
   name = "chest";

}
/*-----------------------------------------------*/
Chest::~Chest()
{
}
/*-----------------------------------------------*/