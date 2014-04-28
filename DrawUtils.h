#include <vector>

// Load a file into an OpenGL texture, and return that texture.
GLuint glTexImageTGAFile( const char* filename, int* outWidth, int* outHeight );

// Draw the sprite
void glDrawSprite( GLuint tex, int x, int y, int w, int h );
void glDrawSprite( GLuint tex, int x, int y, int w, int h, GLfloat tu, GLfloat tv, GLfloat tileSizeX, GLfloat tileSizeY );
void glDrawCollider(int x, int y, int w, int h, std::vector<float> color);