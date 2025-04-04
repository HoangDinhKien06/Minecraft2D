#include "ThreatsObject.h"
#include "Sound.h"
ThreatsObject::ThreatsObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_vanl_ = 0.0;
    y_vanl_ = 0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground_ = 0;
    come_back_time_ = 0;
    frame_ = 0;
    map_x_=0;
    map_y_=0;
    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_THREAT;
    r=rand() % 400 +200;
}
bool ThreatsObject::Loading(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseOj::Loading(path, screen);
    if(ret)
    {
        width_frame_ = rect_.w / THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}
void ThreatsObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
         for (int i = 0; i < THREAT_FRAME_NUM; ++i)
        {
            frame_clip_[i].x = i * width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}
void ThreatsObject::Show(SDL_Renderer* des)
{
    if (come_back_time_ == 0)
    {
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;
    frame_++;
    if (frame_ >= THREAT_FRAME_NUM) frame_ = 0;
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {
        rect_.x,
        rect_.y,
        width_frame_,
        height_frame_
    };
    SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
    }
}
void ThreatsObject::DoPlayer(Map& gMap)
{
    if (come_back_time_ == 0)
    {
        x_vanl_ = 0;
        y_vanl_ += THREAT_GRAVITY_SPEED;
        if (y_vanl_ >= THREAT_MAX_FALL_SPEED)
            y_vanl_ = THREAT_MAX_FALL_SPEED;
        if (input_type_.left_ == 1)
        {
        x_vanl_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
        x_vanl_ += THREAT_SPEED;
        }

        CheckToMap(gMap);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_--;
        if (come_back_time_ == 0)
        {
            InitThreats();
        }
    }
}
void ThreatsObject::InitThreats()
{
            x_vanl_ = 0;
            y_vanl_ = 0;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256;
                animation_a_ -=256;
                animation_b_ -=256;
            }
            else{
                x_pos_=0;
            }
            y_pos_=0;
            come_back_time_=0;
            input_type_.left_=1;
}

 void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletOj* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = nullptr;
            r=rand() % 400 +200;
        }
    }
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void ThreatsObject::CheckToMap(Map& gMap)
{
int x1=0,x2=0,y1=0,y2=0;
    int height_min=height_frame_<TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1=(x_pos_+x_vanl_)/TILE_SIZE;
    x2=(x_pos_+x_vanl_+width_frame_-1)/TILE_SIZE;
    y1=(y_pos_)/TILE_SIZE;
    y2=(y_pos_+ height_min-1)/TILE_SIZE;

    if(x1>=0&& x2<MAX_MAP_X&&y1>0&&y2< MAX_MAP_Y)
    {
        if(x_vanl_>0)
        {
            int val1 = gMap.tile[y1][x2];
            int val2 = gMap.tile[y2][x2];
            if((val1 != BLANK_TILE&&val1 != STATE_MEAT)||(val2 != BLANK_TILE&&val2 != STATE_MEAT))
            {
                x_pos_=x2*TILE_SIZE;
                x_pos_-=width_frame_+1;
                x_vanl_=0;
            }
        }
        else if(x_vanl_<0)
        {
            int val1 = gMap.tile[y1][x2];
            int val2 = gMap.tile[y2][x2];
            if((val1 !=BLANK_TILE&&val1 != STATE_MEAT)||(val2 !=BLANK_TILE&&val2 != STATE_MEAT))
            {
                x_pos_=(x1+1)*TILE_SIZE;
                x_vanl_=0;
            }
        }
    }

    int width_min=width_frame_<TILE_SIZE ? width_frame_: TILE_SIZE;
    x1=(x_pos_)/TILE_SIZE;
    x2=(x_pos_+width_min)/TILE_SIZE;
    y1=(y_pos_+y_vanl_)/TILE_SIZE;
    y2=(y_pos_+y_vanl_+height_frame_-1)/TILE_SIZE;
    if(x1>=0&& x2<MAX_MAP_X&&y1>=0&&y2<MAX_MAP_Y)
    {
        if(y_vanl_>0)
        {
            int val1 = gMap.tile[y2][x1];
            int val2 = gMap.tile[y2][x2];
            if((val1 != BLANK_TILE&&val1 != STATE_MEAT)||(val2 != BLANK_TILE&&val2 != STATE_MEAT))
            {
                y_pos_=y2*TILE_SIZE;
                y_pos_-=(height_frame_+1);
                y_vanl_=0;
                on_ground_=true;

            }
        }
        else if(y_vanl_<0)
        {
            int val1 = gMap.tile[y2][x1];
            int val2 = gMap.tile[y2][x2];
            if((val1!=BLANK_TILE&&val1 != STATE_MEAT) ||( val2!= BLANK_TILE&&val2 != STATE_MEAT))
            {
               y_pos_=(y1+1)* TILE_SIZE;
               y_vanl_=0;

            }
        }
    }
    x_pos_+=x_vanl_;
    y_pos_ += y_vanl_;
    if(x_pos_<0)
    {
        x_pos_=0;
    }
    else if(x_pos_+width_frame_>gMap.max_x_)
    {
        x_pos_=gMap.max_x_-width_frame_-1;
    }

    if(y_pos_>gMap.max_y_)
    {
        come_back_time_=60;
    }
}

ThreatsObject::~ThreatsObject() {

}
void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move_ == STATIC_THREAT)
    {
        ;
    }
    else
    {
        if (on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                Loading("D:\\gamebansung\\map\\Skeleton_01_White_Attack1trais.png", screen);
            }
            else if (x_pos_ < animation_a_)
            {
            input_type_.left_ = 0;
            input_type_.right_ = 1;
            Loading("D:\\gamebansung\\map\\Skeleton_01_White_Attack1.png", screen);
            }
            else
            {
            if (input_type_.left_ == 1)
            {
            Loading("D:\\gamebansung\\map\\Skeleton_01_White_Attack1trais.png", screen);
            }
            }

        }
    }
}
void ThreatsObject::InitBullet(BulletOj* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != nullptr)
    {
        p_bullet->set_bullet_type(BulletOj::LASER_BULLET);
        bool ret=p_bullet->LoadingBullet(screen);
        if(ret)
        {
           p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletOj::DIR_LEFT);
        p_bullet->SetRect(rect_.x + 5, rect_.y +  5);
        p_bullet->set_x_val(15);
        bullet_list_.push_back(p_bullet);
        }
    }
}
void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        BulletOj* p_bullet = bullet_list_.at(i);
        if (p_bullet !=nullptr)
        {
            if (p_bullet->get_is_move())
            {
                int bullet_distance=rect_.x+width_frame_-p_bullet->GetRect().x;
                if(bullet_distance<(r)&&bullet_distance>0)
                {
                  p_bullet->HandleMove(x_limit, y_limit);
                p_bullet->Render(screen);
                }
               else
               {
                   p_bullet->set_is_move(false);
               }
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x+40, rect_.y + 30);
                if (sound.is_enemy_sound_on)
        sound.playEffect("quaiban");
            }
        }
    }
}





