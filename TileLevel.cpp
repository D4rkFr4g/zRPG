#include "TileLevel.h"


TileLevel::TileLevel(void)
{
}
/*-----------------------------------------------*/
TileLevel::TileLevel(int width, int height, int tilesWidth, int tilesHeight)
{
	this->width = width; // Columns
	this->height = height; // Rows
	this->tilesWidth = tilesWidth;
	this->tilesHeight = tilesHeight;
	this->tileArray.reserve(width * height);
	tile_x = 0;
	tile_y = 0;
	tile_xStop = 0;
	tile_yStop = 0;
	startX = 0;
	startY = 0;
   name = "";
}
/*-----------------------------------------------*/
TileLevel::~TileLevel(void)
{
}
/*-----------------------------------------------*/
void TileLevel::drawLevel(int camX, int camY, int screenWidth, int screenHeight)
{
	/* PURPOSE:		Draws tile level based on camera offset 
		RECEIVES:	camX - Horizontal position of camera
						camY - Vertical position of camera
						screenWidth - Width of screen resolution
						screenHeight - Height of screen resolution
		RETURNS:		 
		REMARKS:		 
	*/

	setBounds(camX, camY, screenWidth, screenHeight);
	
	for (int i = tile_y; i < tile_yStop; i++)
	{
		for (int j = tile_x; j < tile_xStop; j++)
		{
			Sprite * tile = &tileArray[(i * width) + j];
			tile->drawUV(camX, camY);
			
			/*
			if (tile->type != 0)
				tile->drawCollider(camX, camY);
			*/
		}
	}
}
/*-----------------------------------------------*/
std::vector<int>* TileLevel::checkCollision(AABB *box)
{
	/* PURPOSE:		Checks for collions of AABB box with surrounding tiles 
		RECEIVES:	box - AABB collider box to check collisions against 
		RETURNS:		vector of tileArray indexes corresponding to all collisions 
		REMARKS:		Only checks for collisions within a set distance from AABB box 
						 
	*/

	std::vector<int>* collisions = new std::vector<int>();
	int overrage = 10;

	int x = box->x - overrage;
	int y = box->y - overrage;
	int width = box->w + overrage;
	int height = box->h + overrage;
	
	setBounds(x, y, width, height);

	for (int i = tile_y; i < tile_yStop; i++)
	{
		for (int j = tile_x; j < tile_xStop; j++)
		{
			int position = (i * this->width) + j;
			Sprite* tile = &tileArray[position];
         if (tile->type != 0 && tile->collider.AABBIntersect(box))
            collisions->push_back(position);
         else
            tile->hasCollided = false;
		}
	}
	return collisions;
}
/*-----------------------------------------------*/
void TileLevel::setBounds(int x, int y, int width, int height)
{
	/* PURPOSE:		Sets bounds to use when searching the tileArray 
		RECEIVES:	x - Horizontal position to start search
						y - Vertical position to start search
						width - Horizontal distance to check
						height - Vertical distance to check
		RETURNS:		
		REMARKS:		 
	*/

	// Calculate which tiles to draw
	tile_x = (int) floor((float) x / tilesWidth);
	tile_y = (int) floor((float) y / tilesHeight);
	tile_xStop = tile_x + (int) ceil((float) (width + tilesWidth) / tilesWidth);
	tile_yStop = tile_y + (int) ceil((float) (height + tilesHeight) / tilesHeight);

	// Only try to draw tiles in array
	if (tile_x < 0)
		tile_x = 0;
	else if (tile_x > this->width)
		tile_x = this->width;
	if (tile_y < 0)
		tile_y = 0;
	else if (tile_y > this->height)
		tile_y = this->height;
	if (tile_xStop > this->width)
		tile_xStop = this->width;
	if (tile_yStop > this->height)
		tile_yStop = this->height;
}