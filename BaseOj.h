#ifndef BASE_OJ_H_
#define BASE_OJ_H_

#include "CommonFunc.h"

class BaseOj {
public:

    BaseOj();
    ~BaseOj();

    void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
    SDL_Rect GetRect() const { return rect_; }
    SDL_Texture* GetOj() const { return p_object_; }

    virtual bool Loading(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
    void Free();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif // BASE_OJ_H_
