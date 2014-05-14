#include "bucketManager.h"

int* bucketManager::windowWidth;
int* bucketManager::windowHeight;
int* bucketManager::windowMaxWidth;
int* bucketManager::windowMaxHeight;

/*-----------------------------------------------*/
bucketManager::bucketManager()
{
}
/*-----------------------------------------------*/
bucketManager::~bucketManager()
{
}
/*-----------------------------------------------*/
void bucketManager::init(int* _windowWidth, int* _windowHeight, int* _windowMaxWidth, int* _windowMaxHeight)
{
   /* PURPOSE:		Initializes bucketManager with needed variables
      RECEIVES:
      RETURNS:
      REMARKS:
   */

   windowWidth = _windowWidth;
   windowHeight = _windowHeight;
   windowMaxWidth = _windowMaxWidth;
   windowMaxHeight = _windowMaxHeight;
}
/*-----------------------------------------------*/
int bucketManager::whichBucket(int x, int y)
{
   int column = (int)floor((float)x / *windowWidth);
   int row = (int)floor((float)y / (*windowHeight));
   int bucketWidth = (int)floor((float)*windowMaxWidth / *windowWidth);

   return (row * bucketWidth) + column;
}
/*-----------------------------------------------*/