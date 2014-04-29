#pragma once
#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include "DrawUtils.h"
#include "Texture.h"

class textureLoader
{
public:
   ~textureLoader(void);
   static void loadTextures(std::unordered_map<std::string, Texture>* g_textures);

protected:
   textureLoader(void);
};

