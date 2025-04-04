#include "BulletOj.h"
#include "CommonFunc.h"
#include "BaseOj.h"


BulletOj::BulletOj()
{
    x_vanl_=0; y_vanl_=0; is_move_=false;bullet_dir_ = DIR_RIGHT;
    bullet_type_=SPHERE_BULLET;
}

BulletOj::~BulletOj()
{

}
bool BulletOj::LoadingBullet(SDL_Renderer* des)
{
    bool ret =false;
    if(bullet_type_==LASER_BULLET)
    {
        ret =Loading("D:\\gamebansung\\map\\danlazer.png", des);
    }
    else
    {
        ret =Loading("D:\\gamebansung\\map\\dan phai1.png", des);
    }
    return ret;
}
void BulletOj::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_vanl_;
        if (rect_.x > x_border) is_move_ = false;
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_vanl_;
        if (rect_.x < 0) is_move_ = false;
    }
    else if (bullet_dir_ == DIR_UP)
    {
        rect_.y -= y_vanl_;
        if (rect_.y < 0) is_move_ = false;
    }
}




