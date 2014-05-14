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

   // Functions
   static void loadTextures(std::unordered_map<std::string, Texture>* g_textures);
   static Texture* getTexture(std::string name);

   // Variables
   static std::unordered_map<std::string, Texture>* textures;

protected:
   textureLoader(void);
};

