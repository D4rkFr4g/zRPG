#include "dialogManager.h"


std::vector<DialogBox>* dialogManager::dialogQueue;
std::unordered_map<std::string, std::vector<DialogBox>> dialogManager::dialogs;
int* dialogManager::screenWidth;
int* dialogManager::screenHeight;

/*-----------------------------------------------*/
dialogManager::dialogManager()
{
}
/*-----------------------------------------------*/
dialogManager::~dialogManager()
{
}
/*-----------------------------------------------*/
void dialogManager::initDialogs()
{
   int cols = (int) floor(*screenWidth / DialogBox::texture->cellWidth);
   int rows = 12;
   int x = 0;
   int y = *screenHeight - (rows * DialogBox::texture->cellHeight);
   
   DialogBox dBox;
   std::vector<DialogBox> dBoxes;
   
   /*-----------------------------------------------*/
   std::string text = "In a stunning turn of original events, the Princess Zelda of Hyrule has been captured by a Dark Lord (surprising, I know).";
   text += "\nLink must set out on a quest to rescue the Princess from the evil clutches of this vile enemy to restore…";
   
   dBox = DialogBox(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   text = "the Princess to her throne, thereby saving the land of Hyrule once again.";
   text += " Shall Link restore balance to the peaceful land of Hyrule as a fierce warrior with a vengeance?";
   text += " Or shall he burn his foes to a crisp as a fireball - slinging mage?";
   text += " The playstyle…";
   
   dBox = DialogBox(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   text = "is up to you to decide. But it is a given that this quest will not be an easy one…";
   dBox = DialogBox(x, y, rows, cols, text, true, true);
   dBoxes.push_back(dBox);

   dialogs["intro"] = dBoxes;
   /*-----------------------------------------------*/
}
/*-----------------------------------------------*/
void dialogManager::dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState)
{
   /* PURPOSE:		Process keyboard commands as they relate to dialog boxes
      RECEIVES:	kbState - current state of the keyboard
                  kbPrevState - Previous frame state of the keyboard
      RETURNS:
      REMARKS:
   */

   static bool isPaused = false;

   // Pause DialogBox
   if (kbState[SDL_SCANCODE_P] && !kbPrevState[SDL_SCANCODE_P])
   {
      if (!isPaused)
      {
         int rows = 10;
         int cols = 30;
         int x = 0;
         int y = 10;

         center(&x, &y, rows, cols);
         dialogQueue->push_back(DialogBox(x, y, rows, cols, "\t\tPause this Game \"Yo!\" ( @ ) \n\bChoose: \n> Save\n\tExit", true, true));
         //dialogQueue->push_back(DialogBox(x, y, rows, cols, "abcdedfghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n!\"~$&'(),-.^…0123456789:;<=>?@", true, false));
         isPaused = true;
      }
      else
      {
         dialogQueue->pop_back();
         isPaused = false;
      }
   }

   if (kbState[SDL_SCANCODE_0] && !kbPrevState[SDL_SCANCODE_0])
   {
      loadDialogQueue(dialogs["intro"]);
   }
   
   if (kbState[SDL_SCANCODE_J] && !kbPrevState[SDL_SCANCODE_J] && !isPaused)
   {
      if (dialogQueue->size() > 0 && dialogQueue->back().isInputNeeded == true)
         dialogQueue->pop_back();
   }
}
/*-----------------------------------------------*/
void dialogManager::center(int* x, int* y, int rows, int cols)
{
   /* PURPOSE:		calculates x and y coordinate to center dialog box on screen
      RECEIVES:   x - x screen coordinate
      y - y screen coordinate
      rows - number of Rows in DialogBox
      cols - number of columns in DialogBox
      RETURNS:
      REMARKS:
   */

   int cellWidth = DialogBox::texture->cellWidth;
   int cellHeight = DialogBox::texture->cellHeight;

   int screenCenterX = (int) floor(*screenWidth / 2.0);
   int screenCenterY = (int) floor(*screenHeight / 2.0);

   int halfTexWidth = (int) floor((cols * cellWidth) / 2.0);
   int halfTexHeight = (int) floor((rows * cellHeight) / 2.0);

   *x = screenCenterX - halfTexWidth;
   *y = screenCenterY - halfTexHeight;
}
/*-----------------------------------------------*/
void dialogManager::centerX(int* x, int rows, int cols)
{
   /* PURPOSE:		calculates x coordinate to center dialog box on screen
      RECEIVES:   x - x screen coordinate
      y - y screen coordinate
      rows - number of Rows in DialogBox
      cols - number of columns in DialogBox

      RETURNS:
      REMARKS:
   */

   int y = 0;
   center(x, &y, rows, cols);
}
/*-----------------------------------------------*/
void dialogManager::centerY(int* y, int rows, int cols)
{
   /* PURPOSE:		calculates y coordinate to center dialog box on screen
      RECEIVES:   x - x screen coordinate
      y - y screen coordinate
      rows - number of Rows in DialogBox
      cols - number of columns in DialogBox

      RETURNS:
      REMARKS:
   */

   int x = 0;
   center(&x, y, rows, cols);
}
/*-----------------------------------------------*/
void dialogManager::loadDialogQueue(std::vector<DialogBox> dialogSequence)
{
   /* PURPOSE:		Loads dialogSequence into the dialogQueue
      RECEIVES:   dialogSequence - a vector of dialog boxes
      RETURNS:
      REMARKS:    Loads the sequence backwards
   */

   for (int i = dialogSequence.size() - 1; i >= 0; i--)
   {
      dialogQueue->push_back(dialogSequence[i]);
   }
}
/*-----------------------------------------------*/