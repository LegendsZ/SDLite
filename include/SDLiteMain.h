#ifndef SDLITE_LIBRARY_H
#define SDLITE_LIBRARY_H

#include<iostream>
#include "Window.h"
#include "Text.h"
#include "Rect.h"
#include "FRect.h"
#include "Button.h"
#include "Audio.h"

#define VERSION "1.0.0.0"
namespace SDLite{
    class SDLiteMain {
    public:
        void static printVersion();
    };
}

#endif //SDLITE_LIBRARY_H
