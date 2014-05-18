#include "Chest.h"

Chest::Chest()
{
   Texture* tex = textureLoader::getTexture("friendly_npcs");
   Sprite sprite = Sprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0, 0, tex->uSize, tex->vSize);
   *this = Chest((Chest&)sprite);
   name = "chest";
   itemName = "";
   qty = 1;

   //Setup collider
   int xOffset = 0;
   int yOffset = 0;
   int width = 40;
   int height = 30;
   colliderXOffset = xOffset;
   colliderYOffset = yOffset;
   setCollider(&AABB(x + xOffset, y + yOffset, width, height));
   isColliderDrawn = true;

}
/*-----------------------------------------------*/
Chest::~Chest()
{
}
/*-----------------------------------------------*/
void Chest::onCollision()
{

}
/*-----------------------------------------------*/
void Chest::onTrigger()
{
   eventQueue->queueEvent(Event(Event::ET_ITEM, "item", itemName));
}
/*-----------------------------------------------*/