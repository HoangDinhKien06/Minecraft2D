#include "Sound.h"
Sound::Sound() : backgroundMusic_(nullptr) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}
Sound::~Sound() {
    stopMusic();
    if (backgroundMusic_) {
        Mix_FreeMusic(backgroundMusic_);
        backgroundMusic_ = nullptr;
    }
    for (auto& pair : effectMap_) {
        Mix_FreeChunk(pair.second);
    }
    Mix_CloseAudio();
}
bool Sound::loadMusic(const std::string& path) {
    backgroundMusic_ = Mix_LoadMUS(path.c_str());
    if (!backgroundMusic_) {
        std::cerr << "Lỗi load nhạc nền: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
void Sound::playMusic(int loops) {
    if (backgroundMusic_) {
        Mix_PlayMusic(backgroundMusic_, loops);
    }
}
void Sound::stopMusic() {
    Mix_HaltMusic();
}
bool Sound::loadEffect(const std::string& name, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "Lỗi load effect: " << Mix_GetError() << std::endl;
        return false;
    }
    effectMap_[name] = chunk;
    return true;
}
void Sound::playEffect(const std::string& name, int loops) {
    auto it = effectMap_.find(name);
    if (it != effectMap_.end()) {
        Mix_PlayChannel(-1, it->second, loops);  // -1: tự chọn kênh
    }
}
void Sound::setMusicVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    Mix_VolumeMusic(volume);
}
void Sound::setEffectVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    for (auto& pair : effectMap_) {
        Mix_VolumeChunk(pair.second, volume);
    }
}
int Sound::getMusicVolume() const {
    return Mix_VolumeMusic(-1);
}
int Sound::getEffectVolume() const {
    if (!effectMap_.empty()) {
        return Mix_VolumeChunk(effectMap_.begin()->second, -1);
    }
    return 0;
}


