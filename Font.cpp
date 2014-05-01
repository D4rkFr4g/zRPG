#include "Font.h"

Texture* Font::texture;
std::unordered_map<char, Sprite> Font::fontMap;
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
   int cellWidth = texture->cellWidth;
   int cellHeight = texture->cellHeight;
   GLfloat uSize = texture->uSize;
   GLfloat vSize = texture->vSize;
   GLuint* tex = &texture->texture;

   //                                 pixelWidth      pixelHeight     gridX     gridY      gridW      gridH
   // Lowercase
   fontMap['a'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 0 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // a
   fontMap['b'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 7 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // b
   fontMap['c'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 14 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // c
   fontMap['d'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 21 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // d
   fontMap['e'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 28 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // e
   fontMap['f'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 35 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // f
   fontMap['g'] = Sprite(tex, x, y, 6 * cellWidth, 12 * cellHeight, 42 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // g
   fontMap['h'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 49 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // h
   fontMap['i'] = Sprite(tex, x, y, 3 * cellWidth, 13 * cellHeight, 56 * uSize, 3 * vSize, 3 * uSize, 13 * vSize); // i
   fontMap['j'] = Sprite(tex, x, y, 5 * cellWidth, 15 * cellHeight, 60 * uSize, 1 * vSize, 5 * uSize, 15 * vSize); // j
   fontMap['k'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 66 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // k
   fontMap['l'] = Sprite(tex, x, y, 3 * cellWidth, 13 * cellHeight, 73 * uSize, 3 * vSize, 3 * uSize, 13 * vSize); // l
   fontMap['m'] = Sprite(tex, x, y, 7 * cellWidth, 10 * cellHeight, 77 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // m
   fontMap['n'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 85 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // n
   fontMap['o'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 92 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // o
   fontMap['p'] = Sprite(tex, x, y, 6 * cellWidth, 12 * cellHeight, 99 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // p
   fontMap['q'] = Sprite(tex, x, y, 6 * cellWidth, 12 * cellHeight, 106 * uSize, 1 * vSize, 6 * uSize, 12 * vSize); // q
   fontMap['r'] = Sprite(tex, x, y, 5 * cellWidth, 10 * cellHeight, 113 * uSize, 3 * vSize, 5 * uSize, 10 * vSize); // r
   fontMap['s'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 119 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // s
   fontMap['t'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 126 * uSize, 3 * vSize, 6 * uSize, 13 * vSize); // t
   fontMap['u'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 133 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // u
   fontMap['v'] = Sprite(tex, x, y, 7 * cellWidth, 10 * cellHeight, 140 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // v
   fontMap['w'] = Sprite(tex, x, y, 7 * cellWidth, 10 * cellHeight, 148 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // w
   fontMap['x'] = Sprite(tex, x, y, 7 * cellWidth, 10 * cellHeight, 156 * uSize, 3 * vSize, 7 * uSize, 10 * vSize); // x
   fontMap['y'] = Sprite(tex, x, y, 7 * cellWidth, 12 * cellHeight, 164 * uSize, 1 * vSize, 7 * uSize, 12 * vSize); // y
   fontMap['z'] = Sprite(tex, x, y, 6 * cellWidth, 10 * cellHeight, 172 * uSize, 3 * vSize, 6 * uSize, 10 * vSize); // z
   // Uppercase
   fontMap['A'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 0 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // A
   fontMap['B'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 7 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // B
   fontMap['C'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 14 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // C
   fontMap['D'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 21 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // D
   fontMap['E'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 28 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // E
   fontMap['F'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 35 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // F
   fontMap['G'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 42 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // G
   fontMap['H'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 49 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // H
   fontMap['I'] = Sprite(tex, x, y, 3 * cellWidth, 13 * cellHeight, 56 * uSize, 19 * vSize, 3 * uSize, 13 * vSize); // I
   fontMap['J'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 60 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // J
   fontMap['K'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 67 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // K
   fontMap['L'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 74 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // L
   fontMap['M'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 81 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // M
   fontMap['N'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 89 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // N
   fontMap['O'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 96 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // O
   fontMap['P'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 103 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // P
   fontMap['Q'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 110 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // Q
   fontMap['R'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 117 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // R
   fontMap['S'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 124 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // S
   fontMap['T'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 131 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // T
   fontMap['U'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 139 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // U
   fontMap['V'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 146 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // V
   fontMap['W'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 154 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // W
   fontMap['X'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 162 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // X
   fontMap['Y'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 170 * uSize, 19 * vSize, 7 * uSize, 13 * vSize); // Y
   fontMap['Z'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 178 * uSize, 19 * vSize, 6 * uSize, 13 * vSize); // Z
   // Symbols
   fontMap['!'] = Sprite(tex, x, y, 3 * cellWidth, 13 * cellHeight, 0 * uSize, 35 * vSize, 3 * uSize, 13 * vSize); // !
   fontMap['"'] = Sprite(tex, x, y, 5 * cellWidth, 4 * cellHeight, 4 * uSize, 34 * vSize, 5 * uSize, 4 * vSize); // "
   fontMap['~'] = Sprite(tex, x, y, 6 * cellWidth, 12 * cellHeight, 10 * uSize, 34 * vSize, 6 * uSize, 12 * vSize); // ~~~
   fontMap['&'] = Sprite(tex, x, y, 6 * cellWidth, 14 * cellHeight, 17 * uSize, 34 * vSize, 6 * uSize, 14 * vSize); // &
   fontMap['|'] = Sprite(tex, x, y, 6 * cellWidth, 14 * cellHeight, 24 * uSize, 34 * vSize, 6 * uSize, 14 * vSize); // |
   fontMap['\''] = Sprite(tex, x, y, 4 * cellWidth, 6 * cellHeight, 31 * uSize, 43 * vSize, 4 * uSize, 6 * vSize); // '
   fontMap['('] = Sprite(tex, x, y, 6 * cellWidth, 15 * cellHeight, 36 * uSize, 34 * vSize, 6 * uSize, 15 * vSize); // (
   fontMap[')'] = Sprite(tex, x, y, 6 * cellWidth, 15 * cellHeight, 43 * uSize, 34 * vSize, 6 * uSize, 15 * vSize); // )
   fontMap[','] = Sprite(tex, x, y, 4 * cellWidth, 6 * cellHeight, 50 * uSize, 33 * vSize, 4 * uSize, 6 * vSize); // ,
   fontMap['-'] = Sprite(tex, x, y, 6 * cellWidth, 3 * cellHeight, 54 * uSize, 42 * vSize, 6 * uSize, 3 * vSize); // -
   fontMap['.'] = Sprite(tex, x, y, 4 * cellWidth, 4 * cellHeight, 56 * uSize, 35 * vSize, 4 * uSize, 4 * vSize); // .
   fontMap['_'] = Sprite(tex, x, y, 6 * cellWidth, 4 * cellHeight, 61 * uSize, 35 * vSize, 6 * uSize, 4 * vSize); // ...
   fontMap['0'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 68 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 0
   fontMap['1'] = Sprite(tex, x, y, 4 * cellWidth, 13 * cellHeight, 75 * uSize, 35 * vSize, 4 * uSize, 13 * vSize); // 1
   fontMap['2'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 80 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 2
   fontMap['3'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 87 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 3
   fontMap['4'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 94 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 4
   fontMap['5'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 101 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 5
   fontMap['6'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 108 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 6
   fontMap['7'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 115 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 7
   fontMap['8'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 122 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 8
   fontMap['9'] = Sprite(tex, x, y, 6 * cellWidth, 13 * cellHeight, 129 * uSize, 35 * vSize, 6 * uSize, 13 * vSize); // 9
   fontMap[':'] = Sprite(tex, x, y, 4 * cellWidth, 10 * cellHeight, 136 * uSize, 35 * vSize, 4 * uSize, 10 * vSize); // :
   fontMap[';'] = Sprite(tex, x, y, 4 * cellWidth, 12 * cellHeight, 141 * uSize, 33 * vSize, 4 * uSize, 12 * vSize); // ;
   fontMap['<'] = Sprite(tex, x, y, 6 * cellWidth, 9 * cellHeight, 146 * uSize, 37 * vSize, 6 * uSize, 9 * vSize); // <
   fontMap['='] = Sprite(tex, x, y, 6 * cellWidth, 7 * cellHeight, 153 * uSize, 37 * vSize, 6 * uSize, 7 * vSize); // =
   fontMap['>'] = Sprite(tex, x, y, 6 * cellWidth, 9 * cellHeight, 160 * uSize, 36 * vSize, 6 * uSize, 9 * vSize); // >
   fontMap['?'] = Sprite(tex, x, y, 7 * cellWidth, 13 * cellHeight, 167 * uSize, 35 * vSize, 7 * uSize, 13 * vSize); // ?
   fontMap['@'] = Sprite(tex, x, y, 16 * cellWidth, 14 * cellHeight, 175 * uSize, 34 * vSize, 16 * uSize, 14 * vSize); // @
   fontMap[' '] = Sprite(tex, x, y, 5 * cellWidth, 1 * cellHeight, 0 * uSize, 0 * vSize, 5 * uSize, 1 * vSize); // space
}
/*-----------------------------------------------*/