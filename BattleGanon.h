#pragma once
#include "BattleSprite.h"


class BattleGanon :
   public BattleSprite
{
private:
   void AI();

public:
   BattleGanon();
   ~BattleGanon();

   // Functions
   virtual void update(int ms) override;
   //virtual void notify(Event* event) override;
   virtual void takeTurn() override;
};

