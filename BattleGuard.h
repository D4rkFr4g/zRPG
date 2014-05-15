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

   // Virtual Functions
   virtual void update(int ms) override;
   //virtual void notify(Event* event) override;
   virtual void takeTurn() override;
   virtual BattleGuard* clone() const override;
};

