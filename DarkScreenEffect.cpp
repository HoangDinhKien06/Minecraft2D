#include "DarkScreenEffect.h"
DarkScreenEffect::DarkScreenEffect(SDL_Renderer* renderer) : g_screen(renderer), isDark(false) {}
void DarkScreenEffect::RenderDarkScreen(bool darkStatus)
{
    if (darkStatus)
    {
        SDL_SetRenderDrawColor(g_screen, 147, 239, 146, 0);
        SDL_Rect darkRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(g_screen, &darkRect); // Vẽ lớp phủ đen
    }
}
void DarkScreenEffect::SetDark(bool darkStatus)
{
    isDark = darkStatus;
}

