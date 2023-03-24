//
// Created by WINDOWS on 3/23/2023.
//
#include "Window.h"
#include "Text.h"

SDL_Renderer* SDLite::Window::renderer = nullptr;

SDLite::Window::Window(const std::string& title, int width, int height) :
        m_Title(title), m_Width(width), m_Height(height)
{
    m_isClosed = !init();
}

SDLite::Window::~Window() {
    Mix_FreeMusic(menuSound);
    Mix_FreeMusic(gameSound);
    Mix_FreeChunk(click_effect);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(m_Window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

bool SDLite::Window::setWindowIcon(std::string path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to create surface!\n";
        return false;
    }
    SDL_SetWindowIcon(m_Window, surface);
    SDL_FreeSurface(surface);
    return true;
}

void SDLite::Window::pollEvents(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_QUIT:
            m_isClosed = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    break;
                case SDLK_a:
                    break;
                case SDLK_s:
                    break;
                case SDLK_d:
                    break;
                case SDLK_ESCAPE:
                    //escape menu?
                    m_isClosed = true; //pause here
                    break;
            }
        case SDL_MOUSEMOTION:
            //std::cout << "Mouse Location: [" << event.motion.x << ", " << event.motion.y << "]!\n";
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        default:
            break;
    }
}

void SDLite::Window::clear() const
{
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, m_R, m_G, m_B, m_A);
    SDL_RenderClear(renderer);
}

bool SDLite::Window::isClosed() const
{
    return m_isClosed;
}

bool SDLite::Window::close()
{
    m_isClosed = true;
    return true;
}

bool SDLite::Window::init() {
    std::cout << "Initializing...";
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "\nFailed to initailize video!\n";
        return false;
    }

    int result = 0;
    if (MIX_INIT_MP3 != (result = Mix_Init(MIX_INIT_MP3))) {
        std::cout << "Could not initialize mixer (result: " << result << ").\n";
        std::cout << "Mix_Init: "<<  Mix_GetError() << "\n";
        return false;
    }
    //Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2096) < 0) {
        std::cout << "Could not initialize mixer (result: " << result << ").\n";
        std::cout << "Open Audio: " << Mix_GetError() << "\n";
        return false;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "\nFailed to initailize sdl_image!\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "\nFailed to initailize sdl_ttf!\n";
        return false;
    }

    m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_HIDDEN);

    if (m_Window == nullptr) {
        std::cerr << "\nFailed to create window!\n";
        return false;
    }

    renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    new Text(Window::renderer, "res/comic.ttf", 35, "Enemies Left: ", { 0,255,0,255 });


    if (renderer == nullptr) {
        std::cerr << "\nFailed to create renderer!\n";
        return false;
    }
    std::cout << "OK!\n";

    return true;
}