#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include "PlayerSprite.h"
#include "EventQueue.h"

class player
{
protected:
   player();

public:

	// Functions
	static PlayerSprite makePlayer(GLuint* texture, int textureWidth, int textureHeight, EventQueue* eventQueue);
	static void playerKeyboard(PlayerSprite* player, const unsigned char* kbState, unsigned char* kbPrevState);
	static void updatePhysics(PlayerSprite* player, int diff_time);
	static void collisionResolution(PlayerSprite* player, Sprite* sprite);
	static void restartPlayer(PlayerSprite* player, int x, int y);
   static void stopPlayer(PlayerSprite* player);

   // Variables
   static EventQueue* eventQueue;
};