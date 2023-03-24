//
// Created by WINDOWS on 3/23/2023.
//

#ifndef SDLITE_FRECT_H
#define SDLITE_FRECT_H

#pragma once
#include "Window.h"
#include <SDL_image.h>

namespace SDLite{
    class FRect {
    public:
        FRect(float w, float h, float x, float y, int r, int g, int b, int a);
        FRect(float w, float h, float x, float y, const std::string& img_path);
        ~FRect();
        static bool delTexture;
        void draw()const;

        bool pollEvents();
        bool pollEvents(SDL_Event event);

        float* getPos();
        bool setPos(float x, float y);

        bool setDisplacement(float x, float y);

        bool changeImage(std::string& img_path);

        std::string current_img_path = "";

        float m_Width, m_Height;
        int m_R, m_G, m_B, m_A;

        void (*m_Handler)(SDL_Event&) = nullptr;
        SDL_Texture* m_Texture = nullptr;
        float m_Pos[2] = { 0,0 };

        static SDL_Texture* getTexture(std::string img_path);
    private:
    };
}

#endif //SDLITE_FRECT_H
