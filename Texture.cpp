#include "Texture.h"


/*-----------------------------------------------*/
Texture::Texture(void)
{
}
/*-----------------------------------------------*/
Texture::~Texture(void)
{
}
/*-----------------------------------------------*/
Texture::Texture(GLuint texture, int width, int height)
{
   this->texture = texture;
   this->width = width;
   this->height = height;
}
/*-----------------------------------------------*/
Texture::Texture(GLuint texture, int width, int height, int cellWidth, int cellHeight)
{
   this->texture = texture;
   this->width = width;
   this->height = height;
   this->cellWidth = cellWidth;
   this->cellHeight = cellHeight;

   this->uSize = 1.0 / (width / cellWidth);
   this->vSize = 1.0 / (height / cellHeight);
}