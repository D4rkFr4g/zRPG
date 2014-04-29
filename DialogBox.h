#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "Sprite.h"

class DialogBox
{
public:
   // Constructors
   DialogBox(void);
   DialogBox(int x, int y, int width, int height, std::string text, bool isBorderVisible);
   ~DialogBox(void);
   
   // Variables
   static Texture* texture;
   int width;
   int height;
   std::string text;
   bool isBorderVisible;

private:
   std::vector<Sprite> borderSprites;
   std::vector<Sprite> fontSprites;
};

