#include "BaseOj.h"
#include "CommonFunc.h"

BaseOj::BaseOj() {
    p_object_ = nullptr;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
BaseOj::~BaseOj() {
   Free();
}
bool BaseOj::Loading(std::string path, SDL_Renderer* screen) {
    if (p_object_ != nullptr) {
        SDL_DestroyTexture(p_object_);
        p_object_ = nullptr;
    }
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if (load_surface == nullptr) {
        std::cout << "❌ IMG_Load FAILED for: " << path << " | Error: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

    new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
    if (new_texture == nullptr) {
        std::cout << "⚠️ SDL_CreateTextureFromSurface FAILED for: " << path << std::endl;
        SDL_FreeSurface(load_surface);
        return false;
    }
    rect_.w = load_surface->w;
    rect_.h = load_surface->h;
    SDL_FreeSurface(load_surface);
    p_object_ = new_texture;
    return true;
}
void BaseOj::Render(SDL_Renderer* des,const SDL_Rect* clip )
{
    SDL_Rect renderquad ={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_object_,clip,&renderquad);
}
void BaseOj::Free()
{
    if(p_object_!=nullptr){
        SDL_DestroyTexture(p_object_);
        p_object_=nullptr;
        rect_.w=0;
        rect_.h=0;
    }
}
