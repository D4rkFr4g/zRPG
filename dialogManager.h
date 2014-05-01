#pragma once
#include <vector>
#include <SDL.h>
#include "DialogBox.h"
#include "Font.h"


class dialogManager
{
public:
   ~dialogManager();

   // Functions
   static void dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState);
   static void center(int* x, int* y, int rows, int cols);
   static void centerX(int* x, int rows, int cols);
   static void centerY(int* y, int rows, int cols);

   // Variables
   static std::vector<DialogBox>* dialogQueue;
   static int* screenWidth;
   static int* screenHeight;

protected:
   dialogManager();
};

