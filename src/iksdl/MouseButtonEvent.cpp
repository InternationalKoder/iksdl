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

#include "iksdl/MouseButtonEvent.hpp"
#include "iksdl/SdlException.hpp"
#include <SDL.h>

namespace iksdl
{
MouseButtonEvent::MouseButtonEvent(const SDL_MouseButtonEvent& sdlEvent) :
    m_clicksCount(sdlEvent.clicks),
    m_mousePosition(sdlEvent.x, sdlEvent.y)
{
    // Mapping for mouse button
    switch(sdlEvent.button)
    {
        case SDL_BUTTON_LEFT:
            m_button = Mouse::Button::Left;
            break;
        case SDL_BUTTON_MIDDLE:
            m_button = Mouse::Button::Middle;
            break;
        case SDL_BUTTON_RIGHT:
            m_button = Mouse::Button::Right;
            break;
        case SDL_BUTTON_X1:
            m_button = Mouse::Button::X1;
            break;
        case SDL_BUTTON_X2:
            m_button = Mouse::Button::X2;
            break;
        default:
            throw SdlException(UNKNOWN_EVENT_TYPE.data());
    }

    // Mapping for button state
    switch(sdlEvent.state)
    {
        case SDL_PRESSED:
            m_buttonState = State::Pressed;
            break;
        case SDL_RELEASED:
            m_buttonState = State::Released;
            break;
        default:
            throw SdlException(UNKNOWN_EVENT_TYPE.data());
    }
}
}
