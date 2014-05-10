/****************************************************** 
* Copyright (c):   2014, All Rights Reserved. 
* Project:         TileEngine 
* File:            main.cpp 
* Purpose:         Create a dynamic tile engine using SDL and OpenGL 
* Start date:      2/17/2014 
* Programmer:      Zane Melcho 
* 
****************************************************** 
*/

#include "main.h"

using namespace std;

/*-----------------------------------------------*/
static int initSDL()
{
	/* PURPOSE:		Sets up program to use a window through SDL
		RECEIVES:	 
		RETURNS:		0 if no issues otherwise returns 1
		REMARKS:		 
	*/

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) 
	{
		return 1;
	}
 
	// Create the window, OpenGL context
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	g_window = SDL_CreateWindow(
	"The Legend of Zelda: A Link to the RPG",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	g_windowWidth, g_windowHeight,
	SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);// | SDL_WINDOW_FULLSCREEN );
	glCullFace( GL_BACK );

	if( !g_window ) 
	{
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext( g_window );

	// Make sure we have a recent version of OpenGL
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) 
	{
		SDL_Quit();
		return 1;
	}
	if( !GLEW_VERSION_1_5 ) 
	{
		SDL_Quit();
		return 1;
	}
	
	return 0;
}
/*-----------------------------------------------*/
static void init2D()
{
	/* PURPOSE:		Initializes OpenGL settings
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	// OpenGL calls
	glViewport(0,0,(GLsizei) g_windowWidth, (GLsizei) g_windowHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, g_windowWidth, g_windowHeight, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);  //Ghost Chickens
}
/*-----------------------------------------------*/
static void initCamera()
{
	/* PURPOSE:		Initializes camera 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		 
	*/

	g_windowOriginalWidth = g_windowWidth;
	g_windowOriginalHeight = g_windowHeight;

	TileLevel currentLevel = *g_currentLevel;

	g_windowMaxWidth = (currentLevel.width * currentLevel.tilesWidth);
	g_windowMaxHeight = (currentLevel.height * currentLevel.tilesHeight);

	g_cam = Camera(0, 0, 0, g_windowMaxWidth - g_windowWidth, 0, g_windowMaxHeight - g_windowHeight);
	g_cam.updateResolution(g_windowWidth, g_windowHeight);

	g_cam.isFollowing = true;
}
/*-----------------------------------------------*/
static void initAudio()
{
   result = FMOD::System_Create(&fmodSystem); // Create the Studio System object.
   if (result != FMOD_OK)
   {
       printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
       exit(-1);
   }

   // Initialize FMOD Studio, which will also initialize FMOD Low Level
   result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
   if (result != FMOD_OK)
   {
       printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
       exit(-1);
   }

   FMOD::ChannelGroup* channelMusic;
   FMOD::ChannelGroup* channelEffects;
   FMOD::Channel    *channel = 0;
   
   fmodSystem->createChannelGroup(NULL, &channelMusic);
   fmodSystem->createChannelGroup(NULL, &channelEffects);

   g_audio = Audio(fmodSystem, channelMusic, channelEffects);
   //g_audio.registerListeners(&g_eventQueue);  //TODO Uncomment
}
/*-----------------------------------------------*/
static void initDialog()
{
   g_dialogManager.dialogQueue = &g_dialogBoxes;
   g_dialogManager.screenWidth = &g_windowWidth;
   g_dialogManager.screenHeight = &g_windowHeight;
   g_dialogManager.initDialogs();
   g_dialogManager.registerListeners(&g_eventQueue);
}
/*-----------------------------------------------*/
static int whichBucket(int x, int y)
{
	/* PURPOSE:		Determines which bucket corresponds to world coordinates 
		RECEIVES:	x - Horizontal screen position
						y - Vertical screen position
		RETURNS:		Returns index of corresponding bucket 
		REMARKS:		Determined by screen resolution each screen is one bucket
	*/

	int column = (int) floor((float) x / g_windowWidth);
	int row = (int) floor((float) y / g_windowHeight);
	int bucketWidth = (int) floor((float) g_windowMaxWidth / g_windowWidth);

	return (row * bucketWidth) + column;
}
/*-----------------------------------------------*/
static void updateCheckBuckets()
{
	/* PURPOSE:		Determines which buckets to check physics against 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Only checks screens immediately surrounding player 
						 
	*/

	g_checkBuckets[0] = whichBucket(g_cam.x - g_windowWidth, g_cam.y + g_windowHeight);
	g_checkBuckets[1] = whichBucket(g_cam.x, g_cam.y + g_windowHeight);
	g_checkBuckets[2] = whichBucket(g_cam.x + g_windowWidth, g_cam.y + g_windowHeight);
	g_checkBuckets[3] = whichBucket(g_cam.x - g_windowWidth, g_cam.y);
	g_checkBuckets[4] = whichBucket(g_cam.x, g_cam.y);
	g_checkBuckets[5] = whichBucket(g_cam.x + g_windowWidth, g_cam.y);
	g_checkBuckets[6] = whichBucket(g_cam.x - g_windowWidth, g_cam.y - g_windowHeight);
	g_checkBuckets[7] = whichBucket(g_cam.x, g_cam.y - g_windowHeight);
	g_checkBuckets[8] = whichBucket(g_cam.x + g_windowWidth, g_cam.y - g_windowHeight);
}
/*-----------------------------------------------*/
static void initBuckets()
{
	/* PURPOSE:		Sets up buckets for optimization based on screen resolution 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Each screen is a bucket
	*/

	g_checkBuckets = new int [g_numOfCheckBuckets];

	// Initialize spriteBuckets
	int bucketWidth = (int) floor((float) g_windowMaxWidth / g_windowWidth);
	int bucketHeight = (int) floor((float) g_windowMaxHeight / g_windowHeight);
   int numOfBuckets = bucketWidth * bucketHeight;
   
   // In case screen is too small
   if (numOfBuckets < 1)
      numOfBuckets = 1;

	g_spriteBuckets.reserve(numOfBuckets);
	
	for (int i = 0; i < numOfBuckets; i++)
	{
		vector<AnimatedSprite> temp;
		g_spriteBuckets.push_back(temp);
	}
}
/*-----------------------------------------------*/
static void loadSprites()
{
	/* PURPOSE:                Loads images into textures for sprites to use
	RECEIVES:
	RETURNS:
	REMARKS:                Also creates and places sprites on map
	*/

	textureLoader::loadTextures(&g_textures);

	// Load the Initial chickens
	for (int i = 0; i < initialChickens; i++)
		makeChicken();

	// Create and place player on map
	Texture* tex = &g_textures["link"];
	g_player = player::makePlayer(&tex->texture, tex->width, tex->height, &g_eventQueue);
	int startX = g_currentLevel->startX;
	int startY = g_currentLevel->startY - g_player.height;

	g_player.updatePosition((float) startX, (float) startY);

   // Setup DialogBox texture to be used
   DialogBox::texture = &g_textures["dialog"];
   Font::texture = &g_textures["font"];
   Font::buildFontMap();
}
/*-----------------------------------------------*/
static void makeChicken()
{
	/* PURPOSE:		Create chicken enemy sprite 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Sets animations, position, and initial bucket
	*/

	int x = rand() % (g_windowMaxWidth - spriteSize);
	int y = rand() % (g_windowMaxHeight - spriteSize);

	Texture* tex = &g_textures["chicken"];
	AnimatedSprite sprite_chicken = AnimatedSprite(&tex->texture, x, y, tex->width, tex->height, 0, 0, 0.5, 1);
	sprite_chicken.type = 2;

	//Setup Collider
	int xOffset = 20;
	int yOffset = 25;
	int width = 20;
	int height = 20;
	sprite_chicken.colliderXOffset = xOffset;
	sprite_chicken.colliderYOffset = yOffset;
	sprite_chicken.setCollider(&AABB(sprite_chicken.x + xOffset, sprite_chicken.y + yOffset, width, height));

	// Walking Animation
	int numFrames = 2;
	int timeToNextFrame = 300;
	AnimationFrame* frames_walking = new AnimationFrame[numFrames];
	frames_walking[0] = AnimationFrame(0,0,0.5,1);
	frames_walking[1] = AnimationFrame(0.5,0,0.5,1);
	Animation animation_walking = Animation("Walking", frames_walking, numFrames);
	sprite_chicken.animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

	// Idle Animation
	numFrames = 1;
	AnimationFrame* frames_idle = new AnimationFrame[numFrames];
	frames_idle[0] = AnimationFrame(0,0,0.5,1);
	Animation animation_idle = Animation("Idle", frames_idle, numFrames);
	sprite_chicken.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);
	sprite_chicken.setAnimation("Walking");
	
	// Set Chicken direction
	sprite_chicken.setSpeed(getSpeed(), getSpeed());

	// Set direction
	if (sprite_chicken.speedX < 0)
		sprite_chicken.isFlippedX = true;
	else if (sprite_chicken.speedX > 0)
		sprite_chicken.isFlippedX = false;

	// Load sprite into bucket
	x = sprite_chicken.x;
	y = sprite_chicken.y;
	g_spriteBuckets[whichBucket(x, y)].push_back(sprite_chicken);
}
/*-----------------------------------------------*/
void chickenAI(int diff_time)
{
	/* PURPOSE:		Control chicken movements based on probabilities 
		RECEIVES:	diff_time - milliseconds since last frame 
		RETURNS:		 
		REMARKS:		 
	*/

	updateCheckBuckets();
	int numOfBuckets = g_spriteBuckets.size();

	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			for (int j = 0; j < (int) g_spriteBuckets[bucket].size(); j++)
			{
				AnimatedSprite* chicken = &g_spriteBuckets[bucket][j];
				float speedX = chicken->speedX;
				float speedY = chicken->speedY;

				// If stopped Restart Chicken Maybe
				if (speedX == 0 && speedY == 0)
				{
					int willRestart = rand() % 100;
					if (!willRestart)
					{
						// Set speed and animation
						speedX = getSpeed();
						speedY = getSpeed();
						chicken->setAnimation("Walking");

						// Set sprite direction
						if (speedX < 0)
							chicken->isFlippedX = true;
						else if (speedX > 0)
							chicken->isFlippedX = false;
					}
				}
				else
				{
					// Randomly stop chickens
					int willStop = rand() % 250;
					if (!willStop)
					{
						speedX = 0;
						speedY = 0;
						chicken->setAnimation("Idle");
					}
				}

				chicken->setSpeed(speedX, speedY);
			}
		}
	}
}
/*-----------------------------------------------*/
void updateSprites(int diff_time)
{
	/* PURPOSE:		Update physics for sprites 
		RECEIVES:	diff_time - milliseconds since last frame 
		RETURNS:		 
		REMARKS:		 
	*/

	// Update player
	g_player.update(diff_time);
	g_cam.follow(g_player.x, g_player.y, g_player.width, g_player.height);

	// Check for Tile Collisions surrounding player
	vector<int>* collisions = g_currentLevel->checkCollision(&g_player.collider);
	while (collisions->size() > 0)
	{
      Sprite* sprite = &g_currentLevel->tileArray[collisions->front()];
		player::collisionResolution(&g_player, sprite);
		collisions->erase(collisions->begin());
 	}

	// Update Other Sprites
	updateCheckBuckets();

	int numOfBuckets = g_spriteBuckets.size();
	
	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			int spriteBucketSize = g_spriteBuckets.size();
			int bucketSize = g_spriteBuckets[bucket].size();
			for (int j = 0; j < bucketSize; j++)
			{
				AnimatedSprite* sprite = &g_spriteBuckets[bucket][j];
				sprite->update(diff_time);

				// Check for Collisions
				if (g_player.collider.AABBIntersect(&sprite->collider))
					player::collisionResolution(&g_player, sprite);

				// Rebucket if necessary
				int newBucket = whichBucket(sprite->x, sprite->y);
				if (newBucket >= 0 && newBucket < spriteBucketSize && newBucket != bucket)
				{
					g_spriteBuckets[newBucket].push_back(*sprite);
					g_spriteBuckets[bucket].erase(g_spriteBuckets[bucket].begin() + j);
					j--;
					bucketSize--;
				}
			}
		}
	}
}
/*-----------------------------------------------*/
static void drawSprites()
{
	/* PURPOSE:		Draws all sprites on screen 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Only drawn if sprite is actually on screen.
	*/

	updateCheckBuckets();

	int numOfBuckets = g_spriteBuckets.size();
	
	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			for (int j = 0; j < (int) g_spriteBuckets[bucket].size(); j++)
			{
				// Only draw if sprite is on screen
				if (g_cam.collider.AABBIntersect(&g_spriteBuckets[bucket][j].collider))
				{
					g_spriteBuckets[bucket][j].drawUV(g_cam.x, g_cam.y);
					//g_spriteBuckets[bucket][j].drawCollider(g_cam.x, g_cam.y);
				}
			}
		}
	}

	g_player.drawUV(g_cam.x, g_cam.y);
	//g_player.drawCollider(g_cam.x, g_cam.y);
}
/*-----------------------------------------------*/
static void drawDialogBoxes()
{
   int size = g_dialogBoxes.size();
   g_isInputRequired = false;
   for (int i = 0; i < (int)g_dialogBoxes.size(); i++)
   {
      if (g_dialogBoxes[i].isInputNeeded)
         g_isInputRequired = true;
    
      g_dialogBoxes[i].display();
   }
}
/*-----------------------------------------------*/
static float getSpeed()
{
	/* PURPOSE:		Randomly selects a set speed that is positive or negative 
		RECEIVES:	 
		RETURNS:		a float corresponding to the speed 
		REMARKS:		 
	*/

	int speed = rand() % 2;
	int negation = rand() % 2;
	if (negation)
		speed *= -1;
	return (float) speed * chickenSpeed;
}
/*-----------------------------------------------*/
static void loadLevel()
{
	/* PURPOSE:		Loads the tile map from flare.txt file
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Determines starting position for player
	*/

   g_currentLevel = new TileLevel();
   levelLoader::loadLevels(&g_levels, &g_currentLevel);

	// Find start position
	int startTile = 4;
	for (int i = 0; i < (int) g_currentLevel->collidableTiles.size(); i++)
	{
		int index = g_currentLevel->collidableTiles[i];
		int type = g_currentLevel->tileArray[index].type;
		if (type == startTile)
		{
			g_currentLevel->startX = g_currentLevel->tileArray[index].x - g_currentLevel->tilesWidth;
			g_currentLevel->startY = g_currentLevel->tileArray[index].y;
		}
	}
   
   Event ev = Event(Event::ET_LEVEL_BEGIN, "level", g_currentLevel->name);
   ev.strParams["newGame"] = "true";
   g_eventQueue.queueEvent(ev);
}
/*-----------------------------------------------*/
static void clearBackground()
{
	/* PURPOSE:		Clears the background to a set color 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Black color currently
	*/

	float r,g,b;
	r = 0;
	g = 0;
	b = 0;
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}
/*-----------------------------------------------*/
static void keyboard()
{
	/* PURPOSE:		Handles keyboard presses by user 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Player related controls are handled through player class
	*/

   if (!g_isInputRequired)
      player::playerKeyboard(&g_player, kbState, kbPrevState);
   else
      player::stopPlayer(&g_player);

   g_dialogManager.dialogKeyboard(kbState, kbPrevState);

   // Reset camera to following if it has been moved around
	if (g_cam.isFollowing && (kbState[SDL_SCANCODE_UP] | kbState[SDL_SCANCODE_DOWN] | kbState[SDL_SCANCODE_LEFT] | kbState[SDL_SCANCODE_RIGHT]))
		g_cam.isFollowing = false;
	else if (!g_cam.isFollowing)
	{
		if (kbState[SDL_SCANCODE_W] | kbState[SDL_SCANCODE_A] | kbState[SDL_SCANCODE_D])
			g_cam.isFollowing = true;
	}

	if (kbState[ SDL_SCANCODE_LEFT ])
	{
		g_cam.updateX(-camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_RIGHT ])
	{
		g_cam.updateX(camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_UP ])
	{
		g_cam.updateY(-camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_DOWN ])
	{
		g_cam.updateY(camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_ESCAPE ])
	{
		shouldExit = true;
	}
	else if (kbState[ SDL_SCANCODE_EQUALS] || kbState[ SDL_SCANCODE_KP_PLUS ])
	{
		makeChicken();
	}
	else if (kbState[SDL_SCANCODE_MINUS] || kbState[SDL_SCANCODE_KP_MINUS])
	{
		// Remove a random chicken
		int numOfBuckets = g_spriteBuckets.size();
		int choice = rand() % numOfBuckets;

		if (g_spriteBuckets[choice].size() > 0)
			g_spriteBuckets[choice].pop_back();
	}
	else if (kbState[SDL_SCANCODE_R] && !kbPrevState[SDL_SCANCODE_R])
	{
		player::restartPlayer(&g_player, g_currentLevel->startX, g_currentLevel->startY);
      g_eventQueue.queueEvent(Event(Event::ET_RESTART));
	}
}
/*-----------------------------------------------*/
static void reshape(const int w, const int h) 
{
	/*	PURPOSE:		Resizes everything based on new window dimensions 
		RECEIVES:	w - Width of window
						h - Height of window
		RETURNS:		 
		REMARKS:		 
	*/

	g_windowWidth = w;
	g_windowHeight = h;
	glViewport(0, 0, w, h);
	//g_cam.updateResolution(w, h); // Updating the camera causes following issues
}
/*-----------------------------------------------*/
void onRender(int* tick, int* prevTick, int ticksPerFrame)
{
   /*	PURPOSE:		Handles all graphics related calls once per SDL loop 
   RECEIVES:	 
   RETURNS:		 
   REMARKS:		 
   */

	do 
	{
		// All draw calls go here
		clearBackground();
		g_currentLevel->drawLevel(g_cam.x, g_cam.y, g_windowOriginalWidth, g_windowOriginalHeight);
		drawSprites();
      drawDialogBoxes();

		// Timer updates
		SDL_Delay( max( 0, ticksPerFrame - (*tick - *prevTick) ));
		*tick = SDL_GetTicks();
	} while( ticksPerFrame - (*tick - *prevTick) > 0 );
	*prevTick = *tick;

   SDL_GL_SwapWindow( g_window );
}
/*-----------------------------------------------*/
void onPhysics(int tick, int* prevPhysicsTick, int ticksPerPhysics)
{
   /*	PURPOSE:		Handles all Physics related calls 
   RECEIVES:	 
   RETURNS:		 
   REMARKS:		 
   */

	while( tick > *prevPhysicsTick + ticksPerPhysics ) 
	{
		// Update physics
		chickenAI(ticksPerPhysics);
		updateSprites(ticksPerPhysics);
		player::updatePhysics(&g_player, ticksPerPhysics);

		// Update Timers
		*prevPhysicsTick += ticksPerPhysics;
	}
}
/*-----------------------------------------------*/
static void onLoop()
{
   /*	PURPOSE:		Handles all once per SDL loop calls 
   RECEIVES:	 
   RETURNS:		 
   REMARKS:		 
   */
   
   g_eventQueue.updateEventQueue();
   fmodSystem->update();
}
/*-----------------------------------------------*/
static void onInit()
{
   /*	PURPOSE:		Handles all initialization related calls 
   RECEIVES:	 
   RETURNS:		 
   REMARKS:		 
   */

   init2D();
	loadLevel();
	initCamera();
   initAudio();
   initBuckets();
	loadSprites();
   initDialog();
}
/*-----------------------------------------------*/
int main( void )
{	
	srand((unsigned int) time(NULL));

	// Setup calls
	if (initSDL())
		return 1;

	onInit();

	// Timers
	int ticksPerFrame = 1000 / 60;
	int prevTick = SDL_GetTicks();
	int ticksPerPhysics = 1000 / 100;
	int prevPhysicsTick = prevTick;

	// Read keyboard status
	kbState = SDL_GetKeyboardState( NULL );
	
	// The game loop
	while( !shouldExit ) 
	{
		memcpy(kbPrevState, kbState, sizeof( kbPrevState ));

		// Handle OS message pump
		SDL_Event event;
		while( SDL_PollEvent( &event )) 
		{
			switch( event.type ) 
			{
				case SDL_QUIT:
				return 0;
			}

			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				reshape(event.window.data1,event.window.data2);
		}

		int tick = SDL_GetTicks();

      keyboard();
		onRender(&tick, &prevTick, ticksPerFrame);
		onPhysics(tick, &prevPhysicsTick, ticksPerPhysics);
      onLoop();
	}

	SDL_Quit();
   fmodSystem->close();
   fmodSystem->release();
	return 0;
}