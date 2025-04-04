#include "BaseOj.h"
#include "CommonFunc.h"
#include "Menu.h"
#include "Button.h"
void showMenu(SDL_Window* window, SDL_Renderer* renderer, BaseOj& menuBackground) {
    bool quit = false;
    SDL_Event e;
    Button startButton(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, 200, 60, "D:\\gamebansung\\map\\nut.png", renderer);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            startButton.handleEvent(&e);
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                quit = true;
                std::cout << "Game started!" << std::endl;
            }
            if (startButton.isPressed()) {
                quit = true;
                std::cout << "Game started!" << std::endl;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        menuBackground.Render(renderer);
        startButton.render(renderer);
        SDL_RenderPresent(renderer);
    }
}
