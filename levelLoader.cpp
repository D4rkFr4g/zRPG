#include "levelLoader.h"

std::vector<std::string> levelLoader::filenames;
/*-----------------------------------------------*/
levelLoader::levelLoader()
{
}
/*-----------------------------------------------*/
levelLoader::~levelLoader()
{
}
/*-----------------------------------------------*/
void levelLoader::loadLevels(std::unordered_map<std::string, TileLevel>* levels, TileLevel** currentLevel)
{
   /* PURPOSE:		Loads all tile maps from flare.txt files
      RECEIVES:
      RETURNS:
      REMARKS:		Sets currentLevel to first map
   */

   using std::string;

   // Set all filnames to be used
   filenames.push_back("overworld");
   filenames.push_back("battle_test");

   for (int i = 0; i < (int)filenames.size(); i++)
   {
      string name = filenames[i];
      (*levels)[name] = TileLevel();
      TileLevel* level = &(*levels)[name];
      string filename = "./Levels/" + name + ".txt";
      tileLoader::loadTiles(filename.c_str(), level);
      level->name = name;
   }

   *currentLevel = &(*levels)[filenames[0]];
   filenames.clear();
}
/*-----------------------------------------------*/