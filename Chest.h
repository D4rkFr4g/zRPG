#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"

class Chest : public Chest
{
private:
	//void AI();

public:
	Chest();
	~Chest();

	// Functions
	virtual void update(int ms) override;
	void setRandomMovement();
};

