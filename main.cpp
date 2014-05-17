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

	g_windowMaxWidth = (g_currentLevel->width * g_currentLevel->tilesWidth);
	g_windowMaxHeight = (g_currentLevel->height * g_currentLevel->tilesHeight);

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
   g_audio.registerListeners(&g_eventQueue);  //TODO Uncomment
}
/*-----------------------------------------------*/
static void initDialog()
{
   g_dialogManager.dialogQueue = &g_dialogBoxes;
   g_dialogManager.screenWidth = &g_windowWidth;
   g_dialogManager.screenHeight = &g_windowHeight;
   g_dialogManager.eventQueue = &g_eventQueue;
   g_dialogManager.initDialogs();
   g_dialogManager.registerListeners(&g_eventQueue);
}
/*-----------------------------------------------*/
static void initBattleManager()
{
   battleManager::dialogManager = &g_dialogManager;
   battleManager::eventQueue = &g_eventQueue;
   battleManager::player = &g_player;
   battleManager::levels = &g_levels;
   battleManager::currentLevel = &g_currentLevel;
   battleManager::cam = &g_cam;
   battleManager::textures = &g_textures;
   battleManager::init();
}
/*-----------------------------------------------*/
static void initMapManager()
{
   g_MapManager = MapManager();
   g_MapManager.player = &g_player;
   g_MapManager.levels = &g_levels;
   g_MapManager.camera = &g_cam;
   g_MapManager.windowWidth = &g_windowWidth;
   g_MapManager.windowHeight = &g_windowHeight;
   g_MapManager.windowMaxWidth = &g_windowMaxWidth;
   g_MapManager.windowMaxHeight = &g_windowMaxHeight;
   g_MapManager.currentLevel = &g_currentLevel;
   g_MapManager.eventQueue = &g_eventQueue;

   g_MapManager.registerListeners(&g_eventQueue);
}
/*-----------------------------------------------*/
static void updateCheckBuckets()
{
	/* PURPOSE:		Determines which buckets to check physics against 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Only checks screens immediately surrounding player 
						 
	*/

	g_checkBuckets[0] = bucketManager::whichBucket(g_cam.x - g_windowWidth, g_cam.y + g_windowHeight);
   g_checkBuckets[1] = bucketManager::whichBucket(g_cam.x, g_cam.y + g_windowHeight);
   g_checkBuckets[2] = bucketManager::whichBucket(g_cam.x + g_windowWidth, g_cam.y + g_windowHeight);
   g_checkBuckets[3] = bucketManager::whichBucket(g_cam.x - g_windowWidth, g_cam.y);
   g_checkBuckets[4] = bucketManager::whichBucket(g_cam.x, g_cam.y);
   g_checkBuckets[5] = bucketManager::whichBucket(g_cam.x + g_windowWidth, g_cam.y);
   g_checkBuckets[6] = bucketManager::whichBucket(g_cam.x - g_windowWidth, g_cam.y - g_windowHeight);
   g_checkBuckets[7] = bucketManager::whichBucket(g_cam.x, g_cam.y - g_windowHeight);
   g_checkBuckets[8] = bucketManager::whichBucket(g_cam.x + g_windowWidth, g_cam.y - g_windowHeight);
}
/*-----------------------------------------------*/
static void initBuckets()
{
	/* PURPOSE:		Sets up buckets for optimization based on screen resolution 
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Each screen is a bucket
	*/

   bucketManager::init(&g_spriteBuckets, &g_windowWidth, &g_windowHeight, &g_windowMaxWidth, &g_windowMaxHeight);
   g_checkBuckets.assign(g_numOfCheckBuckets, 0);

   bucketManager::updateBucketSize();

	//// Initialize spriteBuckets
	//int bucketWidth = (int) floor((float) g_windowMaxWidth / g_windowWidth);
	//int bucketHeight = (int) floor((float) g_windowMaxHeight / g_windowHeight);
 //  int numOfBuckets = bucketWidth * bucketHeight;
 //  
 //  // In case screen is too small
 //  if (numOfBuckets < 1)
 //     numOfBuckets = 1;

	//g_spriteBuckets.reserve(numOfBuckets);
	//
	//for (int i = 0; i < numOfBuckets; i++)
	//{
	//	vector<Sprite*> temp;
	//	g_spriteBuckets.push_back(temp);
	//}
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
   spriteManager::init(&g_spriteBuckets, &g_textures, &g_windowMaxWidth, &g_windowMaxHeight);
   spriteManager::loadLevelSprites(g_currentLevel->name);

   Texture* title = &g_textures["title"];
   g_titleScreen = Sprite(&title->texture, 0, 0, title->width, title->height);

	// Create and place player on map
	Texture* tex = &g_textures["link"];
 	g_player = player::makePlayer(&tex->texture, tex->width, tex->height, &g_eventQueue);
	int startX = g_currentLevel->startX;
   int g_colliderNegativeYOffset = g_player.colliderYOffset + g_player.collider.h;
	int startY = g_currentLevel->startY - g_colliderNegativeYOffset;

	g_player.updatePosition((float) startX, (float) startY);
   g_cam.follow(startX, startY, g_player.width, g_player.height);
   g_player.cam = &g_cam;

   // Setup DialogContainer texture to be used
   DialogContainer::texture = &g_textures["dialog"];
   Font::texture = &g_textures["font"];
   Font::buildFontMap();
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
   std::string levelName = g_currentLevel->name;
   while (collisions->size() > 0 && g_currentLevel->name.compare(levelName)==0)
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
				Sprite* sprite = g_spriteBuckets[bucket][j];
				sprite->update(diff_time);

				// Check for Collisions
				if (g_player.collider.AABBIntersect(&sprite->collider))
					player::collisionResolution(&g_player, sprite);
			}
		}
	}
   
   // Rebucket if necessary
   for (int i = 0; i < g_numOfCheckBuckets; i++)
   {
      if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
      {
         int bucket = g_checkBuckets[i];
         int spriteBucketSize = g_spriteBuckets.size();
         int bucketSize = g_spriteBuckets[bucket].size();
         for (int j = 0; j < bucketSize; j++)
         {
            Sprite* sprite = g_spriteBuckets[bucket][j];
            int newBucket = bucketManager::whichBucket(sprite->x, sprite->y);
            if (newBucket >= 0 && newBucket < spriteBucketSize && newBucket != bucket)
            {
               g_spriteBuckets[newBucket].push_back(sprite);
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
				if (g_cam.collider.AABBIntersect(&g_spriteBuckets[bucket][j]->collider))
					g_spriteBuckets[bucket][j]->drawUV(g_cam.x, g_cam.y);
			}
		}
	}

	g_player.drawUV(g_cam.x, g_cam.y);
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
static void loadLevel()
{
	/* PURPOSE:		Loads the tile map from flare.txt file
		RECEIVES:	 
		RETURNS:		 
		REMARKS:		Determines starting position for player
	*/

   levelLoader::loadLevels(&g_levels, &g_currentLevel);
}
/*-----------------------------------------------*/
static void clearBackground()
{
   /* PURPOSE:		Clears the background to a set color
      RECEIVES:
      RETURNS:
      REMARKS:		Black color currently
      */

   float r, g, b;
   r = 0;
   g = 0;
   b = 0;

   glClearColor(r, g, b, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   SDL_GL_SwapWindow(g_window);
}
/*-----------------------------------------------*/
static void keyboard()
{
   /* PURPOSE:		Handles keyboard presses by user
      RECEIVES:
      RETURNS:
      REMARKS:		Player related controls are handled through player class
      */

   if (!g_isTitleShowing)
   {
      if (!g_isInputRequired)
         player::playerKeyboard(&g_player, kbState, kbPrevState);
      else
         player::stopPlayer(&g_player);

      if (battleManager::isBattle)
         battleManager::keyboard(kbState, kbPrevState);
      else
         g_dialogManager.dialogKeyboard(kbState, kbPrevState);
   }
   // Reset camera to following if it has been moved around
   if (g_cam.isFollowing && (kbState[SDL_SCANCODE_UP] | kbState[SDL_SCANCODE_DOWN] | kbState[SDL_SCANCODE_LEFT] | kbState[SDL_SCANCODE_RIGHT]))
      g_cam.isFollowing = false;
   else if (!g_cam.isFollowing)
   {
      if (kbState[SDL_SCANCODE_W] | kbState[SDL_SCANCODE_A] | kbState[SDL_SCANCODE_D])
         g_cam.isFollowing = true;
   }

   if (kbState[SDL_SCANCODE_LEFT])
   {
      g_cam.updateX(-camSpeed);
   }
   else if (kbState[SDL_SCANCODE_RIGHT])
   {
      g_cam.updateX(camSpeed);
   }
   else if (kbState[SDL_SCANCODE_UP])
   {
      g_cam.updateY(-camSpeed);
   }
   else if (kbState[SDL_SCANCODE_DOWN])
   {
      g_cam.updateY(camSpeed);
   }
   else if (kbState[SDL_SCANCODE_ESCAPE])
   {
      shouldExit = true;
   }
   else if (kbState[SDL_SCANCODE_EQUALS] || kbState[SDL_SCANCODE_KP_PLUS])
   {
      // TODO Remove
      Chicken* chicken = new Chicken();
      chicken->updatePosition(1000, 1000);

      int bucket = bucketManager::whichBucket(chicken->x, chicken->y);
      if (bucket < 0)
         bucket = 0;
      else if (bucket >= g_spriteBuckets.size() - 1)
         bucket = g_spriteBuckets.size() - 1;
      g_spriteBuckets[bucket].push_back(chicken);
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
   else if (kbState[SDL_SCANCODE_Y] && !kbPrevState[SDL_SCANCODE_Y])
   {
      // TODO remove this
      battleManager::checkBattle(battleManager::BATTLE_YES);
   }

   if (g_isTitleShowing && kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J])
   {
      g_isTitleShowing = false;


      Event ev = Event(Event::ET_LEVEL_LOAD, "level", "overworld");
      ev.strParams["newGame"] = "true";
      g_eventQueue.queueEvent(ev);
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
         g_currentLevel->drawLevel(g_cam.x, g_cam.y, g_windowOriginalWidth, g_windowOriginalHeight);
         if (!battleManager::isBattle)
            drawSprites();
         else
            battleManager::drawSprites();

         drawDialogBoxes();
      
      // Title Screen
         if (g_isTitleShowing)
            g_titleScreen.draw();
		
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
      if (!battleManager::isBattle)
      {
         updateSprites(ticksPerPhysics);
         player::updatePhysics(&g_player, ticksPerPhysics);
      }
      else
         battleManager::updateBattle(ticksPerPhysics);

		// Update Timers
		*prevPhysicsTick += ticksPerPhysics;
	}
}
/*-----------------------------------------------*/
static void onQuit()
{
   fmodSystem->close();
   fmodSystem->release();

   
   for (int i = 0; i < (int)g_spriteBuckets.size(); i++)
      g_spriteBuckets[i].clear();
   g_spriteBuckets.clear();
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
   clearBackground();
	loadLevel();
   initMapManager();
	initCamera();
   initAudio();
   initBuckets();
	loadSprites();
   initDialog();
   initBattleManager();
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

   g_eventQueue.queueEvent(Event(Event::ET_TITLE_SCREEN));
	
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

   onQuit();
	SDL_Quit();
   
	return 0;
}
