#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include "DialogBox.h"
#include "Font.h"


class dialogManager
{
private:
   // Functions
   static void loadDialogQueue(std::vector<DialogBox> dialogSequence);

public:
   ~dialogManager();

   // Functions
   static void initDialogs();
   static void dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState);
   static void center(int* x, int* y, int rows, int cols);
   static void centerX(int* x, int rows, int cols);
   static void centerY(int* y, int rows, int cols);

   // Variables
   static std::vector<DialogBox>* dialogQueue;
   static std::unordered_map<std::string, std::vector<DialogBox>> dialogs;
   static int* screenWidth;
   static int* screenHeight;
   static bool isActive;

protected:
   dialogManager();
};

