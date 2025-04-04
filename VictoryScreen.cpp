#include "VictoryScreen.h"
void RenderVictory(SDL_Renderer* renderer)
{
    SDL_Texture* victory_texture = nullptr;
    SDL_Surface* loaded_surface = IMG_Load("D:\\gamebansung\\map\\win.png");

    if (loaded_surface != nullptr)
    {
        victory_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        SDL_FreeSurface(loaded_surface);
    }

    if (victory_texture != nullptr)
    {
        SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, victory_texture, nullptr, &renderQuad);
        SDL_DestroyTexture(victory_texture);
    }
}

