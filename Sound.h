#ifndef SOUND_H
#define SOUND_H
#include "CommonFunc.h"
class Sound {
public:
    Sound();
    ~Sound();
    bool loadMusic(const std::string& path);
    void playMusic(int loops = -1);
    void stopMusic();
    bool loadEffect(const std::string& name, const std::string& path);
    void playEffect(const std::string& name, int loops = 0);
void setMusicVolume(int volume);
void setEffectVolume(int volume);
int getMusicVolume() const;
int getEffectVolume() const;
bool is_enemy_sound_on = true;
private:
    Mix_Music* backgroundMusic_;
    std::map<std::string, Mix_Chunk*> effectMap_;
};
extern Sound sound;
#endif
