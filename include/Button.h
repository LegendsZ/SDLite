//
// Created by WINDOWS on 3/23/2023.
//

#ifndef SDLITE_BUTTON_H
#define SDLITE_BUTTON_H

#pragma once

#include "Rect.h"
#include "Text.h"

namespace SDLite{
    class Button {
    public:
        Button(int w, int h, int x, int y, int r, int g, int b, int a, SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, void(*handler)(SDL_Event&));
        Button(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, void(*handler)(SDL_Event&));
        Button(int w, int h, int x, int y, const std::string& img_path, void(*handler)(SDL_Event&));
        Button(Rect* rect, Text* text, void(*handler)(SDL_Event&));

        bool pollEvents();
        bool pollEvents(SDL_Event event);

        bool setPos(int x, int y);
        int* getPos();


        bool draw();

        Rect* m_Rect;
        Text* m_Text;

        void (*m_Handler)(SDL_Event&);
    private:
    };
}

#endif //SDLITE_BUTTON_H
