#pragma once
#include "BattleSprite.h"


class BattleKnight :
   public BattleSprite
{
private:
   void AI();

public:
   BattleKnight();
   ~BattleKnight();

   // Virtual Functions
   virtual void update(int ms) override;
   //virtual void notify(Event* event) override;
   virtual BattleKnight* clone() const override;
};

