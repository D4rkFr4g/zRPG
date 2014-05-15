#pragma once
#include <unordered_map>
#include "Menu.h"


class BattleMenu
{
public:
   BattleMenu();
   ~BattleMenu();

   // Variables
   static std::unordered_map<std::string, Menu> menus;
};

