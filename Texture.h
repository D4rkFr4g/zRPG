#pragma once
#include <GL\glew.h>

class Texture
{
public:
   Texture(void);
   Texture(GLuint texture, int width, int height);
   Texture(GLuint texture, int width, int height, int cellWidth, int cellHeight);
   ~Texture(void);

   // Variables
   GLuint texture;
   int width;
   int height;
   float uSize;
   float vSize;
   int cellWidth;
   int cellHeight;

};

