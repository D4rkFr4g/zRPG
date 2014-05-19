#pragma once
#include <unordered_map>
#include <string>
#include "AnimatedSprite.h"
#include "Camera.h"
#include "EventListener.h"
#include "EventQueue.h"


class PlayerSprite :
	public AnimatedSprite, public EventListener
{
public:
	PlayerSprite(void);
	PlayerSprite(GLuint* texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY, int health);
	~PlayerSprite(void);

	// Functions
   void initStats(int STR, int CON, int DEX, int INT, int LCK);
   void updateCamera();
   virtual void notify(Event* event) override;
   void registerListeners(EventQueue* eventQueue);


	// Variables
	bool isAlive;
	int health;
   int level;
   int maxLevel;
   int xp;
   int maxHealth;
   int magic;
   int maxMagic;
	int score;
	int state;
	int prevState;
	int jumpTicks;
	int jumpTicksRemaining;
	float jumpSpeed;
	bool isJumping;
   bool hasSword;
   bool isGanonDefeated;
   int startX;
   int startY;
   std::vector<int> xpToNextLevel;
   std::unordered_map<std::string, int> items;
   std::unordered_map<std::string, int> stats;
   Camera* cam;
};

