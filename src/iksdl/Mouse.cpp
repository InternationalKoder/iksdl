/*
 * IKSDL - C++ wrapper for SDL
 * Copyright (C) 2021 InternationalKoder
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "iksdl/Mouse.hpp"
#include <SDL.h>

namespace iksdl
{
bool Mouse::isButtonPressed(Button button)
{
    SDL_PumpEvents();

    uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

    switch(button)
    {
        case Mouse::Button::Left:
            return mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
        case Mouse::Button::Middle:
            return mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE);
        case Mouse::Button::Right:
            return mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT);
        case Mouse::Button::X1:
            return mouseState & SDL_BUTTON(SDL_BUTTON_X1);
        case Mouse::Button::X2:
            return mouseState & SDL_BUTTON(SDL_BUTTON_X2);
    }

    return false;
}

Positioni Mouse::getPosition()
{
    SDL_PumpEvents();

    int x, y;
    SDL_GetMouseState(&x, &y);

    return Positioni(x, y);
}
}
