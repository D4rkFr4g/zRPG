#pragma once


class enumLibrary
{
protected:
   enumLibrary();

public:
   ~enumLibrary();

   static enum COLLISION
   {
      GROUND = 1,
      DEATH,
      PLATFORM,
      START,
      END,
      BATTLE_EASY,
      BATTLE_MEDIUM,
      BATTLE_HARD,
      BATTLE_BOSS,
      DUNGEON_1,
      OVERWORLD,
      VILLAGER,
	   CASTLE
   };
};

