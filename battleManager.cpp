#include "battleManager.h"
#include <typeinfo>


bool battleManager::isBattle = false;
bool battleManager::isPlayerAlive;
bool battleManager::isBattleWon;
PlayerSprite* battleManager::player;
EventQueue* battleManager::eventQueue;
DialogManager* battleManager::dialogManager;
std::vector<BattleSprite*> battleManager::spriteQueue;
std::unordered_map<std::string, TileLevel>* battleManager::levels;
std::unordered_map<int, std::vector<BattleSprite*>> battleManager::enemies;
std::unordered_map<int, std::vector<std::string>> battleManager::loot;
TileLevel** battleManager::currentLevel;
TileLevel* battleManager::previousLevel;
Camera* battleManager::cam;
int battleManager::prevCamX;
int battleManager::prevCamY;
enum battleManager::BATTLE_TYPE battleManager::currentBattle;
int battleManager::numEnemies;
int battleManager::totalLevel;
std::unordered_map<std::string, Texture>* battleManager::textures;
BattleSprite battleManager::battlePlayer;
int battleManager::battleState;
int battleManager::prevBattleState;
int battleManager::currentTurn;
std::unordered_map<int, std::string> battleManager::statBoost;
std::unordered_map<std::string, Menu> battleManager::menus;
BattleMenu battleManager::battleMenu;
int battleManager::healthTimer = 1000;

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
   srand((unsigned int)time(NULL));

   initPlayer();

   // Setup Enemies
   enemyManager::init(textures, &enemies);

   // Setup Loot
   loot[BATTLE_EASY].reserve(20);
   loot[BATTLE_MEDIUM].reserve(20);
   loot[BATTLE_HARD].reserve(20);
   loot[BATTLE_BOSS].reserve(20);

   loot[BATTLE_EASY].push_back("Rupees");
   loot[BATTLE_EASY].push_back("Red Potion");
   loot[BATTLE_MEDIUM].push_back("Rupees");
   loot[BATTLE_MEDIUM].push_back("Red Potion");
   loot[BATTLE_MEDIUM].push_back("Blue Potion");
   loot[BATTLE_HARD].push_back("Rupees");
   loot[BATTLE_HARD].push_back("Red Potion");
   loot[BATTLE_HARD].push_back("Blue Potion");
   loot[BATTLE_HARD].push_back("Green Potion");
   loot[BATTLE_BOSS].push_back("Rupees");
   loot[BATTLE_BOSS].push_back("Triforce of Courage");
   loot[BATTLE_BOSS].push_back("Triforce of Wisdom");
   loot[BATTLE_BOSS].push_back("Triforce of Power");

   // Setup statBoost
   statBoost[0] = "STR";
   statBoost[1] = "CON";
   statBoost[2] = "DEX";
   statBoost[3] = "INT";
   statBoost[4] = "LCK";

   battleState = STATE_PLAYER;

   battleMenu = BattleMenu(battlePlayer.items.size());
}
/*-----------------------------------------------*/
void battleManager::initPlayer()
{
   player->initStats(1, 1, 1, 1, 1);

   // Setup battlePlayer
   Texture* tex = &(*textures)["link_battle"];
   battlePlayer = BattleSprite(&tex->texture, 20, 100, tex->cellWidth, tex->cellHeight,
      0 * tex->uSize, 0 * tex->vSize, 1 * tex->uSize, 1 * tex->vSize);

   battlePlayer.isColliderDrawn = false;

   // Setup animations
   float uSize = tex->uSize;
   float vSize = tex->vSize;

   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;

   //// Idle Animation
   std::vector<AnimationFrame> frames;
   frames.assign(numFrames, AnimationFrame());
   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_idle = Animation("Idle", frames, numFrames);
   battlePlayer.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, false);

   // Attack Animation
   numFrames = 20;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(0 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(0 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(0 * uSize, 16 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(0 * uSize, 15 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(0 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[6] = AnimationFrame(0 * uSize, 13 * vSize, 1 * uSize, 1 * vSize);
   frames[7] = AnimationFrame(0 * uSize, 12 * vSize, 1 * uSize, 1 * vSize);
   frames[8] = AnimationFrame(0 * uSize, 11 * vSize, 1 * uSize, 1 * vSize);
   frames[9] = AnimationFrame(0 * uSize, 10 * vSize, 1 * uSize, 1 * vSize);
   frames[10] = AnimationFrame(0 * uSize, 9 * vSize, 1 * uSize, 1 * vSize);
   frames[11] = AnimationFrame(0 * uSize, 8 * vSize, 1 * uSize, 1 * vSize);
   frames[12] = AnimationFrame(0 * uSize, 7 * vSize, 1 * uSize, 1 * vSize);
   frames[13] = AnimationFrame(0 * uSize, 6 * vSize, 1 * uSize, 1 * vSize);
   frames[14] = AnimationFrame(0 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[15] = AnimationFrame(0 * uSize, 4 * vSize, 1 * uSize, 1 * vSize);
   frames[16] = AnimationFrame(0 * uSize, 3 * vSize, 1 * uSize, 1 * vSize);
   frames[17] = AnimationFrame(0 * uSize, 2 * vSize, 1 * uSize, 1 * vSize);
   frames[18] = AnimationFrame(0 * uSize, 1 * vSize, 1 * uSize, 1 * vSize);
   frames[19] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   Animation animation = Animation("Attack", frames, numFrames);
   AnimationData animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 13;
   battlePlayer.animations[animation.name] = animData;

   // Damaged Animation
   timeToNextFrame = 30;
   numFrames = 13;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 23 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(0 * uSize, 22 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(0 * uSize, 21 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(0 * uSize, 20 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = frames[0];
   frames[5] = frames[1];
   frames[6] = frames[2];
   frames[7] = frames[3];
   frames[8] = frames[0];
   frames[9] = frames[1];
   frames[10] = frames[2];
   frames[11] = frames[3];
   frames[12] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Damaged", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 0;
   battlePlayer.animations[animation.name] = animData;

   // Defend Animation
   timeToNextFrame = 100;
   numFrames = 1;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 24 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Defend", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 0;
   battlePlayer.animations[animation.name] = animData;

   // Flee Animation
   timeToNextFrame = 1000;
   numFrames = 1;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 0 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Flee", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 0;
   battlePlayer.animations[animation.name] = animData;

   // Death Animation
   timeToNextFrame = 1000;
   numFrames = 1;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 26 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Death", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 0;
   battlePlayer.animations[animation.name] = animData;

   // Win Animation
   timeToNextFrame = 1000;
   numFrames = 1;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 25 * vSize, 1 * uSize, 1 * vSize);
   animation = Animation("Win", frames, numFrames);
   animData = AnimationData(animation, timeToNextFrame, false);
   animData.eventFrame = 0;
   battlePlayer.animations[animation.name] = animData;

   battlePlayer.setAnimation("Idle");
   battlePlayer.registerListeners(eventQueue);


   player->maxLevel = 10;
   player->xp = 0;

   player->xpToNextLevel.reserve(player->maxLevel - 1);
   player->xpToNextLevel.push_back(120);
   player->xpToNextLevel.push_back(300);
   player->xpToNextLevel.push_back(540);
   player->xpToNextLevel.push_back(840);
   player->xpToNextLevel.push_back(1440);
   player->xpToNextLevel.push_back(2340);
   player->xpToNextLevel.push_back(3540);
   player->xpToNextLevel.push_back(5340);
   player->xpToNextLevel.push_back(8340);
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

   BattleSprite* bPlayer = spriteQueue[0];
   // Reset player to original yPosition
   if (bPlayer->posY != bPlayer->startY &&
      bPlayer->curAnimation.def.name.compare("Attack") == 0 &&
      bPlayer->isIdle())
   {
      bPlayer->posY = bPlayer->startY;
   }

   //  Flee end animation
   if (bPlayer->curAnimation.def.name.compare("Flee") == 0 && bPlayer->isIdle())
   {
      battleCleanup();
   }

   if (isPlayerAlive && !isBattleWon && isEveryoneIdle())
   {
      // Battle States
      // Idle State
      if (battleState == STATE_IDLE)
      {
         // Handle State Transition
         if (battleState != prevBattleState)
         {
            prevBattleState = battleState;
            battleMenu.resetAll();
         }

         // Check for new Transition
         if (currentTurn == 0 && spriteQueue[0]->curAnimation.isFinished)
            battleState = STATE_PLAYER;
      }
      // Player State
      if (battleState == STATE_PLAYER)
      {
         // Handle State Transition
         if (battleState != prevBattleState)
         {
            prevBattleState = battleState;

            battleMenu.setActiveMenu("player");

            spriteQueue[0]->isDefending = false;
            spriteQueue[0]->setAnimation("Idle");
         }

         // Check for new Transition
         if (isSelected)
         {
            battleState = STATE_ACTION;
         }
         else if (isUp)
            battleMenu.previous();
         else if (isDown)
            battleMenu.next();
      }
      // Action State
      else if (battleState == STATE_ACTION)
      {
         // Handle State Transition
         if (battleState != prevBattleState)
         {
            prevBattleState = battleState;
            battleMenu.setActiveMenu("action");
         }

         // Check for new Transition
         if (isSelected)
         {
            int choice = battleMenu.getSelection();
            battleMenu.turnOff();

            if (choice == ACTION_FIGHT)
               battleState = STATE_ENEMY;
            else if (choice == ACTION_DEFEND)
            {
               battleState = STATE_DEFEND;
               executeSelection();
            }
            else if (choice == ACTION_ITEMS)
               battleState = STATE_ITEMS;
            if (choice == ACTION_FLEE)
            {
               battleState = STATE_FLEE;
               executeSelection();
            }
         }
         else if (isCanceled)
            battleState = STATE_PLAYER;
         else if (isUp)
            battleMenu.previous();
         else if (isDown)
            battleMenu.next();
      }
      // Items State
      else if (battleState == STATE_ITEMS)
      {
         // Handle State Transition
         if (battleState != prevBattleState)
         {
            prevBattleState = battleState;
            battleMenu.setActiveMenu("item");
         }

         // Check for new Transition
         if (isSelected)
         {
            //battleMenu.turnOff();
            executeSelection();
         }
         else if (isCanceled)
            battleState = STATE_ACTION;
         else if (isUp)
            battleMenu.previous();
         else if (isDown)
            battleMenu.next();
      }
      // Enemy State
      else if (battleState == STATE_ENEMY)
      {
         // Handle State Transition
         if (battleState != prevBattleState)
         {
            prevBattleState = battleState;
            battleMenu.setActiveMenu("enemy");
         }

         // Check for new Transition
         if (isSelected)
         {
            executeSelection();
         }
         else if (isCanceled)
         {
            battleState = STATE_ACTION;
         }
         else if (isUp)
            battleMenu.previous();
         else if (isDown)
            battleMenu.next();
      }

      if (isBattle && !isBattleWon)
         dialogManager->updateBattleDialog(battleMenu);


      if (isSelected)
      {
         eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "menu_select"));
      }
      else if (isCanceled)
      {
         eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "menu_back"));
      }
      else if (isUp || isDown)
      {
         eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "menu_cursor"));
      }
}

   // Handle button input when battle is over
   if (!isPlayerAlive && kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J])
   {
      playerDeath();
   }
   if (isBattleWon && kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J])
   {
      dialogManager->battleResetDialog();
   }


   // Keyboard buttons for Debugging Battle // TODO Remove at end
   //---------------------------------------------------------------//

   //if (kbState[SDL_SCANCODE_U] && !kbPrevState[SDL_SCANCODE_U])
   //{
   //   // End battle
   //   battleCleanup(); // TODO Remove when unnecessary
   //   while (spriteQueue.size() > 1)
   //      spriteQueue.pop_back();
   //}
   //if (kbState[SDL_SCANCODE_I] && !kbPrevState[SDL_SCANCODE_I])
   //{
   //   // Kill all enemies
   //   // TODO Remove when unnecessary
   //   for (int i = 1; i < (int)spriteQueue.size(); i++)
   //      spriteQueue[i]->health = 0;

   //   dialogManager->battleResetDialog();
   //}
   //---------------------------------------------------------------//


   if (isBattleWon && dialogManager->dialogQueue->size() <= 2)
      battleCleanup();
}
/*-----------------------------------------------*/
void battleManager::checkBattle(BATTLE_TYPE battle)
{
   /* PURPOSE:		Determines probabilistically if battle should start
      RECEIVES:
      RETURNS:
      REMARKS:
      */

   //if (battle == battleManager::BATTLE_YES) // TODO Remove later
   //{
   //   currentBattle = battleManager::BATTLE_BOSS;
   //   initBattle();
   //}
   if (battle == BATTLE_BOSS)
   {
      currentBattle = battle;
      initBattle();
   }
   else if (rand() % 4 == 0)
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
   isPlayerAlive = true;
   isBattleWon = false;
   battleState = STATE_IDLE;
   totalLevel = 0;
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
   battlePlayer.health = player->stats["CON"] * 50;
   battlePlayer.maxHealth = battlePlayer.health;//player->maxHealth;
   battlePlayer.magic = player->stats["INT"] * 10;
   battlePlayer.maxMagic = battlePlayer.magic;
   battlePlayer.xp = player->xp;
   battlePlayer.level = player->level;
   battlePlayer.isDefending = false;
   battlePlayer.setAnimation("Idle");
   battlePlayer.isAlive = true;
   battlePlayer.updatePosition(battlePlayer.startX, battlePlayer.startY);
   battlePlayer.speedX = 0;
   battlePlayer.isFlippedX = false;

   spriteQueue.push_back(&battlePlayer);

   numEnemies = rand() % 3 + 1;

   std::string battle = "";

   if (currentBattle == BATTLE_EASY)
      battle = "battle_easy";
   else if (currentBattle == BATTLE_MEDIUM)
      battle = "battle_medium";
   else if (currentBattle == BATTLE_HARD)
      battle = "battle_hard";
   else if (currentBattle == BATTLE_BOSS)
      battle = "battle_boss";

   eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", battle));

   if (currentBattle == BATTLE_BOSS)
      numEnemies = 1;

   // Load enemies into spriteQueue for battle
   for (int i = 0; i < numEnemies; i++)
   {
      int numTypesEnemy = enemies[currentBattle].size();
      int choice = rand() % numTypesEnemy;

      BattleSprite* baseEnemy = enemies[currentBattle][choice];
      BattleSprite* enemy = baseEnemy->clone();
      *enemy = *baseEnemy;
      enemy->getNewUUID();
      enemy->registerListeners(eventQueue);
      enemy->targetUUID = spriteQueue[0]->getUUID();
      enemy->targetLevel = spriteQueue[0]->level;
      enemy->targetName = "link";
      enemy->opponentY = spriteQueue[0]->y;
      
      totalLevel += enemy->level;

      // Boost random stats based on level
      for (int i = 0; i < enemy->level; i++)
      {
         int choice = rand() % (int)statBoost.size();
         enemy->stats[statBoost[choice]]++;
      }
      spriteQueue.push_back(enemy);

      int staggerDistance = 75;
      // Stagger enemy positions
      if (i == 1)
      {
         BattleSprite* bSprite = spriteQueue[i + 1];
         bSprite->posY -= staggerDistance;
         bSprite->startY = bSprite->posY;
      }
      else if (i == 2)
      {
         BattleSprite* bSprite = spriteQueue[i + 1];
         bSprite->posY += staggerDistance;
         bSprite->startY = bSprite->posY;
      }
   }

   battleMenu.updateSize("enemy", numEnemies);
   battleMenu.updateSize("item", battlePlayer.items.size());
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

   //battlePlayer.health = battlePlayer.maxHealth;
   //battlePlayer.magic = battlePlayer.maxMagic;
   
   player->isAlive = true;
   
   if (isPlayerAlive)
      eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", previousLevel->name));

   isBattle = false;
   spriteQueue[0]->updatePosition(spriteQueue[0]->x, spriteQueue[0]->startY);

   // Write back items
   player->items = spriteQueue[0]->items;
   player->xp = spriteQueue[0]->xp;
   player->level = spriteQueue[0]->level;
   player->stats = spriteQueue[0]->stats;

   spriteQueue.clear();

   cam->x = prevCamX;
   cam->y = prevCamY;

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
      spriteQueue[i]->drawUV(cam->x, cam->y);
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

   // Low health for Link
   healthTimer -= ms;
   float alpha = ((float)spriteQueue[0]->health / (float)spriteQueue[0]->maxHealth);
   if (alpha > 0 && alpha < 0.10 && healthTimer <= 0)
   {
      healthTimer = 1000;
      eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "low_health"));
   }

   // End battle if player dead
   if (isPlayerAlive && spriteQueue[0]->health <= 0)
   {
      isPlayerAlive = false;

      dialogManager->battleResetDialog();
      dialogManager->updateBattleDialog(battleMenu);
   }

   for (int i = 0; i < (int)spriteQueue.size(); i++)
   {
      spriteQueue[i]->update(ms);

      // Remove enemy if dead
      if (i != 0)
      {
         // Reduce rewards if enemy flees
         BattleSprite* enemy = spriteQueue[i];
         if (enemy->state == BattleSprite::STATE_FLEE && enemy->isIdle())
         {
            numEnemies--;
            totalLevel -= enemy->level;
            enemy->isAlive = true;
            enemy->isRemovable = true;
         }

         if (spriteQueue[i]->isRemovable)
         {
            spriteQueue.erase(remove(spriteQueue.begin(), spriteQueue.end(), spriteQueue[i]));

            battleMenu.decrementEnemies();
         }
         if (spriteQueue.size() <= 1)
         {
            isBattleWon = true;
            battleWin();
         }
      }
   }

   // In case enemy was destroyed
   if (currentTurn < spriteQueue.size())
   {
      // Check if it's time for the next sprite to take it's turn.
      BattleSprite* player = spriteQueue[0];
      BattleSprite* currentSprite = spriteQueue[currentTurn];
      if (currentSprite->isIdle() && spriteQueue.size() > 0)
      {
         if (currentTurn != 0 && isEveryoneIdle() && player->curAnimation.def.name.compare("Flee") != 0) // TODO Remove once Link has a class and a takeTurn() setup
         {
            currentSprite->takeTurn();
            updateCurrentTurn();
         }
      }
   }
   else
      updateCurrentTurn();

   if (!isBattleWon && isPlayerAlive)
      dialogManager->updateBattleDialog(battleMenu);
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
   {
      currentTurn = 0;
   }
}
/*-----------------------------------------------*/
void battleManager::executeSelection()
{
   /* PURPOSE:    execute the current battleState selection
      RECEIVES:
      RETURNS:
      REMARKS:
      */

   bool isCanceled = false;

   BattleSprite* bPlayer = spriteQueue[0];
   // Fighting
   if (battleState == STATE_ENEMY)
   {
      int choice = battleMenu.getSelectedEnemy();
      bPlayer->targetUUID = spriteQueue[choice + 1]->getUUID();
      bPlayer->targetLevel = spriteQueue[choice + 1]->level;
      bPlayer->targetName = spriteQueue[choice + 1]->name;

      // Adjust to be on same track as enemy
      bPlayer->posY = spriteQueue[choice + 1]->posY;

      bPlayer->setAnimation("Attack");
   }
   else if (battleState == STATE_DEFEND)
   {
      bPlayer->isDefending = true;
      bPlayer->setAnimation("Defend");
   }
   else if (battleState == STATE_FLEE)
   {
      if ((rand() % 4) == 0)
      {
         bPlayer->setAnimation("Flee");
         bPlayer->isFlippedX = true;
         bPlayer->updatePosition(bPlayer->x - bPlayer->width + 50, bPlayer->y);
         bPlayer->speedX = -100;
      }
      //battleCleanup();
   }
   else if (battleState == STATE_ITEMS)
   {
      std::unordered_map<std::string, int>::iterator itr;
      itr = bPlayer->items.begin();

      int choice = battleMenu.getSelectedItem();
      for (int i = 0; i < choice; i++)
         itr++;

      if (itr->second > 0)
      {
         useItem(itr);
      }
      else
      {
         isCanceled = true;
      }
   }
   
   if (!isCanceled)
   {
      battleMenu.turnOff();
      battleState = STATE_IDLE;
      battleMenu.resetAll();
      updateCurrentTurn();
   }
}
/*-----------------------------------------------*/
void battleManager::useItem(std::unordered_map<std::string, int>::iterator itr)
{
   std::string item = itr->first;
   int* value = &itr->second;

   if (item.compare("Rupees") == 0)
   {
      int damage = (int)ceil(*value / numEnemies);
      (*value) = 0;
      for (int i = 1; i < (int)spriteQueue.size(); i++)
      {
         Event ev = Event(Event::ET_DAMAGE, "subject", spriteQueue[i]->getUUID());
         ev.numParams["damage"] = damage;
         eventQueue->queueEvent(ev);

         eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "rupee"));
      }
   }

   if (item.compare("Red Potion") == 0 || item.compare("Green Potion") == 0)
   {
      int maxHealth = spriteQueue[0]->maxHealth;
      int newHealth = spriteQueue[0]->health + (int)floor(maxHealth / 2);

      if (newHealth > maxHealth)
         spriteQueue[0]->health = maxHealth;
      else
         spriteQueue[0]->health = newHealth;

      eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "refill_health"));
   }
   if (item.compare("Blue Potion") == 0 || item.compare("Green Potion") == 0)
   {
      int maxMagic = spriteQueue[0]->maxMagic;
      int newMagic = spriteQueue[0]->magic + (int)floor(maxMagic / 2);
      if (newMagic > maxMagic)
         spriteQueue[0]->magic = maxMagic;
      else
         spriteQueue[0]->magic = newMagic;

      eventQueue->queueEvent(Event(Event::ET_SOUND, "soundFX", "magic"));
   }
}
/*-----------------------------------------------*/
void battleManager::playerDeath()
{
   /* PURPOSE:    Handles resetting if player dies
      RECEIVES:
      RETURNS:
      REMARKS:
      */

   battleCleanup();
   eventQueue->queueEvent(Event(Event::ET_RESTART));

   // Make sure the dialog sequence is retriggered
   if (player::isFinalBattle)
      player::isFinalBattle = false;
}
/*-----------------------------------------------*/
void battleManager::battleWin()
{
   /* PURPOSE:    When the battle is over, doles out rewards
      RECEIVES:
      RETURNS:
      REMARKS:
      */

   if (currentBattle == BATTLE_BOSS)
      player->isGanonDefeated = true;

   eventQueue->queueEvent(Event(Event::ET_BATTLE_WIN));

   BattleSprite* bPlayer = spriteQueue[0];
   bPlayer->setAnimation("Win");

   std::unordered_map<std::string, int> tempReward;
   std::vector<std::string> rewards;

   // Decide rewards
   int numLoots = loot[currentBattle].size();

   for (int i = 0; i < numEnemies; i++)
   {
      int numReward = rand() % 2;

      if (numReward == 1)
      {
         int choice = rand() % numLoots;
         std::string s = loot[currentBattle][choice];

         tempReward[s]++;
      }
   }

   // Update player
   std::unordered_map<std::string, int>::iterator itr;

   // Rupee Rewards
   int rupees = numEnemies * 10;

   for (itr = tempReward.begin(); itr != tempReward.end(); itr++)
   {
      // Rupees
      if (itr->first.compare("Rupees") == 0)
      {
         rupees += itr->second * 10;
      }
      else
      {
         // Other items
         bPlayer->items[itr->first] += itr->second;
         rewards.push_back("Found " + itr->first + " x" + std::to_string(itr->second));
      }
   }
   bPlayer->items["Rupees"] += rupees;

   if (rupees > 0)
      rewards.push_back("Found " + std::to_string(rupees) + " Rupees");

   // XP Rewards

   int xpGained = totalLevel * 20;
   bPlayer->xp += xpGained;

   // Check for LevelUp
   if (bPlayer->xp >= player->xpToNextLevel[bPlayer->level - 1])
   {
      bPlayer->level++;
      bPlayer->stats["STR"]++; // TODO Remove once Stat Picker is done
      bPlayer->stats["CON"]++; // TODO Remove once Stat Picker is done
      bPlayer->stats["DEX"]++; // TODO Remove once Stat Picker is done
      bPlayer->stats["INT"]++; // TODO Remove once Stat Picker is done
      bPlayer->stats["LCK"]++; // TODO Remove once Stat Picker is done
      rewards.push_back(player->name + " Leveled Up to Lv. " + std::to_string(bPlayer->level) + "!");
   }

   if (xpGained > 0)
      rewards.push_back("Got " + std::to_string(xpGained) + " XP");

   dialogManager->battleRewards(rewards);
}
/*-----------------------------------------------*/
bool battleManager::isEveryoneIdle()
{
   // Test to make sure all sprites are idle
   bool isEveryoneIdle = true;
   for (int i = 0; i < spriteQueue.size(); i++)
   {
      if (isEveryoneIdle)
         isEveryoneIdle = spriteQueue[i]->isIdle();
   }

   return isEveryoneIdle;
}
/*-----------------------------------------------*/