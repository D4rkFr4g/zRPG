#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include <vector>
#include "Sprite.h"
#include "Texture.h"


class Font
{
private:
   static void tokenize(std::vector<std::string>* tokens, std::string s);
   static void loadWord(std::vector<Sprite>* fontSprites, std::string s, int* x, int y);

protected:
   Font();

public:
   ~Font();

   // Functions
   static void buildFontMap(void);
   static int stringWidth(std::string s);
   static void loadSprites(std::vector<Sprite>* fontSprites, std::string s, int x, int y, int width, int height);

   // Variables
   static Texture* texture;
   static std::unordered_map<char, Sprite> fontMap;
   static int maxFontHeight;
   static int padding;
};