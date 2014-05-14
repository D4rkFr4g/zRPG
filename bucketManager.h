#pragma once
#include <cmath>

class bucketManager
{
protected:
   bucketManager();

public:
   ~bucketManager();

   // Functions
   static void init(int* windowWidth, int* windowHeight, int* windowMaxWidth, int* windowMaxHeight);
   static int whichBucket(int x, int y);

   // Variables
   static int* windowHeight;
   static int* windowWidth;
   static int* windowMaxWidth;
   static int* windowMaxHeight;
      
};

