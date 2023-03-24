//
// Created by WINDOWS on 3/23/2023.
//
#include "Rect.h"

bool SDLite::Rect::delTexture = true;

SDLite::Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) :
        m_Width(w), m_Height(h), m_R(r), m_G(g), m_B(b), m_A(a)
{
    m_Pos[0] = x;
    m_Pos[1] = y;
}

SDLite::Rect::Rect(int w, int h, int x, int y, const std::string& img_path) :
        m_Width(w), m_Height(h), current_img_path(img_path)
{
    m_Pos[0] = x;
    m_Pos[1] = y;
    m_Texture = Rect::getTexture(img_path.c_str());
}

SDLite::Rect::~Rect()
{
    if (delTexture) {
        SDL_DestroyTexture(m_Texture);
    }
}

void SDLite::Rect::draw() const
{
    SDL_Rect rect = { m_Pos[0], m_Pos[1], m_Width, m_Height }; //probably should store it rather than keep making new rects
    if (m_Texture) {
        SDL_RenderCopy(SDLite::Window::renderer, m_Texture, nullptr, &rect);
    }
    else {
        SDL_SetRenderDrawColor(SDLite::Window::renderer, m_R, m_G, m_B, m_A);
        SDL_RenderFillRect(SDLite::Window::renderer, &rect);
    }
}


bool SDLite::Rect::pollEvents()
{
    if (m_Handler == nullptr) {
        return false;
    }
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        m_Handler(event);
    }
    return true;
}

bool SDLite::Rect::pollEvents(SDL_Event event)
{
    if (m_Handler == nullptr) {
        return false;
    }
    m_Handler(event);
    return true;
}

int* SDLite::Rect::getPos()
{
    return m_Pos;
}

bool SDLite::Rect::setPos(int x, int y)
{
    m_Pos[0] = x;
    m_Pos[1] = y;
    return true;
}

bool SDLite::Rect::setDisplacement(int x, int y)
{
    m_Pos[0] += x;
    m_Pos[1] += y;
    return true;
}

bool SDLite::Rect::changeImage(std::string& img_path)
{
    current_img_path = img_path;
    SDL_DestroyTexture(m_Texture);
    m_Texture = Rect::getTexture(img_path.c_str());
    return true;
}

SDL_Texture* SDLite::Rect::getTexture(std::string img_path)
{
    SDL_Surface* surface = IMG_Load(img_path.c_str());
    if (!surface) {
        std::cerr << "Failed to create surface!\n";
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(SDLite::Window::renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture!\n";
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}
