#include "dialogManager.h"


std::vector<DialogBox>* dialogManager::dialogQueue;
/*-----------------------------------------------*/
dialogManager::dialogManager()
{
}
/*-----------------------------------------------*/
dialogManager::~dialogManager()
{
}
/*-----------------------------------------------*/
void dialogManager::dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState)
{
   static bool isPaused = false;

   // Pause DialogBox
   if (kbState[SDL_SCANCODE_P] && !kbPrevState[SDL_SCANCODE_P])
   {
      if (!isPaused)
      {
         dialogQueue->push_back(DialogBox(0, 0, 10, 20, "Pause", true));
         isPaused = true;
      }
      else
      {
         dialogQueue->pop_back();
         isPaused = false;
      }
   }
}
/*-----------------------------------------------*/