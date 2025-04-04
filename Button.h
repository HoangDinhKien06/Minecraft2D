#ifndef BUTTON_H
#define BUTTON_H

#include "CommonFunc.h"
class Button {
public:
    Button();
    Button(int x, int y, int w, int h, std::string texturePath, SDL_Renderer* renderer);
    ~Button();
    void handleEvent(SDL_Event* e);
    void render(SDL_Renderer* renderer);

    bool isPressed() const { return pressed; }
    void setText(std::string newText);

private:
    SDL_Rect buttonRect;
    SDL_Texture* buttonTexture;
    bool pressed;
    std::string text;
};

#endif

