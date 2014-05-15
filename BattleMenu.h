#pragma once
#include <unordered_map>
#include "Menu.h"


class BattleMenu
{
private:
   std::unordered_map<std::string, Menu>::iterator end;
   Menu* activeMenu;

public:
   // Constructors
   BattleMenu();
   BattleMenu(int numOfItems);
   ~BattleMenu();

   // Functions
   void setActiveMenu(std::string menuName);
   void next();
   void previous();
   int getSelection();
   int getNumOfChoices();
   void reset();
   void resetAll();

   // Variables
   std::unordered_map<std::string, Menu> menus;
};

