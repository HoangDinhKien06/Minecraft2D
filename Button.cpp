#include "Button.h"
Button::Button() : buttonRect({ 0, 0, 0, 0 }), buttonTexture(nullptr), pressed(false) {}
Button::Button(int x, int y, int w, int h, std::string texturePath, SDL_Renderer* renderer)
    : buttonRect({x, y, w, h}), buttonTexture(nullptr), pressed(false) {
    SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
    if (loadedSurface != nullptr) {
        buttonTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
}
Button::~Button() {
    if (buttonTexture != nullptr) {
        SDL_DestroyTexture(buttonTexture);
    }
}
void Button::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        pressed = (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
                   y >= buttonRect.y && y <= buttonRect.y + buttonRect.h);
    }
}
void Button::render(SDL_Renderer* renderer) {
    if (buttonTexture != nullptr) {
        SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
    }
}
void Button::setText(std::string newText) {
    text = newText;
}

