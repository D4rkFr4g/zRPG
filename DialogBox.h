#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Font.h"

class DialogBox
{
public:
   // Constructors
   DialogBox(void);
   DialogBox(int x, int y, int rows, int cols, std::string text, bool isBorderVisible);
   ~DialogBox(void);
   
   // Functions
   void display(void);
   void loadBorderSprites(void);
   void loadFontSprites(void);

   // Variables
   static Texture* texture;
   int x;
   int y;
   int width;
   int height;
   int rows;
   int cols;
   std::string text;
   bool isBorderVisible;

private:
   std::vector<Sprite> borderSprites;
   std::vector<Sprite> fontSprites;
};

