#include "Font.h"

Texture* Font::texture;
std::unordered_map<char, Sprite> Font::fontMap;
int Font::maxFontHeight;
int Font::padding;
/*-----------------------------------------------*/
Font::Font()
{
}
/*-----------------------------------------------*/
Font::~Font()
{
}
/*-----------------------------------------------*/
void Font::buildFontMap(void)
{
   /* PURPOSE:		Build font to Sprite mapping
      RECEIVES:	diff_time - milliseconds since last frame
      RETURNS:
      REMARKS:
   */

   int x = 0;
   int y = 0;
   int cellW = texture->cellWidth;
   int cellH = texture->cellHeight;
   GLfloat uSize = texture->uSize;
   GLfloat vSize = texture->vSize;
   GLuint* tex = &texture->texture;

   //                                  offsetY    pixelWidth pixelHeight   gridX     gridY      gridW      gridH
   // Lowercase
   fontMap['a'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 0 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // a
   fontMap['b'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 7 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // b
   fontMap['c'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 14 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // c
   fontMap['d'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 21 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // d
   fontMap['e'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 28 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // e
   fontMap['f'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 35 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // f
   fontMap['g'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 12 * cellH, 42 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // g
   fontMap['h'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 49 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // h
   fontMap['i'] = Sprite(tex, x, y, 0, 0 * cellH, 3 * cellW, 13 * cellH, 56 * uSize, 3 * vSize, 3 * uSize, 13 * vSize); // i
   fontMap['j'] = Sprite(tex, x, y, 0, 0 * cellH, 5 * cellW, 15 * cellH, 60 * uSize, 1 * vSize, 5 * uSize, 15 * vSize); // j
   fontMap['k'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 66 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // k
   fontMap['l'] = Sprite(tex, x, y, 0, 0 * cellH, 3 * cellW, 13 * cellH, 73 * uSize, 3 * vSize, 3 * uSize, 13 * vSize); // l
   fontMap['m'] = Sprite(tex, x, y, 0, 3 * cellH, 7 * cellW, 10 * cellH, 77 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // m
   fontMap['n'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 85 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // n
   fontMap['o'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 92 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // o
   fontMap['p'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 12 * cellH, 99 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // p
   fontMap['q'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 12 * cellH, 106 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // q
   fontMap['r'] = Sprite(tex, x, y, 0, 3 * cellH, 5 * cellW, 10 * cellH, 113 * uSize, 3 * vSize, 5 * uSize, 10 * vSize); // r
   fontMap['s'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 119 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // s
   fontMap['t'] = Sprite(tex, x, y, 0, 0 * cellH, 6 * cellW, 13 * cellH, 126 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // t
   fontMap['u'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 133 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // u
   fontMap['v'] = Sprite(tex, x, y, 0, 3 * cellH, 7 * cellW, 10 * cellH, 140 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // v
   fontMap['w'] = Sprite(tex, x, y, 0, 3 * cellH, 7 * cellW, 10 * cellH, 148 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // w
   fontMap['x'] = Sprite(tex, x, y, 0, 3 * cellH, 7 * cellW, 10 * cellH, 156 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // x
   fontMap['y'] = Sprite(tex, x, y, 0, 3 * cellH, 7 * cellW, 12 * cellH, 164 * uSize, 1 * vSize, 7 * uSize, 12 * vSize); // y
   fontMap['z'] = Sprite(tex, x, y, 0, 3 * cellH, 6 * cellW, 10 * cellH, 172 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // z
   // Uppercase
   fontMap['A'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 0 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // A
   fontMap['B'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 7 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // B
   fontMap['C'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 14 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // C
   fontMap['D'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 21 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // D
   fontMap['E'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 28 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // E
   fontMap['F'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 35 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // F
   fontMap['G'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 42 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // G
   fontMap['H'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 49 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // H
   fontMap['I'] = Sprite(tex, x, y, 3 * cellW, 13 * cellH, 56 * uSize, 19 * vSize, 3 * uSize, 13 * vSize); // I
   fontMap['J'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 60 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // J
   fontMap['K'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 67 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // K
   fontMap['L'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 74 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // L
   fontMap['M'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 81 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // M
   fontMap['N'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 89 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // N
   fontMap['O'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 96 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // O
   fontMap['P'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 103 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // P
   fontMap['Q'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 110 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // Q
   fontMap['R'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 117 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // R
   fontMap['S'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 124 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // S
   fontMap['T'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 131 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // T
   fontMap['U'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 139 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // U
   fontMap['V'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 146 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // V
   fontMap['W'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 154 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // W
   fontMap['X'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 162 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // X
   fontMap['Y'] = Sprite(tex, x, y, 7 * cellW, 13 * cellH, 170 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // Y
   fontMap['Z'] = Sprite(tex, x, y, 6 * cellW, 13 * cellH, 178 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // Z
   // Symbols
   fontMap['!'] = Sprite(tex, x, y, 0, 0 * cellW, 3 * cellW, 13 * cellH, 0 * uSize, 35 * vSize, 3 * uSize, 13 * vSize); // !
   fontMap['"'] = Sprite(tex, x, y, 0, -1 * cellW, 5 * cellW, 4 * cellH, 4 * uSize, 34 * vSize, 5 * uSize, 4 * vSize); // "
   fontMap['~'] = Sprite(tex, x, y, 0, 1 * cellW, 6 * cellW, 12 * cellH, 10 * uSize, 34 * vSize, 6 * uSize, 12 * vSize); // ~~~
   fontMap['&'] = Sprite(tex, x, y, 0, -1 * cellW, 6 * cellW, 14 * cellH, 17 * uSize, 34 * vSize, 6 * uSize, 14 * vSize); // &
   fontMap['|'] = Sprite(tex, x, y, 0, -1 * cellW, 6 * cellW, 14 * cellH, 24 * uSize, 34 * vSize, 6 * uSize, 14 * vSize); // |
   fontMap['\''] = Sprite(tex, x, y, 0, -1 * cellH, 4 * cellW, 6 * cellH, 31 * uSize, 43 * vSize, 4 * uSize, 6 * vSize); // '
   fontMap['('] = Sprite(tex, x, y, 0, -1 * cellW, 6 * cellW, 15 * cellH, 36 * uSize, 34 * vSize, 6 * uSize, 15 * vSize); // (
   fontMap[')'] = Sprite(tex, x, y, 0, -1 * cellW, 6 * cellW, 15 * cellH, 43 * uSize, 34 * vSize, 6 * uSize, 15 * vSize); // )
   fontMap[','] = Sprite(tex, x, y, 0, 9 * cellW, 4 * cellW, 6 * cellH, 50 * uSize, 33 * vSize, 4 * uSize, 6 * vSize); // ,
   fontMap['-'] = Sprite(tex, x, y, 0, 5 * cellW, 6 * cellW, 3 * cellH, 54 * uSize, 42 * vSize, 6 * uSize, 3 * vSize); // -
   fontMap['.'] = Sprite(tex, x, y, 0, 9 * cellW, 4 * cellW, 4 * cellH, 56 * uSize, 35 * vSize, 4 * uSize, 4 * vSize); // .
   fontMap['_'] = Sprite(tex, x, y, 0, 9 * cellW, 6 * cellW, 4 * cellH, 61 * uSize, 35 * vSize, 6 * uSize, 4 * vSize); // ...
   fontMap['0'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 68 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 0
   fontMap['1'] = Sprite(tex, x, y, 0, 0 * cellW, 4 * cellW, 13 * cellH, 75 * uSize, 35 * vSize, 4 * uSize, 13 * vSize); // 1
   fontMap['2'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 80 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 2
   fontMap['3'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 87 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 3
   fontMap['4'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 94 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 4
   fontMap['5'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 101 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 5
   fontMap['6'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 108 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 6
   fontMap['7'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 115 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 7
   fontMap['8'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 122 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 8
   fontMap['9'] = Sprite(tex, x, y, 0, 0 * cellW, 6 * cellW, 13 * cellH, 129 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 9
   fontMap[':'] = Sprite(tex, x, y, 0, 3 * cellW, 4 * cellW, 10 * cellH, 136 * uSize, 35 * vSize, 4 * uSize, 10 * vSize); // :
   fontMap[';'] = Sprite(tex, x, y, 0, 3 * cellW, 4 * cellW, 12 * cellH, 141 * uSize, 33 * vSize, 4 * uSize, 12 * vSize); // ;
   fontMap['<'] = Sprite(tex, x, y, 0, 2 * cellW, 6 * cellW, 9 * cellH, 146 * uSize, 37 * vSize, 6 * uSize, 9 * vSize); // <
   fontMap['='] = Sprite(tex, x, y, 0, 3 * cellW, 6 * cellW, 7 * cellH, 153 * uSize, 37 * vSize, 6 * uSize, 7 * vSize); // =
   fontMap['>'] = Sprite(tex, x, y, 0, 2 * cellW, 6 * cellW, 9 * cellH, 160 * uSize, 36 * vSize, 6 * uSize, 9 * vSize); // >
   fontMap['?'] = Sprite(tex, x, y, 0, 0 * cellW, 7 * cellW, 13 * cellH, 167 * uSize, 35 * vSize, 7 * uSize, 13 * vSize); // ?
   fontMap['@'] = Sprite(tex, x, y, 0, -1 * cellW, 16 * cellW, 14 * cellH, 175 * uSize, 34 * vSize, 16 * uSize, 14 * vSize); // @
   fontMap['\"'] = Sprite(tex, x, y, 0, 0 * cellW, 5 * cellW, 1 * cellH, 0 * uSize, 0 * vSize, 5 * uSize, 1 * vSize); // space
   fontMap['\t'] = Sprite(tex, x, y, 0, 0 * cellW, 15 * cellW, 1 * cellH, 0 * uSize, 0 * vSize, 15 * uSize, 1 * vSize); // tab

   // Set max font height
   for (int i = 0; i < fontMap.size(); i++)
   {
      if (fontMap[i].height > maxFontHeight)
         maxFontHeight = fontMap[i].height;
   }
   padding = 5;
}
/*-----------------------------------------------*/
int Font::stringWidth(std::string s)
{
   /* PURPOSE:		Process keyboard commands as they relate to dialog boxes
      RECEIVES:	s - string to check font width
      RETURNS:    pixel size of total string width
      REMARKS:    This ignores characters not in the fontMap
   */

   int totalWidth = 0;

   for (int i = 0; i < s.length(); i++)
   {
      if (fontMap[s[i]].width != NULL)
         totalWidth += fontMap[s[i]].width;
   }

   return totalWidth;
}
/*-----------------------------------------------*/
void Font::loadSprites(std::vector<Sprite>* fontSprites, std::string s, int x, int y, int width, int height)
{
   using std::string;

   //y += maxFontHeight + 2;
   y += 2;
   std::vector<std::string> tokens;
   tokenize(&tokens, s);
   int spriteX = x;
   int spriteY = y;

   for (int i = 0; i < tokens.size(); i++)
   {
      string s = tokens[i];
      
      if (s.compare("\n") == 0)
      {
         spriteX = x;
         spriteY += maxFontHeight + padding;
      }
      else
      {
         // Will it fit on current line?
         if (spriteX == x)
         {
            if (spriteX + stringWidth(s) < x + width)
               loadWord(fontSprites, s, spriteX, spriteY);
         }
         else
         {
            s = "\"" + s;
            if (spriteX + stringWidth(s) < x + width)
               loadWord(fontSprites, s, spriteX, spriteY);
         }

         spriteX += stringWidth(s);
      }
   }
}
/*-----------------------------------------------*/
void Font::tokenize(std::vector<std::string>* tokens, std::string s)
{
   using std::string;

   char* str = &s[0];
   char* end = &s[s.length()];
   do
   {
      char* begin = str;

      while (*str != ' ' && str != end && *str != '\n')
         str++;

      tokens->push_back(string(begin, str));

      if (*str == '\n')
      {
         tokens->push_back("\n");
         if (*(str + 1) == ' ')
            str++;
      }
   } while (end != str++);
}
/*-----------------------------------------------*/
void Font::loadWord(std::vector<Sprite>* fontSprites, std::string s, int x, int y)
{
   for (int i = 0; i < s.length(); i++)
   {
      char c = s[i];
      Sprite sprite = fontMap[c];
      sprite.x = x;
      sprite.y = y;

      x += sprite.width;

      fontSprites->push_back(sprite);
   }
}