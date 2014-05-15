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

   // Virtual Functions
   virtual void update(int ms) override;
   //virtual void notify(Event* event) override;
   virtual void takeTurn() override;
   virtual BattleGanon* clone() const override;
};

