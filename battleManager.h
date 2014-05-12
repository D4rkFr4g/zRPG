#pragma once
#include <unordered_map>
#include <string>
#include <time.h>
#include <random>
#include <SDL.h>
#include "PlayerSprite.h"
#include "EventQueue.h"
#include "Event.h"
#include "DialogContainer.h"
#include "TileLevel.h"
#include "Camera.h"
#include "BattleSprite.h"
#include "Texture.h"
#include "enemyManager.h"
#include "dialogManager.h"
#include "Menu.h"


class battleManager
{
public:
   ~battleManager();

   // Enum
   enum BATTLE_TYPE { BATTLE_EASY = 6, BATTLE_MEDIUM, BATTLE_HARD, BATTLE_BOSS };
   enum CONTROLS {CONTROL_NULL, CONTROL_UP, CONTROL_DOWN, CONTROL_SELECT, CONTROL_CANCEL};
   enum BATTLE_STATE {STATE_IDLE, STATE_PLAYER, STATE_ACTION, STATE_ENEMY, STATE_ITEMS, STATE_FLEE, STATE_DEFEND};
   enum ACTIONS {ACTION_FIGHT, ACTION_DEFEND, ACTION_ITEMS, ACTION_FLEE};

   // Functions
   static void init();
   static void keyboard(const unsigned char* kbState, unsigned char* kbPrevState);
   static void checkBattle(BATTLE_TYPE battle);
   static void stopPlayer();
   static void initBattle();
   static void battleCleanup();
   static void drawSprites();
   static void updateBattle(int ms);
   static void executeSelection();
   static void useItem(std::string item);
   static void playerDeath();

   // Variables 
   static bool isBattle;
   static bool isPlayerAlive;
   static PlayerSprite* player;
   static EventQueue* eventQueue;
   static DialogManager* dialogManager;
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
   static int battleState;
   static int prevBattleState;
   static int currentTurn;
   static std::unordered_map<std::string, Menu> menus;
   static std::unordered_map<int, std::string> statBoost;

protected:
   battleManager();

private:
   static void updateCurrentTurn();
};

