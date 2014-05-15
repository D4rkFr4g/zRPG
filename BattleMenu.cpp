#include "BattleMenu.h"


/*-----------------------------------------------*/
BattleMenu::BattleMenu()
{

}
/*-----------------------------------------------*/
BattleMenu::BattleMenu(int numOfItems)
{
   menus["player"] = Menu(1);
   menus["action"] = Menu(4);
   menus["item"] = Menu(numOfItems);

   activeMenu = &menus["player"];

   end = menus.end();
}
/*-----------------------------------------------*/
BattleMenu::~BattleMenu()
{
}
/*-----------------------------------------------*/
void BattleMenu::setActiveMenu(std::string menuName)
{
   auto itr = menus.find(menuName);

   // Deactive previousMenu
   activeMenu->isActive = false;

   // Set the activeMenu
   if (itr != end)
      activeMenu = &itr->second;
}
/*-----------------------------------------------*/
void BattleMenu::next()
{
   activeMenu->next();
}
/*-----------------------------------------------*/
void BattleMenu::previous()
{
   activeMenu->previous();
}
/*-----------------------------------------------*/
int BattleMenu::getSelection()
{
   return activeMenu->getSelection();
}
/*-----------------------------------------------*/
void BattleMenu::reset()
{
   activeMenu->reset();
}
/*-----------------------------------------------*/
void BattleMenu::resetAll()
{
   auto itr = menus.begin();

   for (itr; itr != end; itr++)
      itr->second.resetAll();
}
/*-----------------------------------------------*/
int BattleMenu::getNumOfChoices()
{
   return activeMenu->numOfChoices;
}
/*-----------------------------------------------*/