#pragma once
#include<GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Sprite.h"
#include "TileLevel.h"

class tileLoader
{
public:
	static void loadTiles(const char* filename, TileLevel *level);
};

