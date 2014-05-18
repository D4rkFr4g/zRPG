#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"

class VillagerC : public AnimatedSprite
{
private:
	void AI();
	float randomSpeed();
	void updateDirection(float speedX, float speedY);

public:
	VillagerC();
	~VillagerC();

	// Functions
	virtual void update(int ms) override;
   virtual void onTrigger() override;
	void setRandomMovement();
};

