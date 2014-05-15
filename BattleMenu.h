#pragma once
#include <unordered_map>
#include "Menu.h"


class BattleMenu
{
private:
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
   void turnOff();
   void updateSize(std::string menuName, int size);
   void decrementEnemies();
   int getSelectedEnemy();
   int getSelectedItem();
   int getSelectedAction();
   bool isActive(std::string menuName);

   // Variables
   std::unordered_map<std::string, Menu> menus;
};

