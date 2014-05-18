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
   filenames.push_back("lttr_title");
   filenames.push_back("overworld");
   filenames.push_back("battle_easy");
   filenames.push_back("battle_medium");
   filenames.push_back("battle_hard");
   filenames.push_back("dungeon_1");
   filenames.push_back("castle");
   filenames.push_back("battle_boss");

   for (int i = 0; i < (int)filenames.size(); i++)
   {
      string name = filenames[i];
      (*levels)[name] = TileLevel();
      TileLevel* level = &(*levels)[name];
      string filename = "./Levels/" + name + ".txt";
      tileLoader::loadTiles(filename.c_str(), level);
      level->name = name;

      // Find start position
      int startTile = 4;
      for (int i = 0; i < (int)level->collidableTiles.size(); i++)
      {
         int index = level->collidableTiles[i];
         int type = level->tileArray[index].type;
         if (type == startTile)
         {
            level->startX = level->tileArray[index].x - level->tilesWidth;
            level->startY = level->tileArray[index].y;
         }
      }
   }

   // Load first level and clear filenames vector
   *currentLevel = &(*levels)[filenames[0]];
   filenames.clear();
}
/*-----------------------------------------------*/