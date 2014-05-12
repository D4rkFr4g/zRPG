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

   GLuint texture = glTexImageTGAFile("./Sprites/link_Sprites.tga", NULL, NULL);
   (*g_textures)["link"] = Texture(texture, *width, *height, 32, 32);

   texture = glTexImageTGAFile("./Sprites/spriteSheet_chicken.tga", width, height);
   (*g_textures)["chicken"] = Texture(texture, 64, 64, 32, 32);

   texture = glTexImageTGAFile("./Sprites/pig_guard.tga", width, height);
   (*g_textures)["guard"] = Texture(texture, *width, *height, 64, 64);

   texture = glTexImageTGAFile("./Sprites/red_knight.tga", width, height);
   (*g_textures)["knight"] = Texture(texture, *width, *height, 64, 64);

   texture = glTexImageTGAFile("./Sprites/ganon.tga", width, height);
   (*g_textures)["ganon"] = Texture(texture, *width, *height, 128, 128);

   texture = glTexImageTGAFile("./Sprites/link_battle.tga", width, height);
   (*g_textures)["link_battle"] = Texture(texture, *width, *height, 576, 64);

   texture = glTexImageTGAFile("./Sprites/chicken_battle_attack.tga", width, height);
   (*g_textures)["chicken_attack"] = Texture(texture, *width, *height, 576, 64);

   texture = glTexImageTGAFile("./Sprites/guard_battle_attack.tga", width, height);
   (*g_textures)["guard_attack"] = Texture(texture, *width, *height, 576, 64);

   texture = glTexImageTGAFile("./Sprites/knight_battle_attack.tga", width, height);
   (*g_textures)["knight_attack"] = Texture(texture, *width, *height, 576, 64);

   texture = glTexImageTGAFile("./Sprites/ganon_battle_jumpAttack.tga", width, height);
   (*g_textures)["ganon_jumpAttack"] = Texture(texture, *width, *height, 576, 128);

   texture = glTexImageTGAFile("./Sprites/dialog16x16.tga", width, height);
   (*g_textures)["dialog"] = Texture(texture, *width, *height, 16, 16);

   texture = glTexImageTGAFile("./Sprites/lttp_font2x2.tga", width, height);
   (*g_textures)["font"] = Texture(texture, *width, *height, 2, 2);
}
/*-----------------------------------------------*/