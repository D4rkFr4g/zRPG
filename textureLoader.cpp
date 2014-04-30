#include "textureLoader.h"


textureLoader::textureLoader(void)
{
}
/*-----------------------------------------------*/
textureLoader::~textureLoader(void)
{
}
/*-----------------------------------------------*/
void textureLoader::loadTextures(std::unordered_map<std::string, Texture>* g_textures)
{
   int* width = new int;
	int* height = new int;
   
   GLuint texture = glTexImageTGAFile("./Sprites/spriteSheet_chicken.tga", NULL, NULL);
   (*g_textures)["chicken"] = Texture(texture, 64, 64, 32, 32); 

   texture = glTexImageTGAFile("./Sprites/link_Sprites.tga", width, height);
   (*g_textures)["link"] = Texture(texture, *width, *height);

   texture = glTexImageTGAFile("./Sprites/dialog16x16.tga", width, height);
   (*g_textures)["dialog"] = Texture(texture, *width, *height, 16, 16);

   texture = glTexImageTGAFile("./Sprites/lttp_font2x2.tga", width, height);
   (*g_textures)["font"] = Texture(texture, *width, *height);
}
/*-----------------------------------------------*/