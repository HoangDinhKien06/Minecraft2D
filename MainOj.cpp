#include "MainOj.h"
#include "ThreatsObject.h"
#include "Sound.h"
MainOj::MainOj()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_vanl_ = 0;
    y_vanl_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.jump_=0;
    input_type_.down_=0;
    input_type_.up_=0;
    on_ground_=false;
    map_x_=0;
    map_y_=0;
    come_back_time_=0;
    meat_count=0;
    win=false;
}

MainOj::~MainOj()
{

}

bool MainOj::Loading(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseOj::Loading(path, screen);
    if (ret == true)
    {
        width_frame_ = rect_.w / 9;
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect MainOj::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void MainOj::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < 9; ++i)
        {
            frame_clip[i].x = i * width_frame_;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame_;
            frame_clip[i].h = height_frame_;
        }
    }
}

void MainOj::Show(SDL_Renderer* des)
{

    if (status_ == WALK_LEFT)
    {
        if(on_ground_==true)
            {
                Loading("D:\\gamebansung\\map\\dichyentrai1.png",des);
            }
            else{
                Loading("D:\\gamebansung\\map\\nhaytrai.png",des);
            }
    }
    else
    {
        if(on_ground_==true)
            {
                Loading("D:\\gamebansung\\map\\dichuyen.png",des);
            }
            else{
                Loading("D:\\gamebansung\\map\\nhayphai.png",des);
            }
    }

    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
        if (frame_ >= 9) frame_ = 0;
    }
    else
    {
        frame_ = 0;
    }
    if(come_back_time_==0){
    rect_.x = x_pos_-map_x_;
    rect_.y = y_pos_-map_y_;

    SDL_Rect* current_clip = &frame_clip[frame_];
    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}
void MainOj::EatMeat()
{
    meat_count++;
sound.playEffect("an");
}
 void MainOj::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletOj* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = nullptr;
        }
    }
}
void MainOj::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_LEFT:
                status_ = WALK_LEFT;
                input_type_.right_ = 0;
                input_type_.left_ = 1;
            if (on_ground_)
                Loading("D:\\gamebansung\\map\\dichyentrai1.png", screen);
            else
                Loading("D:\\gamebansung\\map\\nhaytrai.png", screen);
                break;
        case SDLK_RIGHT:
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
            if (on_ground_==true)
                Loading("D:\\gamebansung\\map\\dichuyen.png", screen);
            else
                Loading("D:\\gamebansung\\map\\nhayphai.png", screen);
            break;
        case SDLK_UP:
            status_ = WALK_UP;
            break;
        default:
            break;
        }
    }

    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            input_type_.right_ = 0;
            break;
        case SDLK_LEFT:
            input_type_.left_ = 0;
            break;
        default:
            break;
        }
    }

    else if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_RIGHT)
        {
            input_type_.jump_ = 1;
        }

        if (events.button.button == SDL_BUTTON_LEFT)
        {
            if (x_pos_ == 0 && y_pos_ == 0)
            return;
            else{
            BulletOj* p_bullet = new BulletOj();
            p_bullet->set_bullet_type(BulletOj::SPHERE_BULLET);
            p_bullet->LoadingBullet(screen);

            if (status_ == WALK_LEFT)
                p_bullet->set_bullet_dir(BulletOj::DIR_LEFT);
            else if(status_ == WALK_UP)
                p_bullet->set_bullet_dir(BulletOj::DIR_UP);
            else if (status_ == WALK_RIGHT)
                p_bullet->set_bullet_dir(BulletOj::DIR_RIGHT);
            p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_ * 0.25);
            p_bullet->set_x_val(20);
            p_bullet->set_y_val(20);
            p_bullet->set_is_move(true);
            p_bullet_list_.push_back(p_bullet);
            sound.playEffect("ban");
            }
        }
    }
}

void MainOj::HandleBullet(SDL_Renderer* des, const Map& map_data)
{
    for (int i = 0; i < p_bullet_list_.size(); )
    {
        BulletOj* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != nullptr)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
                ++i;
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                delete p_bullet;
                p_bullet = nullptr;
            }
        }
        else
        {
            ++i;
        }
    }
}


void MainOj::DoPlayer(Map& map_data)
{
    if(come_back_time_==0)
    {
    x_vanl_=0;
    y_vanl_+=0.8;
    if(y_vanl_>=MAX_FALL_SPEED_)
    {
        y_vanl_=MAX_FALL_SPEED_;
    }
    if(input_type_.left_==1)
    {
        x_vanl_-=PLAYER_SPEED;
    }
    else if (input_type_.right_==1)
    {
        x_vanl_+=PLAYER_SPEED;
    }
    if(input_type_.jump_==1)
    {
        if(on_ground_==true)
    {
        y_vanl_=-PLAYER_JUMP_VAL;
         on_ground_=false;
        sound.playEffect("nhay");
    }
        input_type_.jump_=0;

    }
    CheckToMap( map_data);
    CenterEntityOnMAp(map_data);
    }
    if(come_back_time_>0)
    {
        come_back_time_--;
        if(come_back_time_==0)
        {
            if(x_pos_>256){
            x_pos_-=256;
            map_x_-=256;
            }
            y_pos_=0;
            x_vanl_=0;
            y_vanl_=0;
        }
    }
}
void MainOj:: CenterEntityOnMAp(Map& map_data)
{
    map_data.start_x_=x_pos_-(SCREEN_WIDTH/2);
    if(map_data.start_x_<0)
    {
        map_data.start_x_=0;
    }
    else if(map_data.start_x_+SCREEN_WIDTH>=map_data.max_x_)
    {
        map_data.start_x_=map_data.max_x_-SCREEN_WIDTH;
    }
    map_data.start_y_=y_pos_-(SCREEN_HEIGHT)/2;
    if(map_data.start_y_<0)
    {
        map_data.start_y_=0;
    }
    else if(map_data.start_y_+SCREEN_HEIGHT>= map_data.max_y_)
    {
        map_data.start_y_=map_data.max_y_-SCREEN_HEIGHT;
    }
};
void MainOj::CheckToMap(Map& map_data)
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
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
        if (val1 == STATE_MEAT ||val2==STATE_MEAT )
        {
         map_data.tile[y1][x2]= 0;
        map_data.tile[y2][x2]= 0;
        EatMeat();
        }
        else if(val1==5||val2==5)
        {
            win=true;
        }
        else{
            if(val1 != BLANK_TILE||val2 != BLANK_TILE)
            {
                x_pos_=x2*TILE_SIZE;
                x_pos_-=width_frame_+1;
                x_vanl_=0;
            }
        }
    }
        else if(x_vanl_<0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
        if (val1 == STATE_MEAT ||val2==STATE_MEAT )
        {
         map_data.tile[y1][x2]= 0;
        map_data.tile[y2][x2]= 0;
        EatMeat();
        }
        else if(val1==5||val2==5)
        {
            win=true;
        }
        else
        {
            if(val1 !=BLANK_TILE||val2 !=BLANK_TILE)
            {
                x_pos_=(x1+1)*TILE_SIZE;
                x_vanl_=0;
            }
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
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if (val1 == STATE_MEAT ||val2==STATE_MEAT )
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                EatMeat();
            }
            else if(val1==5||val2==5)
        {
            win=true;
        }
            else{
               if(val1 != BLANK_TILE||val2 != BLANK_TILE)
            {
                y_pos_=y2*TILE_SIZE;
                y_pos_-=(height_frame_+1);
                y_vanl_=0;
                on_ground_=true;

            }
        }
    }
        else if(y_vanl_<0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if (val1 == STATE_MEAT ||val2==STATE_MEAT )
            {
                 map_data.tile[y2][x1]= 0;
                map_data.tile[y2][x2] = 0;
                EatMeat();
            }
            else if(val1==5||val2==5)
        {
            win=true;
        }
            else
            {
               if(val1!=BLANK_TILE || val2!= BLANK_TILE)
            {
               y_pos_=(y1+1)* TILE_SIZE;
               y_vanl_=0;

            }
        }
    }
}
    x_pos_+=x_vanl_;
    y_pos_ += y_vanl_;
    if(x_pos_<0)
    {
        x_pos_=0;
    }
    else if(x_pos_+width_frame_>map_data.max_x_)
    {
        x_pos_=map_data.max_x_-width_frame_-1;
    }

    if(y_pos_>map_data.max_y_)
    {
        come_back_time_=60;
    }
}

