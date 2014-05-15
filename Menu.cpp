#include "Menu.h"


/*-----------------------------------------------*/
Menu::Menu()
{
}
/*-----------------------------------------------*/
Menu::Menu(int numChoices)
{
   this->numOfChoices = numChoices;
   this->selection = 0;
   this->isActive = false;
}
Menu::~Menu()
{
}
/*-----------------------------------------------*/
void Menu::next()
{
   /* PURPOSE:		Sets selection to next choice
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   if (numOfChoices != 0)
      selection = (++selection) % numOfChoices;
}
/*-----------------------------------------------*/
void Menu::previous()
{
   /* PURPOSE:		Sets selection to previous choice
      RECEIVES:   
      RETURNS:
      REMARKS:
   */

   if (numOfChoices != 0)
   {
      selection = (--selection) % numOfChoices;

      if (selection < 0)
         selection += numOfChoices;
   }
}
/*-----------------------------------------------*/
void Menu::setActive(bool value)
{
   /* PURPOSE:		Set if the menu is currently active
      RECEIVES:   value - true if menu is active otherwise false
      RETURNS:
      REMARKS:
   */

   isActive = value;
}
/*-----------------------------------------------*/
int Menu::getSelection()
{
   /* PURPOSE:		Getter for Menu selection
      RECEIVES:
      RETURNS:    number related to current selection
      REMARKS:
      */

   return selection;
}
/*-----------------------------------------------*/
void Menu::reset()
{
   /* PURPOSE:		Resets the menu selection to first choice
      RECEIVES:
      RETURNS:
      REMARKS:
      */

   selection = 0;
}
/*-----------------------------------------------*/
void Menu::resetAll()
{
   reset();
   setActive(false);
}
/*-----------------------------------------------*/