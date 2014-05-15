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
}
/*-----------------------------------------------*/
BattleMenu::~BattleMenu()
{
}
/*-----------------------------------------------*/
void BattleMenu::setActiveMenu(std::string menuName)
{
   std::unordered_map<std::string, Menu>::iterator itr = menus.find(menuName);
   std::unordered_map<std::string, Menu>::iterator tmp = menus.end();
   // Deactive previousMenu
   activeMenu->isActive = false;

   // Set the activeMenu
   if (itr != tmp)
   {
      //Menu* m = &itr->second;
      activeMenu = &itr->second;
      activeMenu->isActive = true;
   }
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
   std::unordered_map<std::string, Menu>::iterator itr = menus.begin();
   std::unordered_map<std::string, Menu>::iterator end = menus.end();

   for (itr; itr != end; itr++)
      itr->second.resetAll();
}
/*-----------------------------------------------*/
int BattleMenu::getNumOfChoices()
{
   return activeMenu->numOfChoices;
}
/*-----------------------------------------------*/
void BattleMenu::turnOff()
{
   activeMenu->isActive = false;
}
/*-----------------------------------------------*/
void BattleMenu::updateSize(std::string menuName, int size)
{
   menus[menuName] = Menu(size);
}
/*-----------------------------------------------*/
void BattleMenu::decrementEnemies()
{
   menus["enemy"].numOfChoices--;
}
/*-----------------------------------------------*/
int BattleMenu::getSelectedEnemy()
{
   return menus["enemy"].getSelection();
}
/*-----------------------------------------------*/
int BattleMenu::getSelectedItem()
{
   return menus["item"].getSelection();
}
/*-----------------------------------------------*/
int BattleMenu::getSelectedAction()
{
   return menus["action"].getSelection();
}
/*-----------------------------------------------*/
bool BattleMenu::isActive(std::string menuName)
{
   return menus[menuName].isActive;
}
/*-----------------------------------------------*/