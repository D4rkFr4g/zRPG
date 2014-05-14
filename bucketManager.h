#pragma once
#include <cmath>
#include <vector>
#include "Sprite.h"

class bucketManager
{
protected:
   bucketManager();

public:
   ~bucketManager();

   // Functions
   static void init(std::vector<std::vector<Sprite*>>* spriteBuckets, int* windowWidth, int* windowHeight, int* windowMaxWidth, int* windowMaxHeight);
   static int whichBucket(int x, int y);

   // Variables
   static int* windowHeight;
   static int* windowWidth;
   static int* windowMaxWidth;
   static int* windowMaxHeight;
   static std::vector<std::vector<Sprite*>>* spriteBuckets;
      
};

