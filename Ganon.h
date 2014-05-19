#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"
#include "enumLibrary.h"

class Ganon : public AnimatedSprite
{
private:
	void AI();
	float randomSpeed();
	void updateDirection(float speedX, float speedY);

public:
	Ganon();
	~Ganon();

	// Functions
	virtual void update(int ms) override;
	virtual void onTrigger() override;
	void setRandomMovement();
};

