#pragma once
#include "BattleSprite.h"


class BattleChicken :
   public BattleSprite
{
private:
   void AI();

public:
   BattleChicken();
   ~BattleChicken();

   // Virtual Functions
   virtual void update(int ms) override;
   virtual void notify(Event* event) override;
   virtual BattleChicken* clone() const override;
};

