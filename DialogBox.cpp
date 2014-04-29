#include "DialogBox.h"


static Texture* texture;

/*-----------------------------------------------*/
DialogBox::DialogBox(void)
{
}
/*-----------------------------------------------*/
DialogBox::~DialogBox(void)
{
}
/*-----------------------------------------------*/
DialogBox::DialogBox(int x, int y, int width, int height, std::string text, bool isBorderVisible)
{
   /* PURPOSE:		Creates a DialogBox to be printed to the screen 
		RECEIVES:	x - x window coordinate
                  y - y window coordinate
                  width - width of dialogBox based on cell size of texture
                  height - height of dialogBox based on cell size of texture
                  text - text to be printed in the DialogBox
                  isBorderVisible - If false then it will only print text to the screen
		RETURNS:		Object of DialogBox
		REMARKS:		
	*/

   this->width = width;
   this->height = height;
   this->text = text;
   isBorderVisible = isBorderVisible;
}