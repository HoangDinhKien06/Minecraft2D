#ifndef DARKSCREENEFFECT_H
#define DARKSCREENEFFECT_H
#include "CommonFunc.h"

class DarkScreenEffect {
public:
    DarkScreenEffect(SDL_Renderer* renderer);
    void RenderDarkScreen(bool isDark);
    void SetDark(bool darkStatus);
private:
    SDL_Renderer* g_screen;
    bool isDark;
};

#endif

