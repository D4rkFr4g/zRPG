#include "Chest.h"

Chest::Chest()
{
   Texture* tex = textureLoader::getTexture("friendly_npcs");
   Sprite sprite = Sprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0 * tex->uSize, 3 * tex->vSize, tex->uSize, tex->vSize);
   *this = Chest((Chest&)sprite);
   name = "chest";
   itemName = "";
   qty = 1;

   //Setup collider
   int xOffset = 1;
   int yOffset = 0;
   int width = 30;
   int height = 35;
   colliderXOffset = xOffset;
   colliderYOffset = yOffset;
   setCollider(&AABB(x + xOffset, y + yOffset, width, height));
   isColliderDrawn = false;

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
   if (isVisible)
   {
      Event ev = Event(Event::ET_ITEM, "name", itemName);
      ev.numParams["qty"] = qty;
      eventQueue->queueEvent(ev);
      isVisible = false;
   }
}
/*-----------------------------------------------*/