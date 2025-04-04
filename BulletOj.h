#ifndef BULLET_OJ_H_
#define BULLET_OJ_H_
#include "BaseOj.h"
#include "CommonFunc.h"

class BulletOj : public BaseOj
{
public:
    BulletOj();
    ~BulletOj();

    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP=22,
        DIR_UP_LEFT=23,
        DIR_UP_RIGHT=24,
        DIR_DOWN_LEFT=25,
        DIR_DOWN_RIGHT=26,
        DIR_DOWN=27,
    };
    enum BulletType
    {
        SPHERE_BULLET=50,
        LASER_BULLET=51,
    };
    void set_x_val(const int& xVal) { x_vanl_ = xVal; }
    void set_y_val(const int& yVal) { y_vanl_ = yVal; }
    int get_x_val() const { return x_vanl_; }
    int get_y_val() const { return y_vanl_; }

    void set_is_move(const bool& isMove) { is_move_ = isMove; }
    bool get_is_move() const { return is_move_; }

    void set_bullet_dir(const unsigned int& bulletDir) { bullet_dir_ = bulletDir; }
    int get_bullet_dir() const { return bullet_dir_; }

    void set_bullet_type(const unsigned int& bulletType) { bullet_type_ = bulletType; }
    unsigned int get_bullet_type() const { return bullet_type_; }

    void HandleMove(const int& x_border, const int& y_border);
    bool LoadingBullet(SDL_Renderer* des);
private:
    int x_vanl_;
    int y_vanl_;
    bool is_move_;
    unsigned int bullet_dir_;
    unsigned int bullet_type_;

};

#endif
