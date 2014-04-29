#include "Texture.h"


Texture::Texture(void)
{
}


Texture::~Texture(void)
{
}

Texture::Texture(GLuint texture, int width, int height)
{
   this->texture = texture;
   this->width = width;
   this->height = height;
}