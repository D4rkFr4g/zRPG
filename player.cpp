#include "player.h"

//enum {IDLE, WALKING, RUN_SHOOTING, JUMPING, PRONE, PRONE_SHOOTING, IDLE_SHOOT, WALKING_GUN_UP, WALKING_GUN_DOWN, DEATH};
enum { IDLE, WALKING_UP, WALKING_DOWN, WALKING_LEFT_RIGHT, WALKING_DIAG_UP, WALKING_DIAG_DOWN, DEATH };
enum { COLLISION_NULL, COLLISION_GROUND, COLLISION_DEATH, COLLISION_PLATFORM, COLLISION_START, COLLISION_END, BATTLE_EASY,
   BATTLE_MEDIUM, BATTLE_HARD};
enum { LEFT, RIGHT, TOP, BOTTOM };

EventQueue* player::eventQueue;

PlayerSprite player::makePlayer(GLuint* texture, int textureWidth, int textureHeight, EventQueue* evQueue)
{
   /* PURPOSE:		Sets up player sprite for this game
   RECEIVES:	texture - OpenGl texture to use when drawing player
   textureWidth - Width of texture
   textureHeight - Height of texture
   RETURNS:		PlayerSprite object corresponding to the player
   REMARKS:		Sets up collider and animations of player
   */

   player::eventQueue = evQueue;

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
   AnimationFrame* frames_idle = new AnimationFrame[numFrames];
   frames_idle[0] = AnimationFrame(0 * uSize, 16 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_idle = Animation("Idle", frames_idle, numFrames);
   player.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

   // Walking Down Animation
   numFrames = 7;
   AnimationFrame* frames_walkingDown = new AnimationFrame[numFrames];
   frames_walkingDown[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[1] = AnimationFrame(1 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[2] = AnimationFrame(2 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[3] = AnimationFrame(3 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[4] = AnimationFrame(4 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[5] = AnimationFrame(5 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDown[6] = AnimationFrame(6 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingDown = Animation("Walking Down", frames_walkingDown, numFrames);
   player.animations[animation_walkingDown.name] = AnimationData(animation_walkingDown, timeToNextFrame, true);

   // Walking Up Animation
   numFrames = 6;
   AnimationFrame* frames_walkingUp = new AnimationFrame[numFrames];
   frames_walkingUp[0] = AnimationFrame(0 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingUp[1] = AnimationFrame(1 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingUp[2] = AnimationFrame(2 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingUp[3] = AnimationFrame(3 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingUp[4] = AnimationFrame(4 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingUp[5] = AnimationFrame(5 * uSize, 17 * vSize, 1 * uSize, 1 * vSize);
   Animation animation_walkingUp = Animation("Walking Up", frames_walkingUp, numFrames);
   player.animations[animation_walkingUp.name] = AnimationData(animation_walkingUp, timeToNextFrame, true);

   // Walking Left & Right Animation
   numFrames = 6;
   AnimationFrame* frames_walkingLR = new AnimationFrame[numFrames];
   frames_walkingLR[0] = AnimationFrame(0 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingLR[1] = AnimationFrame(1 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingLR[2] = AnimationFrame(2 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingLR[3] = AnimationFrame(3 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingLR[4] = AnimationFrame(4 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingLR[5] = AnimationFrame(5 * uSize, 18 * vSize, 1 * uSize, 1 * vSize);

   Animation animation_walkingLR = Animation("Walking LR", frames_walkingLR, numFrames);
   player.animations[animation_walkingLR.name] = AnimationData(animation_walkingLR, timeToNextFrame, true);

   // Walking Diag facing down animation
   numFrames = 5;
   AnimationFrame* frames_walkingDiagDown = new AnimationFrame[numFrames];
   frames_walkingDiagDown[0] = AnimationFrame(0 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagDown[1] = AnimationFrame(1 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagDown[2] = AnimationFrame(2 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagDown[3] = AnimationFrame(3 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagDown[4] = AnimationFrame(4 * uSize, 5 * vSize, 1 * uSize, 1 * vSize);

   Animation animation_walkingDiagDown = Animation("Walking DiagDown", frames_walkingDiagDown, numFrames);
   player.animations[animation_walkingDiagDown.name] = AnimationData(animation_walkingDiagDown, timeToNextFrame, true);

   // Walking Diag facing up animation
   numFrames = 6;
   AnimationFrame* frames_walkingDiagUp = new AnimationFrame[numFrames];
   frames_walkingDiagUp[0] = AnimationFrame(0 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagUp[1] = AnimationFrame(1 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagUp[2] = AnimationFrame(2 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagUp[3] = AnimationFrame(3 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagUp[4] = AnimationFrame(4 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);
   frames_walkingDiagUp[5] = AnimationFrame(5 * uSize, 14 * vSize, 1 * uSize, 1 * vSize);

   Animation animation_walkingDiagUp = Animation("Walking DiagUp", frames_walkingDiagUp, numFrames);
   player.animations[animation_walkingDiagUp.name] = AnimationData(animation_walkingDiagUp, timeToNextFrame, true);

   // Death Animation
   numFrames = 2;
   timeToNextFrame = 150;
   AnimationFrame* frames_death = new AnimationFrame[numFrames];
   frames_death[0] = AnimationFrame(21 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
   frames_death[1] = AnimationFrame(24 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
   Animation animation_death = Animation("Death", frames_death, numFrames);
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

   //float gravity = (float) 0;

   // Gravity effect
   //player->speedY = player->speedY + gravity;

   // JumpingTicks Adjustment
   //if (player->state == JUMPING && player->jumpTicksRemaining > 0)
   //player->jumpTicksRemaining -= diff_time;
}
/*-----------------------------------------------*/
void player::collisionResolution(PlayerSprite* player, Sprite* sprite)
{
   /* PURPOSE:		Handles collision based resolutions of sprites
   RECEIVES:	player - Sprite object of player
   sprite - Sprite object player collided with
   RETURNS:
   REMARKS:
   */

   // Debug Collision Type
   if (0)
      std::cout << "Collision Type = " << sprite->type << std::endl;

   bool* sides = AABB::AABBwhichSideIntersected(&player->prevCollider, &player->collider, &sprite->collider);

   // Ground Collision
   if (sprite->type == COLLISION_GROUND || sprite->type == COLLISION_PLATFORM)
   {

      if (sides[TOP])
      {
         player->isJumping = false;
         player->speedY = 0;
         int newY = (sprite->collider.y - 1) - (player->collider.h + player->colliderYOffset);
         player->updatePosition(player->posX, (float)newY);
      }
      else if (sides[BOTTOM])
      {
         player->isJumping = false;
         player->speedY = 0;
         int newY = (sprite->collider.y + 1) + sprite->collider.h - player->colliderYOffset;
         player->updatePosition(player->posX, (float)newY);
      }


      if (sprite->type == COLLISION_GROUND)
      {
         if (sides[LEFT])
         {
            player->speedX = 0;
            int newX = (sprite->collider.x - 1) - (player->collider.w + player->colliderXOffset);
            player->updatePosition((float)newX, player->posY);
         }
         else if (sides[RIGHT])
         {
            player->speedX = 0;
            int newX = (sprite->collider.x + 1) + sprite->collider.w - player->colliderXOffset;
            player->updatePosition((float)newX, player->posY);
         }
         /*
         else if (sides[TOP])
         {
         player->isJumping = false;
         player->speedY = 0;
         int newY = (sprite->colliderYOffset - 1) - player->height;
         player->updatePosition(player->posX, (float) newY);
         }
         */
      }
   }
   if (sprite->type == COLLISION_END)
      std::cout << "You Win" << std::endl;
   if (sprite->type == COLLISION_DEATH)
   {
      player->state = DEATH;
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