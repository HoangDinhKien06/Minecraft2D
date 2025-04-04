#include "CommonFunc.h"
#include "BaseOj.h"
#include "game_map.h"
#include "MainOj.h"
#include "ImpTimes.h"
#include "scrolling_background.h"
#include "ThreatsObject.h"
#include "ExplosionOj.h"
#include "TextOj.h"
#include "Menu.h"
#include "PlayerPower.h"
#include "Gemotric.h"
#include "VictoryScreen.h"
#include "DarkScreenEffect.h"
#include "Sound.h"
TTF_Font* font_time= nullptr;
Uint32 start_ticks = 0;
Uint32 pause_start_ticks = 0;
Uint32 pause_duration = 0;
bool is_paused = false;
SDL_Texture* help_texture = nullptr;
BaseOj gBackgroundTexture[BACKGROUND_LAYER];
std::vector<double> offsetSpeed(BACKGROUND_LAYER, 0.0);
TextOj music_volume_text;
TextOj effect_volume_text;
Sound sound;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);

    if (ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_Window = SDL_CreateWindow("Minecraft 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_Window == nullptr) {
        success = false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);

        if (g_screen == nullptr) success = false;
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlag = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlag) & imgFlag)) success = false;
        }

        if (TTF_Init() == -1) success = false;

        font_time = TTF_OpenFont("D:\\gamebansung\\map\\FVF Fernando 08.ttf", 15);
        music_volume_text.SetColor(TextOj::WHITE_TEXT);
        effect_volume_text.SetColor(TextOj::WHITE_TEXT);

        if (font_time == nullptr) success = false;
        SDL_Surface* help_surface = IMG_Load("D:\\gamebansung\\map\\menuhd.png");
        if (help_surface) {
            help_texture = SDL_CreateTextureFromSurface(g_screen, help_surface);
            SDL_FreeSurface(help_surface);
        }
        else {
            std::cout << "❌ Không load được ảnh help.png: " << IMG_GetError() << std::endl;
        }
    }
    for (int i = 0; i < BACKGROUND_LAYER; ++i) {
        if (!gBackgroundTexture[i].Loading(LAYER[i], g_screen)) {
            std::cout << "❌ Failed to load layer: " << LAYER[i] << std::endl;
            return false;
        }
    }
    return success;
}
void close()
{
    SDL_DestroyRenderer(g_screen);
    g_screen=nullptr;
    SDL_DestroyWindow(g_Window);
    g_Window=nullptr;
    IMG_Quit();
    SDL_Quit();
}
std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[50];
        for (int i = 0; i < 50; i++)
            {
                int r = rand() % 50;
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != nullptr)
                {
            p_threat->Loading("D:\\gamebansung\\map\\Skeleton_01_White_Attack1trais.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*(200+r));
            p_threat->set_y_pos(200);
            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
                }
            }
    ThreatsObject* threats_objs = new ThreatsObject[50];
    for (int i = 0; i < 50; i++)
    {
        int r = rand() % 50;
        ThreatsObject* p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat->Loading("D:\\gamebansung\\map\\Skeleton_01_Yellow_Walktrai.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i*(220+r));
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            BulletOj* p_bullet = new BulletOj();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}
int main(int argc, char* argv[])
{
        bool ShowVictoryScreen(SDL_Renderer* renderer);
        ImpTimer fps_timer;
        int vol_music = sound.getMusicVolume();
        sound.setMusicVolume(vol_music + 10);
        int vol_effect = sound.getEffectVolume();
        sound.setEffectVolume(vol_effect - 10);
        sound.loadEffect("chet", "D:\\gamebansung\\sound\\boing.mp3");
        sound.loadEffect("no","D:\\gamebansung\\sound\\explosion.mp3" );
        sound.loadEffect("nhay", "D:\\gamebansung\\sound\\alert.mp3");
        sound.loadEffect("an", "D:\\gamebansung\\sound\\coin.mp3");
        sound.loadEffect("ban", "D:\\gamebansung\\sound\\shotgun.mp3");
        sound.loadEffect("quaiban","D:\\gamebansung\\sound\\arrowtrap.mp3" );
        int frame_exp_width = 96;
        int frame_exp_height = 96;
        if(InitData()==false)
        return -1;

    BaseOj menuBackground;
    if (!menuBackground.Loading("D:\\gamebansung\\background\\menu.png", g_screen)) {
        std::cout << "Failed to load menu background!" << std::endl;
        return -1;
    }
    showMenu(g_Window, g_screen, menuBackground);
    start_ticks = SDL_GetTicks();
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    sound.loadMusic("D:\\gamebansung\\sound\\cave.mp3");
    sound.playMusic();
    game_map.LoadTiles(g_screen);

    MainOj p_player;
    p_player.Loading(std::string("D:\\gamebansung\\map\\dichuyen.png"), g_screen);
    p_player.set_clips();
    PlayerPower player_power;
    player_power.Init(g_screen);
    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH * 0.5 - 300, 8);
    std::vector<ThreatsObject*> threats_list = MakeThreadList();
        ExplosionObject exp_threat;
        bool tRet = exp_threat.Loading("D:\\gamebansung\\map\\no.png", g_screen);
        if (!tRet) return -1;
        exp_threat.set_clip();
        int num_die=0;
        TextOj time_game;
        time_game.SetColor(TextOj::WHITE_TEXT);
        TextOj mark_game;
        mark_game.SetColor(TextOj::WHITE_TEXT);
        UINT mark_value=0;
        TextOj meat_game;
        meat_game.SetColor(TextOj::WHITE_TEXT);
        time_game.SetColor(TextOj::WHITE_TEXT);
        bool is_quit=false;
        DarkScreenEffect darkScreenEffect(g_screen);
        bool isDark = false;
        while(!is_quit)
        {
        if (is_paused) {
        while (is_paused) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
                return 0;
                }
                else if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_p) {
                is_paused = false;
                pause_duration += SDL_GetTicks() - pause_start_ticks;
            }
        }
        SDL_RenderClear(g_screen);
        if (help_texture) {
            SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            SDL_RenderCopy(g_screen, help_texture, NULL, &renderQuad);
        }
        TextOj pauseText;
        pauseText.SetColor(TextOj::WHITE_TEXT);
        pauseText.SetText("Press P to continue");
        pauseText.LoadFromRenderText(font_time, g_screen);
        pauseText.RenderText(g_screen, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 50);
        SDL_RenderPresent(g_screen);
        SDL_Delay(16);
        }
        pause_duration += SDL_GetTicks() - pause_start_ticks;

        continue;
        }
        fps_timer.start();
        while(SDL_PollEvent(&g_event)!=0)
              {
                  if (g_event.type == SDL_KEYDOWN) {
        switch (g_event.key.keysym.sym) {
        case SDLK_EQUALS:
            sound.setMusicVolume(sound.getMusicVolume() + 10);
            break;
        case SDLK_MINUS:
            sound.setMusicVolume(sound.getMusicVolume() - 10);
            break;
        case SDLK_m:
            sound.setMusicVolume(0);
            break;
        case SDLK_0:
        sound.is_enemy_sound_on = !sound.is_enemy_sound_on;
            break;
        case SDLK_p:
        if (!is_paused) {
            is_paused = true;
            pause_start_ticks = SDL_GetTicks();
            } else {
            is_paused = false;
        pause_duration += SDL_GetTicks() - pause_start_ticks;
        }
            break;
        case SDLK_8:
            sound.setEffectVolume(sound.getEffectVolume() - 10);
            break;
        case SDLK_9:
            sound.setEffectVolume(sound.getEffectVolume() + 10);
            break;
        case SDLK_n:
            sound.setEffectVolume(0);
            break;
            }
            }
                if(g_event.type==SDL_QUIT)
                {
                      is_quit=true;
                }
                p_player.HandelInputAction(g_event,g_screen);
                    }
                if (p_player.getWin())
                {
                ShowVictoryScreen(g_screen);
                is_quit = true;
                break;
                }
                SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
                SDL_RenderClear(g_screen);
                RenderScrollingBackground(offsetSpeed, gBackgroundTexture, g_screen);
                Map map_data=game_map.GetMap();
                p_player.HandleBullet(g_screen, map_data);
                p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
                p_player.DoPlayer(map_data);
                p_player.Show(g_screen);
                game_map.SetMap(map_data);
                game_map.DrawMap(g_screen);
                GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
                ColorData color_data(0, 80, 150);
                Gemotric::RenderRectangle(rectangle_size, color_data, g_screen);

                GeometricFormat outlineSize(1, 1, SCREEN_WIDTH - 1, 38);
                ColorData color_data2(255, 255, 255);
                Gemotric::RenderOutline(outlineSize, color_data2, g_screen);
                player_power.Show(g_screen);
                player_money.Show(g_screen);
                if (SDL_GetTicks() - start_ticks > 500)
                {
                for (int i = 0; i < threats_list.size(); i++)
                {
                ThreatsObject* p_threat = threats_list.at(i);
                if (p_threat != nullptr)
                {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bColl = false;
                std::vector<BulletOj*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); ++jj)
                {
                BulletOj* pt_bullet = tBullet_list.at(jj);
                if (pt_bullet)
                {
                bColl = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                if (bColl)
                {
                p_threat->RemoveBullet(jj);
                break;
                }
                }
                }
            SDL_Rect rect_threat = p_threat->GetRectFrame();
            bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
            if (bColl || bCol2)
                {
            num_die++;
            sound.playEffect("chet");
            if(num_die<=3){
                    isDark = true;  // Bật lớp phủ tối
            p_player.SetRect(0,0) ;
            p_player.set_comeback_time(60);
            SDL_Delay(1000);
            player_power.Decrease();
            player_power.Render(g_screen);
            continue;
            }
            else{
            if (MessageBoxA(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
            p_threat->Free();
            close();
            SDL_Quit();
            return 0;
            }
                }
                }
        }
    }
}
darkScreenEffect.RenderDarkScreen(isDark);
if (p_player.get_comeback_time() == 0)
    {
        isDark = false; // Tắt lớp phủ tối
    }
            std::vector<BulletOj*> bullet_arr = p_player.get_bullet_list();
            for (int r = 0; r < bullet_arr.size(); ++r)
            {
            BulletOj* p_bullet = bullet_arr.at(r);
            if (p_bullet != nullptr)
            {
            for (int t = 0; t < threats_list.size(); ++t)
            {
            ThreatsObject* obj_threat = threats_list.at(t);
            if (obj_threat != NULL)
            {
                SDL_Rect tRect;
                tRect.x = obj_threat->GetRect().x;
                tRect.y = obj_threat->GetRect().y;
                tRect.w = obj_threat->get_width_frame();
                tRect.h = obj_threat->get_height_frame();
                SDL_Rect bRect = p_bullet->GetRect();

                bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                if (bCol && p_bullet->get_is_move())
                {
                    int dx = abs(p_bullet->GetRect().x - obj_threat->GetRect().x);
                    int dy = abs(p_bullet->GetRect().y - obj_threat->GetRect().y);
                    if (dx > 500 || dy > 500) continue;
                    sound.playEffect("no");
                    mark_value++;
                    for(int ex=0;ex< NUM_FRAME_EXP;ex++){
                    int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                    int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                        exp_threat.set_frame(ex);
                        exp_threat.SetRect(x_pos, y_pos);
                        exp_threat.Show(g_screen);
                    }
                    p_player.RemoveBullet(r);
                    obj_threat->Free();
                    threats_list.erase(threats_list.begin() + t);
                    }
                }
            }
        }
    }
        std::string str_time = "Time: ";
        Uint32 current_ticks = SDL_GetTicks();
        Uint32 time_val = (SDL_GetTicks() - start_ticks - pause_duration) / 1000;
        Uint32 val_time = (time_val >= 300) ? 0 : 300 - time_val;


        if (val_time == 0)
        {
        if (MessageBoxW(nullptr, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
        {
        is_quit=true;
        break;
        }
        }
        else
        {
        std::string str_val = std::to_string(val_time);
        str_time += str_val;
        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time, g_screen);
        time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 8);
        }
        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Kill: ");
        strMark += val_str_mark;
        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 8);
        int meat_count=p_player.GetMeatCount();
        std::string meat_str = std::to_string(meat_count);
        meat_game.SetText(meat_str);
        meat_game.LoadFromRenderText(font_time, g_screen);
        meat_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 8);
        int current_music_vol = sound.getMusicVolume();
        int current_effect_vol = sound.getEffectVolume();
        std::string music_str = "Music:" + std::to_string(current_music_vol);
        std::string effect_str = "Effect:" + std::to_string(current_effect_vol);
        music_volume_text.SetText(music_str);
        effect_volume_text.SetText(effect_str);
        music_volume_text.LoadFromRenderText(font_time, g_screen);
        effect_volume_text.LoadFromRenderText(font_time, g_screen);
        music_volume_text.RenderText(g_screen, SCREEN_WIDTH - 350, 8);
        effect_volume_text.RenderText(g_screen, SCREEN_WIDTH - 470, 8);
              SDL_RenderPresent(g_screen);
              int real_imp_time =fps_timer.get_ticks();
              int time_one_frame=1000/FRAME_PER_SECOND;
              if(real_imp_time<time_one_frame)
              {
                  int delay_time =time_one_frame-real_imp_time;
                  if(delay_time>=0)
                  SDL_Delay(delay_time);
              }
    }
    for (int i = 0; i < threats_list.size(); i++)
    {
    ThreatsObject* p_threat = threats_list.at(i);
    if (p_threat)
    {
        p_threat->Free();
        p_threat = NULL;
    }
    }
    threats_list.clear();
    close();
    return 0;
    }
    bool ShowVictoryScreen(SDL_Renderer* renderer)
    {
    SDL_Surface* victory_surface = IMG_Load("D:\\gamebansung\\map\\win.png");
    sound.stopMusic();
    sound.loadMusic("D:\\gamebansung\\sound\\credits.mp3");
    sound.playMusic(0);
    if (!victory_surface) return false;
    SDL_Texture* victory_texture = SDL_CreateTextureFromSurface(renderer, victory_surface);
    SDL_FreeSurface(victory_surface);
    if (!victory_texture) return false;
    SDL_RenderClear(renderer);
    SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, victory_texture, NULL, &renderQuad);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyTexture(victory_texture);
    return true;
}
