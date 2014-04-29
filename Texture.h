#pragma once
#include <GL\glew.h>

class Texture
{
public:
   Texture(void);
   Texture(GLuint texture, int width, int height);
   ~Texture(void);

   // Variables
   GLuint texture;
   int width;
   int height;

};

