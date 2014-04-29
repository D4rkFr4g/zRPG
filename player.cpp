#include "player.h"

//enum {IDLE, WALKING, RUN_SHOOTING, JUMPING, PRONE, PRONE_SHOOTING, IDLE_SHOOT, WALKING_GUN_UP, WALKING_GUN_DOWN, DEATH};
enum {IDLE, WALKING_UP, WALKING_DOWN, WALKING_LEFT, WALKING_RIGHT, WALKING_UP_LEFT, WALKING_UP_RIGHT, WALKING_DOWN_LEFT,
	WALKING_DOWN_RIGHT, DEATH};
enum {COLLISION_NULL, COLLISION_GROUND, COLLISION_DEATH, COLLISION_PLATFORM, COLLISION_START, COLLISION_END};
enum {LEFT, RIGHT, TOP, BOTTOM};

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

	player = PlayerSprite(texture, 0, 0, 80, 80, 
		0, 8 * vSize, 2 * uSize , 3 * vSize, health);
	player.maxSpeedX = 100;
	player.maxSpeedY = 100;
	//player.jumpSpeed = -300;
	//player.jumpTicks = 200;

	//Setup Collider
	int xOffset = 27;
	int yOffset = 40;
	int width = 25;
	int height = 25;
	player.colliderXOffset = xOffset;
	player.colliderYOffset = yOffset;
	player.setCollider(&AABB(player.x + xOffset, player.y + yOffset, width, height));
   player.isColliderDrawn = false;


   // Animations
	int numFrames = 1;
	int timeToNextFrame = 200;

	// Idle Animation
	AnimationFrame* frames_idle = new AnimationFrame[numFrames];
	frames_idle[0] = AnimationFrame(0 * uSize, 16 * vSize, 1 * uSize, 1 * vSize);
	Animation animation_idle = Animation("Idle", frames_idle, numFrames);
	player.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

	// Walking Down Animation
	numFrames = 8;
	AnimationFrame* frames_walkingDown = new AnimationFrame[numFrames];
	frames_walkingDown[0] = AnimationFrame(0 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[1] = AnimationFrame(1 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[2] = AnimationFrame(2 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[3] = AnimationFrame(3 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[4] = AnimationFrame(4 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[5] = AnimationFrame(5 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[6] = AnimationFrame(6 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
	frames_walkingDown[7] = AnimationFrame(7 * uSize, 19 * vSize, 1 * uSize, 1 * vSize);
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

	Animation animation_walkingLeft = Animation("Walking Left", frames_walkingLR, numFrames);
	player.animations[animation_walkingLeft.name] = AnimationData(animation_walkingLeft, timeToNextFrame, true);
	Animation animation_walkingRight = Animation("Walking Right", frames_walkingLR, numFrames);
	player.animations[animation_walkingRight.name] = AnimationData(animation_walkingRight, timeToNextFrame, true);

	// Walking Animation
	/*
	numFrames = 4;
	AnimationFrame* frames_walking = new AnimationFrame[numFrames];
	frames_walking[0] = AnimationFrame(0 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[1] = AnimationFrame(3 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[2] = AnimationFrame(6 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[3] = AnimationFrame(9 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walking = Animation("Walking", frames_walking, numFrames);
	player.animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);
	*/

	// WalkingGunUp Animation
	/*
	numFrames = 4;
	AnimationFrame* frames_walkingGunUp = new AnimationFrame[numFrames];
	frames_walkingGunUp[0] = AnimationFrame(0 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[1] = AnimationFrame(3 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[2] = AnimationFrame(6 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[3] = AnimationFrame(9 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walkingGunUp = Animation("WalkingGunUp", frames_walkingGunUp, numFrames);
	player.animations[animation_walkingGunUp.name] = AnimationData(animation_walkingGunUp, timeToNextFrame, true);
	*/

	// WalkingGunDown Animation
	/*
	numFrames = 4;
	AnimationFrame* frames_walkingGunDown = new AnimationFrame[numFrames];
	frames_walkingGunDown[0] = AnimationFrame(12 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[1] = AnimationFrame(15 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[2] = AnimationFrame(18 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[3] = AnimationFrame(21 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walkingGunDown = Animation("WalkingGunDown", frames_walkingGunDown, numFrames);
	player.animations[animation_walkingGunDown.name] = AnimationData(animation_walkingGunDown, timeToNextFrame, true);
	*/

	// Jumping Animation
	/*
	numFrames = 4;
	AnimationFrame* frames_jumping = new AnimationFrame[numFrames];
	frames_jumping[0] = AnimationFrame(9 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[1] = AnimationFrame(12 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[2] = AnimationFrame(15 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[3] = AnimationFrame(18 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_jumping = Animation("Jumping", frames_jumping, numFrames);
	player.animations[animation_jumping.name] = AnimationData(animation_jumping, timeToNextFrame, true);
	*/
	
	// Prone Animation
	/*
	numFrames = 1;
	AnimationFrame* frames_prone = new AnimationFrame[numFrames];
	frames_prone[0] = AnimationFrame(0 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_prone = Animation("Prone", frames_prone, numFrames);
	player.animations[animation_prone.name] = AnimationData(animation_prone, timeToNextFrame, true);
	*/

	// Death Animation
	numFrames = 2;
	timeToNextFrame = 150;
	AnimationFrame* frames_death = new AnimationFrame[numFrames];
	frames_death[0] = AnimationFrame(21 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_death[1] = AnimationFrame(24 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_death = Animation("Death", frames_death, numFrames);
	player.animations[animation_death.name] = AnimationData(animation_death, timeToNextFrame, false);

	// IdleShooting Animation
	/*
	numFrames = 4;
	timeToNextFrame = 40;
	AnimationFrame* frames_shooting = new AnimationFrame[numFrames];
	frames_shooting[0] = AnimationFrame(6 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_shooting[1] = AnimationFrame(3 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_shooting[2] = AnimationFrame(0 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_shooting[3] = AnimationFrame(3 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_shooting = Animation("Shooting", frames_shooting, numFrames);
	player.animations[animation_shooting.name] = AnimationData(animation_shooting, timeToNextFrame, true);
	*/

	// RunShooting Animation
	/*
	numFrames = 8;
	timeToNextFrame = 100;
	AnimationFrame* frames_runShooting = new AnimationFrame[numFrames];
	frames_runShooting[0] = AnimationFrame(12 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[1] = AnimationFrame(0 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[2] = AnimationFrame(15 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[3] = AnimationFrame(3 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[4] = AnimationFrame(18 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[5] = AnimationFrame(6 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[6] = AnimationFrame(21 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[7] = AnimationFrame(9 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_runShooting = Animation("RunShooting", frames_runShooting, numFrames);
	player.animations[animation_runShooting.name] = AnimationData(animation_runShooting, timeToNextFrame, true);
	*/

	// ProneShooting Animation
	/*
	numFrames = 3;
	timeToNextFrame = 40;
	AnimationFrame* frames_proneShooting = new AnimationFrame[numFrames];
	frames_proneShooting[0] = AnimationFrame(6 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	frames_proneShooting[1] = AnimationFrame(0 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	frames_proneShooting[2] = AnimationFrame(3 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_proneShooting = Animation("ProneShooting", frames_proneShooting, numFrames);
	player.animations[animation_proneShooting.name] = AnimationData(animation_proneShooting, timeToNextFrame, true);
	*/

	// LookUp Animation
	/*
	numFrames = 1;
	timeToNextFrame = 200;
	AnimationFrame* frames_lookUp = new AnimationFrame[numFrames];
	frames_lookUp[0] = AnimationFrame(24 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_lookUp = Animation("LookUp", frames_lookUp, numFrames);
	player.animations[animation_lookUp.name] = AnimationData(animation_lookUp, timeToNextFrame, true);
	*/

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
		if (kbState[SDL_SCANCODE_A])
		{
			player->speedX = player->maxSpeedX;
			player->isFlippedX = true;
			player->speedX *= -1;
		}
		else if (kbState[SDL_SCANCODE_D])
		{
			player->speedX = player->maxSpeedX;
			player->isFlippedX = false;
		}
		else if (kbState[SDL_SCANCODE_W])
		{
			player->speedY = player->maxSpeedY;
			player->speedY *= -1;
		}
		else if (kbState[SDL_SCANCODE_S])
		{
			player->speedY = player->maxSpeedY;
		}
	}

	bool isIdle = (kbState[SDL_SCANCODE_W] | kbState[SDL_SCANCODE_A] | kbState[SDL_SCANCODE_S] | 
		kbState[SDL_SCANCODE_D] | kbState[SDL_SCANCODE_J] | kbState[SDL_SCANCODE_SPACE]) != 1;
	bool isWalkingLeft = (kbState[SDL_SCANCODE_A]) == 1;
	bool isWalkingRight = (kbState[SDL_SCANCODE_D]) == 1;
	bool isWalkingUp = (kbState[SDL_SCANCODE_W]) == 1;
	bool isWalkingDown = (kbState[SDL_SCANCODE_S]) == 1;

	//bool isRunShooting = ((kbState[SDL_SCANCODE_A] | kbState[SDL_SCANCODE_D]) & kbState[SDL_SCANCODE_J]) == 1;
	//bool isJumping = kbState[SDL_SCANCODE_K] == 1;
	//bool isProne = kbState[SDL_SCANCODE_S] == 1;
	//bool isShooting = kbState[SDL_SCANCODE_J] == 1;
	//bool isProneShooting = (kbState[SDL_SCANCODE_S] & kbState[SDL_SCANCODE_J]) == 1;

	// Player States
	// IDLE State
	if (player->state == IDLE)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Idle");
			player->prevState = player->state;

			player->speedX = 0;
			player->speedY = 0;
		}

		// Check for new Transition
		if (isWalkingLeft)
			player->state = WALKING_LEFT;
		else if (isWalkingRight)
			player->state = WALKING_RIGHT;
		else if (isWalkingDown)
			player->state = WALKING_DOWN;
		else if (isWalkingUp)
			player->state = WALKING_UP;

		/*
		else if (isShooting)
			player->state = IDLE_SHOOT;
		else if (isProne)
			player->state = PRONE;
		else if (isJumping)
			player->state = JUMPING;
		*/
	}

	// WALKING_DOWN State
	else if (player->state == WALKING_DOWN)	
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Walking Down");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (isIdle)
			player->state = IDLE;

	}

	// WALKING_UP State
	else if (player->state == WALKING_UP)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Walking Up");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (isIdle)
			player->state = IDLE;
	}

	// WALKING_LEFT State
	else if (player->state == WALKING_LEFT)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Walking Left");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (isIdle)
			player->state = IDLE;
	}

	// WALKING_RIGHT State
	else if (player->state == WALKING_RIGHT)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Walking Right");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (isIdle)
			player->state = IDLE;
	}

	/*
	// RUN SHOOTING State
	else if (player->state == RUN_SHOOTING)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("RunShooting");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!isWalking)
		{
			if (isShooting && !isProne)
				player->state = IDLE_SHOOT;
			else if (isProneShooting)
				player->state = PRONE_SHOOTING;
			else
				player->state = IDLE;
		}
		else if (isWalking && !isShooting)
			player->state = WALKING;
		else if (isProne)
		{
			if (isShooting)
				player->state = PRONE_SHOOTING;
			else
				player->state = PRONE;
		}
		else if (isJumping)
			player->state = JUMPING;
	}
	*/

	/*
	// JUMPING State
	else if (player->state == JUMPING)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Jumping");
			player->prevState = player->state;

			player->isJumping = true;
			if (player->jumpTicksRemaining <= 0)
				player->jumpTicksRemaining = player->jumpTicks;
		}

		if (isJumping)
		{
			if (player->jumpTicksRemaining > 0)
				player->speedY = player->jumpSpeed;
		}
		else
			player->jumpTicksRemaining = 0;

		// Check for new Transition
		if (!player->isJumping)
		{
			if (!isWalking)
			{
				if (isShooting)
					player->state = IDLE_SHOOT;
				else
					player->state = IDLE;
			}
			else if (isWalking)
			{
				if(isShooting)
					player->state = RUN_SHOOTING;
				else
					player->state = WALKING;
			}
			else if (isProne)
			{
				if (isShooting)
					player->state = PRONE_SHOOTING;
				else
					player->state = PRONE;
			}
		}
	}
	*/

	/*
	// PRONE State
	else if (player->state == PRONE)
	{
		player->speedX = 0;

		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Prone");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!isProne && !isWalking && !isJumping)
		{
			if (isShooting)
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if (isWalking && !isProne)
		{
			// Fix for Gun Up / Gun Down
			if(isShooting)
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (isShooting)
		{
			player->state = PRONE_SHOOTING;
		}
		else if (isJumping)
			player->state = JUMPING;
	}
	*/

	/*
	// PRONE SHOOTING State
	else if (player->state == PRONE_SHOOTING)
	{
		player->speedX = 0;

		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("ProneShooting");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!isWalking && !isJumping && !isProne)
		{
			if (isShooting)
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if (isWalking && !isProne)
		{
			if(isShooting)
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (isProne && !isShooting)
		{
			player->state = PRONE;
		}
		else if (isJumping)
			player->state = JUMPING;
	}
	*/

	/*
	// IDLE SHOOT State
	else if (player->state == IDLE_SHOOT)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Shooting");
			player->prevState = player->state;

			player->speedX = 0;
		}

		// Check for new Transition
		if (isIdle)
		{
			player->state = IDLE;
		}
		else if (isWalking)
		{
			if(isShooting)
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (isProne)
		{
			if (isShooting)
				player->state = PRONE_SHOOTING;
			else
				player->state = PRONE;
		}
		else if (isJumping)
			player->state = JUMPING;
	}
	*/

	else if (player->state == DEATH)
	{
		// Handle State Transition
 		if (player->state != player->prevState)
		{
			player->setAnimation("Death");
			player->prevState = player->state;

         eventQueue->queueEvent(Event(Event::ET_DEATH, "subject", "player"));

			player->isJumping = true;
			if (player->speedX >= 0)
				player->speedX = -200;
			else
				player->speedX = 200;
			player->speedY = -300;
		}
		
		if (!player->isJumping)
			player->speedX = 0;
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
			int newY = (sprite->collider.y - 1) - player->height;
			player->updatePosition(player->posX,(float) newY);
		}

		if (sprite->type == COLLISION_GROUND)
		{
			if (sides[LEFT])
			{
				player->speedX = 0;
				int newX = (sprite->collider.x - 1) - (player->collider.w + player->colliderXOffset);
				player->updatePosition((float) newX, player->posY);
			}
 			else if (sides[RIGHT])
			{
  				player->speedX = 0;
				int newX = (sprite->collider.x + 1) + sprite->collider.w - player->colliderXOffset;
				player->updatePosition((float) newX , player->posY);
			}
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
	player->setSpeed(0,0);
	player->updatePosition(x, y - player->height);
}
/*-----------------------------------------------*/