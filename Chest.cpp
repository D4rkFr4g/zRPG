#include "Chest.h"

Chest::Chest()
{
	Texture* tex = textureLoader::getTexture("friendly_npcs");
	Sprite sprite = Sprite(&tex->texture, 0, 0, tex->cellWidth, tex->cellHeight, 0 * tex->uSize, 3 * tex->vSize, 1 * tex->uSize, 1 * tex->vSize);
	*this = Chest((Chest&)sprite);
	type = 1;
	name = "chest";

	//Setup Collider
	int xOffset = 10;
	int yOffset = 15;
	int width = 20;
	int height = 20;
	float uSize = 1;
	float vSize = 1;
	colliderXOffset = xOffset;
	colliderYOffset = yOffset;
	setCollider(&AABB(x + xOffset, y + yOffset, width, height));
	maxSpeed = 50;
	isColliderDrawn = true;

	// Idle Animation
	int numFrames = 1;
	int timeToNextFrame = 300;
	std::vector<AnimationFrame> frames;
	frames.clear();
	frames.assign(numFrames, AnimationFrame());

	frames[0] = AnimationFrame(0, 3, uSize, vSize);
	Animation animation_idle = Animation("Idle", frames, numFrames);
	animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);


}
/*-----------------------------------------------*/
Chest::~Chest()
{
}
/*-----------------------------------------------*/