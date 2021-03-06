#include "DialogContainer.h"


Texture* DialogContainer::texture;

/*-----------------------------------------------*/
DialogContainer::DialogContainer(void)
{
}
/*-----------------------------------------------*/
DialogContainer::~DialogContainer(void)
{
}
/*-----------------------------------------------*/
DialogContainer::DialogContainer(int x, int y, int rows, int cols, std::string text, bool isBorderVisible, bool isInputRequired)
{
   /* PURPOSE:		Creates a DialogContainer to be printed to the screen 
		RECEIVES:	x - x window coordinate
                  y - y window coordinate
                  width - width of DialogContainer based on cell size of texture
                  height - height of DialogContainer based on cell size of texture
                  text - text to be printed in the DialogContainer
                  isBorderVisible - If false then it will only print text to the screen
		RETURNS:		Object of DialogContainer
		REMARKS:		
	*/

   this->x = x;
   this->y = y;
   this->rows = rows;
   this->cols = cols;
   this->text = text;
   this->isBorderVisible = isBorderVisible;
   this->isInputNeeded = isInputRequired;

   loadBorderSprites();
   loadFontSprites();
}
/*-----------------------------------------------*/
void DialogContainer::display(void)
{
   /* PURPOSE:		Displays dialog box to the screen
      RECEIVES:	
      RETURNS:		
      REMARKS:
   */

   if (isBorderVisible)
   {
      for (int i = 0; i < (int) borderSprites.size(); i++)
         borderSprites[i].drawUV(0, 0);
   }

   for (int i = 0; i < (int) fontSprites.size(); i++)
      fontSprites[i].drawUV(0,0);
}
/*-----------------------------------------------*/
void DialogContainer::loadBorderSprites(void)
{
   /* PURPOSE:		Creates sprites to make up the dialog box
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   // Default to minimum size if too small
   if (this->rows < 2)
      this->rows = 2;
   if (this->cols < 2)
      this->cols = 2;

   int rows = this->rows;// (int)floor(this->rows / texture->uSize);
   int cols = this->cols;// (int)floor(this->cols / texture->vSize);

   int xPos = x;
	int yPos = y;
   int cellWidth = texture->cellWidth;
   int cellHeight = texture->cellHeight;
   float uSize = texture->uSize;
   float vSize = texture->vSize;
   GLfloat tu = 0;
   GLfloat tv = 0;
   GLuint* tex = &texture->texture;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
         // Set texture coordinate positions for dialog box tiles
         // Top Row
         if (i == 0)
         {
            // Top Left
            if (j == 0)
            {
               tu = 0 * uSize;
               tv = 2 * vSize;
            }
            // Top Right
            else if (j == cols - 1)
            {
               tu = 2 * uSize;
               tv = 2 * vSize;
            }
            // Top Middle
            else
            {
               tu = 1 * uSize;
               tv = 2 * vSize;
            }
         }
         // Bottom Row
         else if (i == rows - 1)
         {
            // Bottom Left
            if (j == 0)
            {
               tu = 0 * uSize;
               tv = 0 * vSize;
            }
            // Bottom Right
            else if (j == cols - 1)
            {
               tu = 2 * uSize;
               tv = 0 * vSize;
            }
            // Bottom Middle
            else
            {
               tu = 1 * uSize;
               tv = 0 * vSize;
            }
         }
         // Middle Row
         else
         {
            // Middle Left
            if (j == 0)
            {
               tu = (GLfloat)0 * uSize;
               tv = (GLfloat)1 * vSize;
            }
            // Middle Right
            else if (j == cols - 1)
            {
               tu = (GLfloat)2 * uSize;
               tv = (GLfloat)1 * vSize;
            }
            // Middle Middle
            else
            {
               tu = (GLfloat) 1 * uSize;
               tv = (GLfloat)1 * vSize;
            }
         }

         Sprite s = Sprite(tex, xPos, yPos, cellWidth, cellHeight, tu, tv, uSize, vSize);
         borderSprites.push_back(s);

         xPos += cellWidth;
		}
      xPos = x;
      yPos += cellHeight;
	}
}
/*-----------------------------------------------*/
void DialogContainer::loadFontSprites(void)
{
   /* PURPOSE:		Loads fonts into the DialogContainer
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   int cellWidth = texture->cellWidth;
   int cellHeight = texture->cellHeight;
   
   int startX = x + cellWidth;
   int startY = y + cellHeight;

   fontSprites.clear();
   Font::loadSprites(&fontSprites, text, startX, startY, (cols-3) * cellWidth, (rows-2)*cellHeight);
}
/*-----------------------------------------------*/