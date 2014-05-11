#pragma once
class Menu
{
public:
   Menu();
   Menu(int numChoices);
   ~Menu();

   // Functions
   void next();
   void previous();
   void setActive(bool value);
   int getSelection();
   void reset();

   // Variables
   bool isActive;

private:

   // Variables
   int numOfChoices;
   int selection;
};

