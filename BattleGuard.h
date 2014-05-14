#pragma once
#include "BattleSprite.h"

class BattleGuard :
   public BattleSprite
{
private:
   void AI();

public:
   BattleGuard();
   ~BattleGuard();

   // Functions
   virtual void update(int ms) override;
   //virtual void notify(Event* event) override;
};

