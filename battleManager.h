#pragma once
#include <unordered_map>
#include <string>
#include <time.h>
#include <random>
#include <SDL.h>
#include "PlayerSprite.h"
#include "EventQueue.h"
#include "Event.h"
#include "DialogBox.h"
#include "TileLevel.h"
#include "Camera.h"
#include "BattleSprite.h"
#include "Texture.h"
#include "enemyManager.h"


class battleManager
{
protected:
   battleManager();

private:
   static void updateCurrentTurn();

public:
   ~battleManager();

   // Enum
   enum BATTLE_TYPE { BATTLE_EASY = 6, BATTLE_MEDIUM, BATTLE_HARD, BATTLE_BOSS };

   // Functions
   static void init();
   static void keyboard(const unsigned char* kbState, unsigned char* kbPrevState);
   static void checkBattle(BATTLE_TYPE battle);
   static void stopPlayer();
   static void initBattle();
   static void battleCleanup();
   static void drawSprites();
   static void updateBattle(int ms);

   // Variables
   static bool isBattle;
   static PlayerSprite* player;
   static EventQueue* eventQueue;
   static std::vector<DialogBox>* dialogQueue;
   static std::unordered_map<std::string, TileLevel>* levels;
   static std::unordered_map<int, std::vector<BattleSprite>> enemies;
   static std::unordered_map<int, std::vector<std::string>> loot;
   static TileLevel** currentLevel;
   static TileLevel* previousLevel;
   static std::vector<BattleSprite> spriteQueue;
   static Camera* cam;
   static int prevCamX;
   static int prevCamY;
   static BATTLE_TYPE currentBattle;
   static BattleSprite battlePlayer;
   static std::unordered_map<std::string, Texture>* textures;
   static int currentTurn;
   static std::unordered_map<int, std::string> statBoost;
};

