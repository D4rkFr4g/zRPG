#include "textureLoader.h"


textureLoader::textureLoader(void)
{
}


textureLoader::~textureLoader(void)
{
}

void textureLoader::loadTextures(std::unordered_map<std::string, Texture>* g_textures)
{
   using namespace std;

   int* width = new int;
	int* height = new int;
   
   GLuint texture = glTexImageTGAFile("./Sprites/spriteSheet_chicken.tga", NULL, NULL);
   (*g_textures)["chicken"] = Texture(texture, 64, 64); 

   texture = glTexImageTGAFile("./Sprites/contra_sheet.tga", width, height);
   (*g_textures)["contra"] = Texture(texture, *width, *height);
}
