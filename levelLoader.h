#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "TileLevel.h"
#include "tileLoader.h"


class levelLoader
{
protected:
   levelLoader();

public:
   // Constructors
   ~levelLoader();

   // Functions
   static void loadLevels(std::unordered_map<std::string, TileLevel>* levels, TileLevel** currentLevel);

   // Variables
   static std::vector<std::string> filenames;
};

