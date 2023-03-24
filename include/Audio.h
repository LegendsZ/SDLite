//
// Created by WINDOWS on 3/23/2023.
//

#ifndef SDLITE_AUDIO_H
#define SDLITE_AUDIO_H

#pragma once
#include <SDL_mixer.h>
#include <string>

namespace SDLite{
    class Audio {
    public:

        static Audio* instance;
        static Audio* makeInstance();

        static Mix_Chunk* getChunk(std::string filepath);

        static void Release();
        static void playMusic(Mix_Music* music, int loops = -1);
        static void pauseMusic();
        static void resumeMusic();

        static void playEffect(Mix_Chunk* effect, int loops = 0, int channel = 0);

    private:
    };
}

#endif //SDLITE_AUDIO_H
