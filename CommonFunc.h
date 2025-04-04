#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "ImpTimes.h"
#include <list>
#include <windows.h>
#include <map>
#include <thread>
#include <chrono>
#include <cstdlib>

static SDL_Window* g_Window=nullptr;
static SDL_Renderer* g_screen=nullptr;
static SDL_Event g_event;

const int FRAME_PER_SECOND =30;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP =32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR=0Xff;
#define BLANK_TILE 0

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define STATE_MEAT 4
struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};





struct Map
{
    int start_x_;
    int start_y_;
    int max_x_;
    int max_y_;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name_;
};
namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}


#endif

