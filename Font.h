#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include "Sprite.h"
#include "Texture.h"


class Font
{
private:

protected:
   Font();

public:
   ~Font();

   // Functions
   static void buildFontMap(void);

   // Variables
   static Texture* texture;
   static std::unordered_map<char, Sprite> fontMap;
};