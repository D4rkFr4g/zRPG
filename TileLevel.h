#pragma once
#include "Sprite.h"
#include <vector>

class TileLevel
{
public:
	TileLevel(void);
	TileLevel(int width, int height, int tileWidth, int tileHeight);
	~TileLevel(void);

	// Functions
	void drawLevel(int camX, int camY, int screenWidth, int screenHeight);
	std::vector<int>* checkCollision(AABB *box);

	// Variables
	int tilesWidth, tilesHeight;
	int width, height;
	int startX, startY;
	int tile_x, tile_y, tile_xStop, tile_yStop;
	std::vector<Sprite> tileArray;
	std::vector<int> collidableTiles; 

private:

	// Functions
	void setBounds(int x, int y, int width, int height);
};

