#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"

class Chest : public AnimatedSprite
{
private:
   void AI();
   //float randomSpeed();
   //void updateDirection();

public:
   Chest();
   ~Chest();

   // Functions
   //virtual void update(int ms) override;
   //void setRandomMovement();
};
