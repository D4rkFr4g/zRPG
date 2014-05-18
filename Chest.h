#pragma once
#include "Sprite.h"
#include "Texture.h"
#include "textureLoader.h"

class Chest : public Sprite
{
private:
	//void AI();
	//float randomSpeed();
	//void updateDirection();

public:
	Chest();
	~Chest();

	// Functions
	//virtual void update(int ms) override;
	//void setRandomMovement();

	//Variables
	std::map<std::string, AnimationData> animations;
};

