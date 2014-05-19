#include "player.h"
#include "battleManager.h"

//enum {IDLE, WALKING, RUN_SHOOTING, JUMPING, PRONE, PRONE_SHOOTING, IDLE_SHOOT, WALKING_GUN_UP, WALKING_GUN_DOWN, DEATH};
enum { IDLE, WALKING_UP, WALKING_DOWN, WALKING_LEFT_RIGHT, WALKING_DIAG_UP, WALKING_DIAG_DOWN, DEATH };
enum { LEFT, RIGHT, TOP, BOTTOM };

EventQueue* player::eventQueue;
int player::timeBetweenBattles = 5000;
int player::timeSinceLastBattle = 0;
bool player::isBattleReady = false;
int player::timeBetweenDialogs = 1000;
int player::timeSinceLastDialog = 0;
bool player::isDialogReady = false;
bool* player::isInputRequired;
bool player::isGameOver = false;

PlayerSprite player::makePlayer(GLuint* texture, int textureWidth, int textureHeight, EventQueue* evQueue, bool* isInputRequired)
{
   /* PURPOSE:		Sets up player sprite for this game
   RECEIVES:	texture - OpenGl texture to use when drawing player
   textureWidth - Width of texture
   textureHeight - Height of texture
   RETURNS:		PlayerSprite object corresponding to the player
   REMARKS:		Sets up collider and animations of player
   */

   player::eventQueue = evQueue;
   player::isInputRequired = isInputRequired;

   PlayerSprite player;
   float cellSize = 32;
   float uSize = 1 / (textureWidth / cellSize);
   float vSize = 1 / (textureHeight / cellSize);
   int health = 100;

   player = PlayerSprite(texture, 0, 0, 65, 65,
      0, 8 * vSize, 2 * uSize, 3 * vSize, health);
   player.maxSpeedX = 175;
   player.maxSpeedY = 175;
   //player.jumpSpeed = -300;
   //player.jumpTicks = 200;
   player.name = "Link";
   player.maxHealth = 100;
   player.magic = 10;
   player.maxMagic = 10;
   player.items["Rupees"] = 1;

   //Setup Collider
   int xOffset = 20;
   int yOffset = 45;
   int width = 25;
   int height = 8;
   player.colliderXOffset = xOffset;
   player.colliderYOffset = yOffset;
   player.setCollider(&AABB(player.x + xOffset, player.y + yOffset, width, height));
   player.isColliderDrawn = false;


   // Animations
   int numFrames = 1;
   int timeToNextFrame = 100;

   // Idle Animation
   //AnimationFrame* frames_idle = new AnimationFrame[numFrames];
   std::vector<AnimationFrame> frames;
   frames.assign(numFrames, AnimationFrame());
   frames[0] = AnimationFrame(0 * uSize, 16 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_idle = Animation("Idle", frames, numFrames);
   player.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

   // Walking Down Animation
   numFrames = 7;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(1 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(2 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(3 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(4 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(5 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames[6] = AnimationFrame(6 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingDown = Animation("Walking Down", frames, numFrames);
   player.animations[animation_walkingDown.name] = AnimationData(animation_walkingDown, timeToNextFrame, true);

   // Walking Up Animation
   numFrames = 6;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(1 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(2 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(3 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(4 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(5 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingUp = Animation("Walking Up", frames, numFrames);
   player.animations[animation_walkingUp.name] = AnimationData(animation_walkingUp, timeToNextFrame, true);

   // Walking Left & Right Animation
   numFrames = 6;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(1 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(2 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(3 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(4 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(5 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingLR = Animation("Walking LR", frames, numFrames);
   player.animations[animation_walkingLR.name] = AnimationData(animation_walkingLR, timeToNextFrame, true);

   // Walking Diag facing down animation
   numFrames = 5;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(1 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(2 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(3 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(4 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingDiagDown = Animation("Walking DiagDown", frames, numFrames);
   player.animations[animation_walkingDiagDown.name] = AnimationData(animation_walkingDiagDown, timeToNextFrame, true);

   // Walking Diag facing up animation
   numFrames = 6;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(0 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[1] = AnimationFrame(1 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[2] = AnimationFrame(2 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[3] = AnimationFrame(3 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[4] = AnimationFrame(4 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames[5] = AnimationFrame(5 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingDiagUp = Animation("Walking DiagUp", frames, numFrames);
   player.animations[animation_walkingDiagUp.name] = AnimationData(animation_walkingDiagUp, timeToNextFrame, true);

   // Death Animation -- This animation isn't on the sheet yet.
   numFrames = 2;
   timeToNextFrame = 150;
   frames.clear();
   frames.assign(numFrames, AnimationFrame());

   frames[0] = AnimationFrame(21 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
   frames[1] = AnimationFrame(24 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
   Animation animation_death = Animation("Death", frames, numFrames);
   player.animations[animation_death.name] = AnimationData(animation_death, timeToNextFrame, false);

   // Initialize animation and return
   player.setAnimation("Idle");
   return player;
}
/*-----------------------------------------------*/
void player::playerKeyboard(PlayerSprite* player, const unsigned char* kbState, unsigned char* kbPrevState)
{
   /* PURPOSE:		State machine to handle keyboard inputs by user
   RECEIVES:	player - Sprite object of player
   kbState - Current keyboard state
   kbPrevState - Previous keyboard state
   RETURNS:
   REMARKS:
   */

   // Player Direction
   if (player->state != DEATH)
   {
      if (kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_D])
      {
         player->speedX = player->maxSpeedX;
         player->isFlippedX = true;
         player->speedX *= -1;
      }
      if (kbState[SDL_SCANCODE_D] & !kbState[SDL_SCANCODE_A])
      {
         player->speedX = player->maxSpeedX;
         player->isFlippedX = false;
      }
      if (kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_S])
      {
         player->speedY = player->maxSpeedY;
         player->speedY *= -1;
      }
      if (kbState[SDL_SCANCODE_S] & !kbState[SDL_SCANCODE_W])
      {
         player->speedY = player->maxSpeedY;
      }
      if (kbState[SDL_SCANCODE_A] & kbState[SDL_SCANCODE_D])
         player->speedX = 0;
      if (kbState[SDL_SCANCODE_W] & kbState[SDL_SCANCODE_S])
         player->speedY = 0;

      if (!kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D])
         player->speedX = 0;
      if (!kbState[SDL_SCANCODE_W] && !kbState[SDL_SCANCODE_S])
         player->speedY = 0;
   }

   bool isIdle = (kbState[SDL_SCANCODE_W] | kbState[SDL_SCANCODE_A] | kbState[SDL_SCANCODE_S] |
      kbState[SDL_SCANCODE_D] | kbState[SDL_SCANCODE_J] | kbState[SDL_SCANCODE_SPACE]) != 1;
   bool isWalkingLeft = (kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_D] & !kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_S]) == 1;
   bool isWalkingRight = (kbState[SDL_SCANCODE_D] & !kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_S]) == 1;
   bool isWalkingUp = (kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_S] & !kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_D]) == 1;
   bool isWalkingDown = (kbState[SDL_SCANCODE_S] & !kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_D]) == 1;

   bool isWalkingUpLeft = (kbState[SDL_SCANCODE_W] & kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_S] & !kbState[SDL_SCANCODE_D]) == 1;
   bool isWalkingUpRight = (kbState[SDL_SCANCODE_W] & kbState[SDL_SCANCODE_D] & !kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_S]) == 1;
   bool isWalkingDownLeft = (kbState[SDL_SCANCODE_S] & kbState[SDL_SCANCODE_A] & !kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_D]) == 1;
   bool isWalkingDownRight = (kbState[SDL_SCANCODE_S] & kbState[SDL_SCANCODE_D] & !kbState[SDL_SCANCODE_W] & !kbState[SDL_SCANCODE_A]) == 1;

   if (isWalkingUpLeft || isWalkingUpRight || isWalkingDownLeft || isWalkingDownRight)
   {
      player->speedX *= .75;
      player->speedY *= .75;
   }


   // Player States
   // IDLE State
   if (player->state == IDLE)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = false;

         //player->setAnimation("Idle");
         player->prevState = player->state;

         player->speedX = 0;
         player->speedY = 0;
      }

      // Check for new Transition
      if (isWalkingLeft || isWalkingRight)
         player->state = WALKING_LEFT_RIGHT;
      else if (isWalkingUp)
         player->state = WALKING_UP;
      else if (isWalkingDown)
         player->state = WALKING_DOWN;
      else if (isWalkingUpRight || isWalkingUpLeft)
         player->state = WALKING_DIAG_UP;
      else if (isWalkingDownRight || isWalkingDownLeft)
         player->state = WALKING_DIAG_DOWN;
   }

   // WALKING_DOWN State
   else if (player->state == WALKING_DOWN)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = true;
         player->setAnimation("Walking Down");
         player->prevState = player->state;
      }

      // Check for new Transition
      if (isIdle)
      {
         player->setCurrentFrame(0);
         player->isAnimated = false;
         player->state = IDLE;
      }
      else if (isWalkingLeft || isWalkingRight)
         player->state = WALKING_LEFT_RIGHT;
      else if (isWalkingUp)
         player->state = WALKING_UP;
      else if (isWalkingUpRight || isWalkingUpLeft)
         player->state = WALKING_DIAG_UP;
      else if (isWalkingDownRight || isWalkingDownLeft)
         player->state = WALKING_DIAG_DOWN;
   }

   // WALKING_UP State
   else if (player->state == WALKING_UP)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = true;
         player->setAnimation("Walking Up");
         player->prevState = player->state;
      }

      // Check for new Transition
      if (isIdle)
      {
         player->setCurrentFrame(1);
         player->isAnimated = false;
         player->state = IDLE;
      }
      else if (isWalkingLeft || isWalkingRight)
         player->state = WALKING_LEFT_RIGHT;
      else if (isWalkingDown)
         player->state = WALKING_DOWN;
      else if (isWalkingUpRight || isWalkingUpLeft)
         player->state = WALKING_DIAG_UP;
      else if (isWalkingDownRight || isWalkingDownLeft)
         player->state = WALKING_DIAG_DOWN;
   }

   // WALKING_LEFT_RIGHT State
   else if (player->state == WALKING_LEFT_RIGHT)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = true;
         player->setAnimation("Walking LR");
         player->prevState = player->state;
      }

      // Check for new Transition
      if (isIdle)
      {
         player->setCurrentFrame(1);
         player->isAnimated = false;
         player->state = IDLE;
      }
      else if (isWalkingDown)
         player->state = WALKING_DOWN;
      else if (isWalkingUp)
         player->state = WALKING_UP;
      else if (isWalkingUpRight || isWalkingUpLeft)
         player->state = WALKING_DIAG_UP;
      else if (isWalkingDownRight || isWalkingDownLeft)
         player->state = WALKING_DIAG_DOWN;
   }

   // WALKING_DIAG_UP State
   else if (player->state == WALKING_DIAG_UP)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = true;
         player->setAnimation("Walking DiagUp");
         player->prevState = player->state;
      }

      // Check for new Transition
      if (isIdle)
      {
         player->setCurrentFrame(2);
         player->isAnimated = false;
         player->state = IDLE;
      }
      else if (isWalkingLeft || isWalkingRight)
         player->state = WALKING_LEFT_RIGHT;
      else if (isWalkingDown)
         player->state = WALKING_DOWN;
      else if (isWalkingUp)
         player->state = WALKING_UP;
      else if (isWalkingDownRight || isWalkingDownLeft)
         player->state = WALKING_DIAG_DOWN;
   }

   // WALKING_DIAG_DOWN State
   else if (player->state == WALKING_DIAG_DOWN)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->isAnimated = true;
         player->setAnimation("Walking DiagDown");
         player->prevState = player->state;
      }

      // Check for new Transition
      if (isIdle)
      {
         player->setCurrentFrame(0);
         player->isAnimated = false;
         player->state = IDLE;
      }
      else if (isWalkingLeft || isWalkingRight)
         player->state = WALKING_LEFT_RIGHT;
      else if (isWalkingDown)
         player->state = WALKING_DOWN;
      else if (isWalkingUp)
         player->state = WALKING_UP;
      else if (isWalkingUpRight || isWalkingUpLeft)
         player->state = WALKING_DIAG_UP;
   }

   // Death State
   else if (player->state == DEATH)
   {
      // Handle State Transition
      if (player->state != player->prevState)
      {
         player->setAnimation("Death");
         player->prevState = player->state;

         eventQueue->queueEvent(Event(Event::ET_DEATH, "subject", "player"));

         /*player->isJumping = true;
         if (player->speedX >= 0)
         player->speedX = -200;
         else
         player->speedX = 200;
         player->speedY = -300;*/
      }

      /*if (!player->isJumping)
      player->speedX = 0;*/
   }

   // Debug for State
   if (0)
   {
      if (player->state != player->prevState)
      {
         std::cout << "prevState = " << player->prevState << std::endl;
         std::cout << "state = " << player->state << std::endl;
      }
   }
}
/*-----------------------------------------------*/
void player::updatePhysics(PlayerSprite* player, int diff_time)
{
   /* PURPOSE:		Handles physics updates for player sprite
      RECEIVES:	player - Sprite object of player
      diff_time - milliseconds since last frame
      RETURNS:
      REMARKS:
      */

   // Timer for battle rest periods
   if (!isBattleReady && !battleManager::isBattle)
   {
      timeSinceLastBattle += diff_time;
      if (timeSinceLastBattle > timeBetweenBattles)
      {
         timeSinceLastBattle = 0;
         isBattleReady = true;
      }
   }

   // Timer for dialog to prevent double dialoging
   if (!isDialogReady)
   {
      timeSinceLastDialog += diff_time;
      if (timeSinceLastDialog > timeBetweenDialogs)
      {
         timeSinceLastDialog = 0;
         isDialogReady = true;
      }
   }
}
/*-----------------------------------------------*/
void player::collisionResolution(PlayerSprite* player, Sprite* sprite, const unsigned char* kbState, unsigned char* kbPrevState)
{
   /* PURPOSE:		Handles collision based resolutions of sprites
   RECEIVES:	player - Sprite object of player
   sprite - Sprite object player collided with
   RETURNS:
   REMARKS:
   */


   static bool isFinalBattle = false;
   static bool isZeldaFinished = false;

   // Debug Collision Type
   if (0)
      std::cout << "Collision Type = " << sprite->type << std::endl;

   bool* sides = AABB::AABBwhichSideIntersected(&player->prevCollider, &player->collider, &sprite->collider);

   // Ground Collision
   if (sprite->type == enumLibrary::COLLISION::GROUND || (sprite->type == enumLibrary::COLLISION::VILLAGER && !player->hasSword))
   {

      if (sides[TOP])
      {
         player->speedY = 0;
         int newY = (sprite->collider.y - 1) - (player->collider.h + player->colliderYOffset);
         player->updatePosition(player->posX, (float)newY);
      }
      else if (sides[BOTTOM])
      {
         player->speedY = 0;
         int newY = (sprite->collider.y + 1) + sprite->collider.h - player->colliderYOffset;
         player->updatePosition(player->posX, (float)newY);
      }
      else if (sides[LEFT])
      {
         player->speedX = 0;
         int newX = (sprite->collider.x - 1) - (player->colliderXOffset + player->collider.w);
         player->updatePosition((float)newX, player->posY);
      }
      else if (sides[RIGHT])
      {
         player->speedX = 0;
         int newX = (sprite->collider.x + sprite->collider.w + 1) - player->colliderXOffset;
         player->updatePosition((float)newX, player->posY);
      }
      player->updateCamera();
   }

   // Handle Trigger events
   if (kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J])
      sprite->onTrigger();

   if (sprite->type == enumLibrary::COLLISION::BATTLE_BOSS && player->isGanonDefeated)
      sprite->isVisible = false;

   // Only resolve onCollisionEnter and not onCollisionStay
   if (!sprite->hasCollided)
   {
      // Handle sprite based collision logic
      sprite->onCollision();

      if (sprite->type == enumLibrary::COLLISION::END)
      {
         //std::cout << "You Win" << std::endl;
      }
      if (sprite->type == enumLibrary::COLLISION::DEATH)
      {
         //player->state = DEATH;
      }
      if (sprite->type == enumLibrary::COLLISION::VILLAGER)
      {
         if (kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J])
         {
            if (!player->hasSword)
            {
               Event ev = Event(Event::ET_COLLISION_START, "dialog", "guard_warning");
               eventQueue->queueEvent(ev);

               player->speedX = 0;
               player->updatePosition(player->posX - 3, player->posY);
               player->updateCamera();
            }
            else
            {
               Event ev = Event(Event::ET_COLLISION_START, "dialog", "guard_talk");
               eventQueue->queueEvent(ev);
            }
         }
         else if (isDialogReady)
         {
            if (!player->hasSword)
            {
               Event ev = Event(Event::ET_COLLISION_START, "dialog", "guard_dangerous");
               eventQueue->queueEvent(ev);
               isDialogReady = false;

               player->speedX = 0;
               player->updatePosition(player->posX - 3, player->posY);
               player->updateCamera();
            }
            else if (player->level < 5)
            {
               Event ev = Event(Event::ET_COLLISION_START, "dialog", "guard_weak");
               eventQueue->queueEvent(ev);
               isDialogReady = false;
            }
         }
      }
      if (sprite->type == enumLibrary::COLLISION::DUNGEON_1)
      {
         eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", "dungeon_1"));
      }
      else if (sprite->type == enumLibrary::COLLISION::OVERWORLD)
      {
         eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", "overworld"));
      }
      if (sprite->type == enumLibrary::COLLISION::CASTLE)
      {
         eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", "castle"));
      }
      else if (sprite->type == enumLibrary::COLLISION::OVERWORLD)
      {
         eventQueue->queueEvent(Event(Event::ET_LEVEL_LOAD, "level", "overworld"));
      }

      if (isBattleReady && player->hasSword)
      {
         if (sprite->type == enumLibrary::COLLISION::BATTLE_EASY)
         {
            battleManager::checkBattle(battleManager::BATTLE_EASY);
         }
         else if (sprite->type == enumLibrary::COLLISION::BATTLE_MEDIUM)
         {
            battleManager::checkBattle(battleManager::BATTLE_MEDIUM);
         }
         else if (sprite->type == enumLibrary::COLLISION::BATTLE_HARD)
         {
            battleManager::checkBattle(battleManager::BATTLE_HARD);
         }

         if (battleManager::isBattle)
            isBattleReady = false;
      }
      
      if (!*isInputRequired && !isFinalBattle && sprite->type == enumLibrary::COLLISION::BATTLE_BOSS && !player->isGanonDefeated)
      {
         isFinalBattle = true;

         Event ev = Event(Event::ET_COLLISION_START, "dialog", "ganon_finale");
         eventQueue->queueEvent(ev);
         isDialogReady = false;
      }

      if (!*isInputRequired && !isGameOver && sprite->type == enumLibrary::COLLISION::ZELDA && player->isGanonDefeated)
      {
         Event ev = Event(Event::ET_COLLISION_START, "dialog", "zelda");
         eventQueue->queueEvent(ev);
         ev = Event(Event::ET_SOUND, "music", "princess_zeldas_rescue");
         eventQueue->queueEvent(ev);
         
         isDialogReady = false;
         isZeldaFinished = true;
      }

   }
   sprite->hasCollided = true;

   if (isDialogReady && !*isInputRequired && isFinalBattle && sprite->type == enumLibrary::COLLISION::BATTLE_BOSS && !player->isGanonDefeated)
   {
      battleManager::checkBattle(battleManager::BATTLE_BOSS);
   }

   if (isDialogReady && isZeldaFinished && sprite->type == enumLibrary::COLLISION::ZELDA && player->isGanonDefeated)
   {
      isGameOver = true;
   }
}
/*-----------------------------------------------*/
void player::restartPlayer(PlayerSprite* player, int x, int y)
{
   /* PURPOSE:		Resets player to starting position and state
   RECEIVES:	player - Sprite object of player
   x - Horizontal position to start at
   y - Vertical position to start at
   RETURNS:
   REMARKS:
   */

   player->setAnimation("Idle");
   player->isAlive = true;
   player->state = IDLE;
   player->isFlippedX = false;
   player->health = 100;
   player->isJumping = false;
   player->setSpeed(0, 0);
   player->updatePosition((float)x, (float)y - player->height);
}
/*-----------------------------------------------*/
void player::stopPlayer(PlayerSprite* player)
{
   /* PURPOSE:		Stops player for use in Battle System
      RECEIVES:	player - Sprite object of player
      RETURNS:
      REMARKS:
      */

   player->isAnimated = false;
   player->prevState = player->state;
   player->speedX = 0;
   player->speedY = 0;
   player->state = IDLE;
}