#include "battleManager.h"


bool battleManager::isBattle = false;
PlayerSprite* battleManager::player;
EventQueue* battleManager::eventQueue;
DialogManager* battleManager::dialogManager;
std::vector<BattleSprite> battleManager::spriteQueue;
std::unordered_map<std::string, TileLevel>* battleManager::levels;
std::unordered_map<int, std::vector<BattleSprite>> battleManager::enemies;
std::unordered_map<int, std::vector<std::string>> battleManager::loot;
TileLevel** battleManager::currentLevel;
TileLevel* battleManager::previousLevel;
Camera* battleManager::cam;
int battleManager::prevCamX;
int battleManager::prevCamY;
enum battleManager::BATTLE_TYPE battleManager::currentBattle;
std::unordered_map<std::string, Texture>* battleManager::textures;
BattleSprite battleManager::battlePlayer;
int battleManager::battleState;
int battleManager::prevBattleState;
int battleManager::currentTurn;
std::unordered_map<int, std::string> battleManager::statBoost;
std::unordered_map<std::string, Menu> battleManager::menus;

/*-----------------------------------------------*/
battleManager::battleManager()
{
}
/*-----------------------------------------------*/
battleManager::~battleManager()
{
}
/*-----------------------------------------------*/
void battleManager::init()
{
   srand((unsigned int) time(NULL));

   // Setup battlePlayer
   Texture* tex = &(*textures)["link"];
   battlePlayer = BattleSprite(&tex->texture, 50, 100, 65, 65,
      0 * tex->uSize, 8 * tex->vSize, 1 * tex->uSize, 1 * tex->vSize);
   battlePlayer.isAnimated = false; // TODO Remove once animations are done

   for (int i = 0; i < (int)player->xpToNextLevel.size(); i++)
      player->xpToNextLevel[i] = (i + 1) * 100;

   // Setup Enemies
   enemyManager::init(textures, &enemies);

   // Setup Loot
   loot[BATTLE_EASY].push_back("Rupees");
   loot[BATTLE_EASY].push_back("Red Potion");
   loot[BATTLE_MEDIUM].push_back("Rupees");
   loot[BATTLE_MEDIUM].push_back("Red Potion");
   loot[BATTLE_MEDIUM].push_back("Blue Potion");
   loot[BATTLE_HARD].push_back("Rupees");
   loot[BATTLE_HARD].push_back("Red Potion");
   loot[BATTLE_HARD].push_back("Blue Potion");
   loot[BATTLE_HARD].push_back("Green Potion");

   // Setup statBoost
   statBoost[0] = "STR";
   statBoost[1] = "CON";
   statBoost[2] = "DEX";
   statBoost[3] = "INT";
   statBoost[4] = "LCK";

   battleState = STATE_PLAYER;
   menus["player"] = Menu(1);
   menus["action"] = Menu(4);
   menus["item"] = Menu(battlePlayer.items.size());
}
/*-----------------------------------------------*/
void battleManager::keyboard(const unsigned char* kbState, unsigned char* kbPrevState)
{
   /* PURPOSE:		Process keyboard input for battles
      RECEIVES:   kbState - current state of the keyboard
                  kbPrevState - Previous frame state of the keyboard
      RETURNS:
      REMARKS:
   */

   bool isSelected = kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J];
   bool isCanceled = kbState[SDL_SCANCODE_K] && !kbPrevState[SDL_SCANCODE_K];
   bool isUp = kbState[SDL_SCANCODE_W] && !kbPrevState[SDL_SCANCODE_W];
   bool isDown = kbState[SDL_SCANCODE_S] && !kbPrevState[SDL_SCANCODE_S];   

   // Battle States
   // Idle State
   if (battleState == STATE_IDLE)
   {
      // Handle State Transition
      if (battleState != prevBattleState)
      {
         prevBattleState = battleState;
         std::unordered_map<std::string, Menu>::iterator itr = menus.begin();
         std::unordered_map<std::string, Menu>::iterator end = menus.end();
         for (itr; itr != end; itr++)
         {
            itr->second.reset();
            itr->second.setActive(false);
         }
      }

      // Check for new Transition
      if (currentTurn == 0)
         battleState = STATE_PLAYER;
   }
   // Player State
   if (battleState == STATE_PLAYER)
   {
      // Handle State Transition
      if (battleState != prevBattleState)
      {
         prevBattleState = battleState;
         menus["player"].setActive(true);
      }

      // Check for new Transition
      if (isSelected)
      {
         battleState = STATE_ACTION;
      }
      else if (isUp)
         menus["player"].previous();
      else if (isDown)
         menus["player"].next();
   }
   // Action State
   else if (battleState == STATE_ACTION)
   {
      // Handle State Transition
      if (battleState != prevBattleState)
      {
         prevBattleState = battleState;
         menus["action"].setActive(true);
      }

      // Check for new Transition
      if (isSelected)
      {
         int choice = menus["action"].getSelection();
         menus["action"].setActive(false);
         if (choice == ACTION_FIGHT)
            battleState = STATE_ENEMY;
         else if (choice == ACTION_DEFEND)
            executeSelection();
         else if (choice == ACTION_ITEMS)
            battleState = STATE_ITEMS;
         if (choice == ACTION_FLEE)
            executeSelection();
      }
      else if (isCanceled)
      {
         menus["action"].setActive(false);
         battleState = STATE_PLAYER;
      }
      else if (isUp)
         menus["action"].previous();
      else if (isDown)
         menus["action"].next();
   }
   // Items State
   else if (battleState == STATE_ITEMS)
   {
      // Handle State Transition
      if (battleState != prevBattleState)
      {
         prevBattleState = battleState;
         menus["item"].setActive(true);
      }

      // Check for new Transition
      if (isSelected)
      {
         menus["item"].setActive(false);
         executeSelection();
      }
      else if (isCanceled)
      {
         menus["item"].setActive(false);
         battleState = STATE_ACTION;
      }
      else if (isUp)
         menus["item"].previous();
      else if (isDown)
         menus["item"].next();
   }
   // Enemy State
   else if (battleState == STATE_ENEMY)
   {
      // Handle State Transition
      if (battleState != prevBattleState)
      {
         prevBattleState = battleState;
         menus["enemy"].setActive(true);
      }

      // Check for new Transition
      if (isSelected)
      {
         executeSelection();
      }
      else if (isCanceled)
      {
         menus["enemy"].setActive(false);
         menus["action"].setActive(true);
         battleState = STATE_ACTION;
      }
      else if (isUp)
         menus["enemy"].previous();
      else if (isDown)
         menus["enemy"].next();
   }

   dialogManager->updateBattleDialog(menus);

   if (kbState[SDL_SCANCODE_U] && !kbPrevState[SDL_SCANCODE_U])
   {
      battleCleanup(); // TODO Remove when unneeded
   }
}
/*-----------------------------------------------*/
void battleManager::checkBattle(BATTLE_TYPE battle)
{
   /* PURPOSE:		Determines probabilistically if battle should start
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   if (rand() % 100 >= 75)
   {
      currentBattle = battle;
      initBattle();
   }
}
/*-----------------------------------------------*/
void battleManager::stopPlayer()
{
   /* PURPOSE:		Stops player movement and animations
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   player->isAnimated = false;
   player->prevState = player->state;
   player->speedX = 0;
   player->speedY = 0;
   player->state = 0;
   player->isAlive = false;
}
/*-----------------------------------------------*/
void battleManager::initBattle()
{
   /* PURPOSE:		Sets up battle and stores current state
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   currentTurn = 0;
   isBattle = true;
   previousLevel = *currentLevel;
   stopPlayer();
   prevCamX = cam->x;
   prevCamY = cam->y;
   cam->x = 0;
   cam->y = 0;

   // Player setup
   battlePlayer.initStats(player->stats["STR"], player->stats["CON"], 
      player->stats["DEX"], player->stats["INT"], player->stats["LCK"]);
   battlePlayer.items = player->items;
   battlePlayer.name = player->name;
   battlePlayer.health = player->health;
   battlePlayer.maxHealth = player->maxHealth;
   battlePlayer.magic = player->magic;
   battlePlayer.maxMagic = player->maxMagic;

   spriteQueue.push_back(battlePlayer);

   int numEnemies = rand() % 3 + 1;

   if (currentBattle == BATTLE_EASY)
      *currentLevel = &(*levels)["battle_test"];
   else if (currentBattle == BATTLE_MEDIUM)
   {
      *currentLevel = &(*levels)["battle_medium"];
   }
   else if (currentBattle == BATTLE_HARD)
   {
      *currentLevel = &(*levels)["battle_hard"];
   }
   else if (currentBattle == BATTLE_BOSS)
   {
      *currentLevel = &(*levels)["battle_boss"];
   }

   // Load enemies into spriteQueue for battle
   for (int i = 0; i < numEnemies; i++)
   {
      int numTypesEnemy = enemies[currentBattle].size();
      int choice = rand() % numTypesEnemy;

      BattleSprite enemy = enemies[currentBattle][choice];
      
      // Boost stats based on level
      for (int i = 0; i < enemy.level; i++)
      {
         int choice = rand() % (int)statBoost.size();
         enemy.stats[statBoost[choice]]++;
      }
      spriteQueue.push_back(enemy);

      // Stagger enemy positions
      if (i == 1)
         spriteQueue[i+1].posY -= 75;
      else if (i == 2)
         spriteQueue[i+1].posY += 75;
   }

   menus["enemy"] = Menu(numEnemies);
   menus["item"] = Menu(battlePlayer.items.size());
   dialogManager->initBattleDialog(&spriteQueue);
}
/*-----------------------------------------------*/
void battleManager::battleCleanup()
{
   /* PURPOSE:		Resets everything to return to normal map mode
      RECEIVES:	
      RETURNS:
      REMARKS:
   */

   battlePlayer.health = battlePlayer.maxHealth;
   battlePlayer.magic = battlePlayer.maxMagic;
   player->isAlive = true;
   *currentLevel = previousLevel;
   isBattle = false;
   spriteQueue.clear();

   cam->x = prevCamX;
   cam->y = prevCamY;

   // Clean the spriteQueue
   for (int i = 1; i < (int)spriteQueue.size(); i++)
      spriteQueue.pop_back();

   dialogManager->battleCleanup();
}
/*-----------------------------------------------*/
void battleManager::drawSprites()
{
   /* PURPOSE:		Draws all battle related sprites
      RECEIVES:   
      RETURNS:
      REMARKS:
   */

   for (int i = 0; i < (int)spriteQueue.size(); i++)
   {
      spriteQueue[i].drawUV(cam->x, cam->y);
   }
}
/*-----------------------------------------------*/
void battleManager::updateBattle(int ms)
{
   /* PURPOSE:		Update the battle based on how much time passed
      RECEIVES:   ms - time in milliseconds since last update
      RETURNS:
      REMARKS: 
   */

   for (int i = 0; i < (int) spriteQueue.size(); i++)
   {
      spriteQueue[i].update(ms);
   }

   if (currentTurn != 0)
   {
      enemyManager::updateEnemy(&spriteQueue[currentTurn]);
      updateCurrentTurn();
   }
}
/*-----------------------------------------------*/
void battleManager::updateCurrentTurn()
{
   /* PURPOSE:		Updates whose turn it is to attack
      RECEIVES:   
      RETURNS:
      REMARKS:
   */

   currentTurn++;
   if (currentTurn >= spriteQueue.size())
      currentTurn = 0;
}
/*-----------------------------------------------*/
void battleManager::executeSelection()
{
   battleState = STATE_IDLE;
   updateCurrentTurn();
}
/*-----------------------------------------------*/