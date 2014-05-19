#pragma once
#include "AnimatedSprite.h"
#include "Texture.h"
#include "textureLoader.h"

class Zelda : public AnimatedSprite
{
private:
	void AI();
	float randomSpeed();
	void updateDirection(float speedX, float speedY);

public:
	Zelda();
	~Zelda();

	// Functions
	virtual void update(int ms) override;
	virtual void onTrigger() override;
   virtual void onCollision() override;
	void setRandomMovement();
};

