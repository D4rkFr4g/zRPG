#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"

class VillagerA : public AnimatedSprite
{
private:
	void AI();
	float randomSpeed();
	void updateDirection(float speedX, float speedY);

public:
	VillagerA();
	~VillagerA();

	// Functions
	virtual void update(int ms) override;
	void setRandomMovement();

   // Variables
   bool hasSword;
};

