#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_timer.h>
#include <GL/glew.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
#include <unordered_map>
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include "DrawUtils.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "PlayerSprite.h"
#include "Camera.h"
#include "TileLevel.h"
#include "tileLoader.h"
#include "player.h"
#include "Audio.h"
#include "EventQueue.h"
#include "Texture.h"
#include "textureLoader.h"

// Forward Declarations
static void keyboard();
static void clearBackground();
static void makeChicken();
static float getSpeed();

// Constants
const int camSpeed = 10;
const int g_numOfLevels = 1;
const int spriteSize = 64;
const int spriteReserve = 50000;
const int initialChickens = 20;
const int chickenSpeed = 50;
const unsigned char* kbState = NULL;
const int g_numOfCheckBuckets = 9; 

// Global Variables
SDL_Window* g_window;
float color[] = {0,0,0};
float currentDirection = 1;
int g_windowWidth = 640;
int g_windowOriginalWidth;
int g_windowHeight = 480;
int g_windowOriginalHeight;
int g_windowMaxWidth = 0;
int g_windowMaxHeight = 0;
Camera g_cam;
TileLevel* g_currentLevel;
std::unordered_map<std::string, TileLevel> g_level;
std::vector<std::vector<AnimatedSprite>> g_spriteBuckets;
int* g_checkBuckets;
std::unordered_map<std::string, Texture> g_textures;
unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
bool shouldExit = false;
PlayerSprite g_player;
FMOD_RESULT result;
FMOD::System* fmodSystem;
Audio g_audio;
static EventQueue eventQueue;