#pragma once
#include <vector>
#include <SDL.h>
#include "DialogBox.h"


class dialogManager
{
public:
   ~dialogManager();

   // Functions
   static void dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState);

   // Variables
   static std::vector<DialogBox>* dialogQueue;

protected:
   dialogManager();

};

