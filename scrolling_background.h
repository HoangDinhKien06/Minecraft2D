#pragma once
#include <vector>
#include <string>
#include "BaseOj.h"
const int BACKGROUND_LAYER = 9;
#define LAYER_1_SPEED 0.5
#define LAYER_2_SPEED 1.0
#define LAYER_3_SPEED 1.5
#define LAYER_4_SPEED 2.0
#define LAYER_5_SPEED 2.5
#define LAYER_6_SPEED 3.0
#define LAYER_7_SPEED 3.5
#define LAYER_8_SPEED 4.0
#define LAYER_9_SPEED 4.5
extern const std::string LAYER[BACKGROUND_LAYER];
void RenderScrollingBackground(std::vector<double>& offsetSpeed,
                               BaseOj(&gBackgroundTexture)[BACKGROUND_LAYER],
                               SDL_Renderer* gRenderer);

