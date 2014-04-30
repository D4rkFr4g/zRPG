#include "dialogManager.h"


std::vector<DialogBox>* dialogManager::dialogQueue;
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
void dialogManager::dialogKeyboard(const unsigned char* kbState, unsigned char* kbPrevState)
{
   static bool isPaused = false;

   // Pause DialogBox
   if (kbState[SDL_SCANCODE_P] && !kbPrevState[SDL_SCANCODE_P])
   {
      if (!isPaused)
      {
         int rows = 10;
         int cols = 20;
         int x = 0;
         int y = 10;

         center(&x, &y, rows, cols);
         dialogQueue->push_back(DialogBox(x, y, rows, cols, "Pause", true));
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

   int screenCenterX = floor(*screenWidth / 2.0);
   int screenCenterY = floor(*screenHeight / 2.0);

   int halfTexWidth = floor((cols * cellWidth) / 2.0);
   int halfTexHeight = floor((rows * cellHeight) / 2.0);

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