#ifndef MAIN_OJ_H_
#define MAIN_OJ_H_
#include "CommonFunc.h"
#include "BaseOj.h"
#include "BulletOj.h"
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED_ 10
#define PLAYER_SPEED 10
#define PLAYER_JUMP_VAL 15;
class MainOj :public BaseOj
{
    public:
        MainOj();
        ~MainOj();
        enum Walk_Type
        {
            WALK_RIGHT=0,
            WALK_LEFT=1,
            WALK_UP=2,
            WALK_DOWN=3,
            WALK_UP_RIGHT=4,
            WALK_UP_LEFT=5,
            WALK_DOWN_RIGHT=6,
            WALK_DOWN_LEFT=7,
        };
        bool Loading(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
        void set_clips();
        void DoPlayer(Map& map_data);
        void CheckToMap(Map& map_data);
        void SetMapXY(const int map_x, const int map_y){map_x_=map_x;map_y_=map_y;}
        void CenterEntityOnMAp(Map& map_data);
        void UpdateImagePlayer(SDL_Renderer* des);
        SDL_Rect GetRectFrame();
        void set_bullet_list(std::vector<BulletOj*> bullet_list)
        {
            p_bullet_list_=bullet_list;
        }
        std::vector<BulletOj*>get_bullet_list() const {return p_bullet_list_;}
        void HandleBullet(SDL_Renderer* des, const Map& map_data);
        void RemoveBullet(const int& idx);
        void EatMeat();
        void set_comeback_time(const int& cb_time){come_back_time_=cb_time;}
        int GetMeatCount() const {return meat_count;}
        bool getWin() const { return win; }
        int get_comeback_time() const { return come_back_time_; }
    int meat_count;
    bool win;
    std::vector<BulletOj*> p_bullet_list_;
    float x_vanl_;
    float y_vanl_;

    float x_pos_;
    float y_pos_;
    int width_frame_;
    int height_frame_;
    SDL_Rect frame_clip[9];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time_;


};
#endif

