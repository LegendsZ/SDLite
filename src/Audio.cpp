//
// Created by WINDOWS on 3/23/2023.
//
#include "Audio.h"

SDLite::Audio* SDLite::Audio::instance = nullptr;

SDLite::Audio* SDLite::Audio::makeInstance()
{
    if (instance == nullptr) {
        instance = new Audio();
    }
    return instance;;
}

Mix_Chunk* SDLite::Audio::getChunk(std::string filepath)
{
    return Mix_LoadWAV(filepath.c_str());
}

void SDLite::Audio::Release()
{
    delete instance;
    instance = nullptr;
}

void SDLite::Audio::playMusic(Mix_Music* music, int loops)
{
    Mix_PlayMusic(music, loops);
}

void SDLite::Audio::pauseMusic()
{
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void SDLite::Audio::resumeMusic()
{
    if (Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}

void SDLite::Audio::playEffect(Mix_Chunk* effect, int loops, int channel)
{
    Mix_PlayChannel(channel, effect, loops);
}
