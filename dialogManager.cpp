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
         dialogQueue->push_back(DialogBox(x, y, rows, cols, "Pause", true));
         isPaused = true;
      }
      else
      {
         dialogQueue->pop_back();
         isPaused = false;
      }
   }



   ////////////////////////////////////////////////////////////////////////////////
   // Debug font Sprites
   //    Won't  show up because of the order of printing the screen
   //    You would need to call this function after other draws.
   ////////////////////////////////////////////////////////////////////////////////
   if (0)
   {
      static std::vector<Sprite> sprites;
      //static bool isDisplayed = false;
      static Sprite s = Font::fontMap[' '];
      int x = 0;
      int y = 0;
      center(&x, &y, 0, 0);
      static Sprite r = Font::fontMap['I'];
      r.x = x - r.width;
      r.y = y-100;
      static std::unordered_map<char, Sprite>::iterator itr = Font::fontMap.begin();
      if (kbState[SDL_SCANCODE_KP_5] && !kbPrevState[SDL_SCANCODE_KP_5])
      {
         //if (!isDisplayed)
         //{
         char a = itr->first;
            s = itr->second;
            s.x = x;
            s.y = y - 100;
            //isDisplayed = true;
            itr++;
            if (itr == Font::fontMap.end())
               itr = Font::fontMap.begin();
         //}
      }
      r.drawUV(0, 0);
      s.drawUV(0, 0);
   }
   ////////////////////////////////////////////////////////////////////////////////
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