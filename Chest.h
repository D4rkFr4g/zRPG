#pragma once
#include "Sprite.h"
#include "Texture.h"
#include "textureLoader.h"

class Chest : public Sprite
{
private:

public:
   Chest();
   ~Chest();

   // Virtual Functions
   virtual void onCollision() override;
   virtual void onTrigger() override;

   // Variables
   int qty;
   std::string itemName;
};
