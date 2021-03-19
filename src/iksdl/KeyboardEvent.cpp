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

#include "iksdl/KeyboardEvent.hpp"
#include "iksdl/SdlException.hpp"
#include "iksdl/common.hpp"
#include <SDL.h>
#include <algorithm>

namespace iksdl
{
KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& sdlEvent) :
    m_repeat(sdlEvent.repeat != 0)
{
    // Mapping for event type
    switch(sdlEvent.type)
    {
        case SDL_KEYDOWN:
            m_type = Type::KeyDown;
            break;
        case SDL_KEYUP:
            m_type = Type::KeyUp;
            break;
        default:
            throw SdlException(UNKNOWN_EVENT_TYPE.data());
    }

    // Mapping for key state
    switch(sdlEvent.state)
    {
        case SDL_PRESSED:
            m_keyState = KeyState::Pressed;
            break;
        case SDL_RELEASED:
            m_keyState = KeyState::Released;
            break;
        default:
            throw SdlException(UNKNOWN_EVENT_TYPE.data());
    }

    // Mapping for key
    static const std::vector<std::pair<int, Keyboard::Key>> keyMap = [] ()
    {
        std::vector<std::pair<int, Keyboard::Key>> map(
        {
            { SDLK_a, Keyboard::Key::A },
            { SDLK_b, Keyboard::Key::B },
            { SDLK_c, Keyboard::Key::C },
            { SDLK_d, Keyboard::Key::D },
            { SDLK_e, Keyboard::Key::E },
            { SDLK_f, Keyboard::Key::F },
            { SDLK_g, Keyboard::Key::G },
            { SDLK_h, Keyboard::Key::H },
            { SDLK_i, Keyboard::Key::I },
            { SDLK_j, Keyboard::Key::J },
            { SDLK_k, Keyboard::Key::K },
            { SDLK_l, Keyboard::Key::L },
            { SDLK_m, Keyboard::Key::M },
            { SDLK_n, Keyboard::Key::N },
            { SDLK_o, Keyboard::Key::O },
            { SDLK_p, Keyboard::Key::P },
            { SDLK_q, Keyboard::Key::Q },
            { SDLK_r, Keyboard::Key::R },
            { SDLK_s, Keyboard::Key::S },
            { SDLK_t, Keyboard::Key::T },
            { SDLK_u, Keyboard::Key::U },
            { SDLK_v, Keyboard::Key::V },
            { SDLK_w, Keyboard::Key::W },
            { SDLK_x, Keyboard::Key::X },
            { SDLK_y, Keyboard::Key::Y },
            { SDLK_z, Keyboard::Key::Z },
            { SDLK_0, Keyboard::Key::Zero },
            { SDLK_1, Keyboard::Key::One },
            { SDLK_2, Keyboard::Key::Two },
            { SDLK_3, Keyboard::Key::Three },
            { SDLK_4, Keyboard::Key::Four },
            { SDLK_5, Keyboard::Key::Five },
            { SDLK_6, Keyboard::Key::Six },
            { SDLK_7, Keyboard::Key::Seven },
            { SDLK_8, Keyboard::Key::Eight },
            { SDLK_9, Keyboard::Key::Nine },
            { SDLK_KP_0, Keyboard::Key::Num0 },
            { SDLK_KP_1, Keyboard::Key::Num1 },
            { SDLK_KP_2, Keyboard::Key::Num2 },
            { SDLK_KP_3, Keyboard::Key::Num3 },
            { SDLK_KP_4, Keyboard::Key::Num4 },
            { SDLK_KP_5, Keyboard::Key::Num5 },
            { SDLK_KP_6, Keyboard::Key::Num6 },
            { SDLK_KP_7, Keyboard::Key::Num7 },
            { SDLK_KP_8, Keyboard::Key::Num8 },
            { SDLK_KP_9, Keyboard::Key::Num9 },
            { SDLK_DOWN, Keyboard::Key::DownArrow },
            { SDLK_UP, Keyboard::Key::UpArrow },
            { SDLK_LEFT, Keyboard::Key::LeftArrow },
            { SDLK_RIGHT, Keyboard::Key::RightArrow },
            { SDLK_F1, Keyboard::Key::F1 },
            { SDLK_F2, Keyboard::Key::F2 },
            { SDLK_F3, Keyboard::Key::F3 },
            { SDLK_F4, Keyboard::Key::F4 },
            { SDLK_F5, Keyboard::Key::F5 },
            { SDLK_F6, Keyboard::Key::F6 },
            { SDLK_F7, Keyboard::Key::F7 },
            { SDLK_F8, Keyboard::Key::F8 },
            { SDLK_F9, Keyboard::Key::F9 },
            { SDLK_F10, Keyboard::Key::F10 },
            { SDLK_F11, Keyboard::Key::F11 },
            { SDLK_F12, Keyboard::Key::F12 },
            { SDLK_QUOTE, Keyboard::Key::Quote },
            { SDLK_BACKSLASH, Keyboard::Key::Backslash },
            { SDLK_COMMA, Keyboard::Key::Comma },
            { SDLK_EQUALS, Keyboard::Key::Equals },
            { SDLK_BACKQUOTE, Keyboard::Key::BackQuote },
            { SDLK_KP_DIVIDE, Keyboard::Key::NumDivide },
            { SDLK_KP_MINUS, Keyboard::Key::NumMinus },
            { SDLK_KP_MULTIPLY, Keyboard::Key::NumMultiply },
            { SDLK_KP_PLUS, Keyboard::Key::NumPlus },
            { SDLK_KP_PERIOD, Keyboard::Key::NumPeriod },
            { SDLK_LEFTBRACKET, Keyboard::Key::LeftBracket },
            { SDLK_MINUS, Keyboard::Key::Minus },
            { SDLK_NUMLOCKCLEAR, Keyboard::Key::Numlock },
            { SDLK_PERIOD, Keyboard::Key::Period },
            { SDLK_RIGHTBRACKET, Keyboard::Key::RightBracket },
            { SDLK_SEMICOLON, Keyboard::Key::SemiColon },
            { SDLK_SLASH, Keyboard::Key::Slash },
            { SDLK_APPLICATION, Keyboard::Key::Application },
            { SDLK_BACKSPACE, Keyboard::Key::Backspace },
            { SDLK_CAPSLOCK, Keyboard::Key::CapsLock },
            { SDLK_DELETE, Keyboard::Key::Delete },
            { SDLK_END, Keyboard::Key::End },
            { SDLK_ESCAPE, Keyboard::Key::Escape},
            { SDLK_INSERT, Keyboard::Key::Insert },
            { SDLK_KP_ENTER, Keyboard::Key::NumEnter },
            { SDLK_LALT, Keyboard::Key::LeftAlt },
            { SDLK_LCTRL, Keyboard::Key::LeftCtrl },
            { SDLK_LSHIFT, Keyboard::Key::LeftShift },
            { SDLK_PAGEUP, Keyboard::Key::PageUp },
            { SDLK_PAGEDOWN, Keyboard::Key::PageDown },
            { SDLK_PAUSE, Keyboard::Key::Pause },
            { SDLK_PRINTSCREEN, Keyboard::Key::PrintScreen },
            { SDLK_RALT, Keyboard::Key::RightAlt },
            { SDLK_RCTRL, Keyboard::Key::RightCtrl },
            { SDLK_RETURN, Keyboard::Key::Return },
            { SDLK_RSHIFT, Keyboard::Key::RightShift },
            { SDLK_SCROLLLOCK, Keyboard::Key::ScrollLock},
            { SDLK_SPACE, Keyboard::Key::Space },
            { SDLK_TAB, Keyboard::Key::Tab }
        });

        std::sort(map.begin(), map.end(), comparePairKeys<int, Keyboard::Key>);
        map.shrink_to_fit();

        return map;
    }();

    // Set key
    const auto it = std::lower_bound(keyMap.begin(), keyMap.end(), std::make_pair(sdlEvent.keysym.sym, Keyboard::Key::A),
                                     comparePairKeys<int, Keyboard::Key>);

    if(it != keyMap.end() && it->first == sdlEvent.keysym.sym)
        m_key = it->second;
    else
        throw SdlException(UNKNOWN_EVENT_TYPE.data());

    // Mapping for modifiers
    const auto& mod = sdlEvent.keysym.mod;

    bool any = false;
    if(mod & KMOD_LSHIFT)
    {
        m_modifiers.push_back(Modifier::LeftShift);
        any = true;
    }
    if(mod & KMOD_RSHIFT)
    {
        m_modifiers.push_back(Modifier::RightShift);
        any = true;
    }
    if(any)
         m_modifiers.push_back(Modifier::AnyShift);

    any = false;
    if(mod & KMOD_LCTRL)
    {
        m_modifiers.push_back(Modifier::LeftCtrl);
        any = true;
    }
    if(mod & KMOD_RCTRL)
    {
        m_modifiers.push_back(Modifier::RightCtrl);
        any = true;
    }
    if(any)
         m_modifiers.push_back(Modifier::AnyCtrl);

    any = false;
    if(mod & KMOD_LALT)
    {
        m_modifiers.push_back(Modifier::LeftAlt);
        any = true;
    }
    if(mod & KMOD_RALT)
    {
        m_modifiers.push_back(Modifier::RightAlt);
        any = true;
    }
    if(any)
        m_modifiers.push_back(Modifier::AnyAlt);


    if(mod & KMOD_NUM)
        m_modifiers.push_back(Modifier::NumLock);

    if(mod & KMOD_CAPS)
        m_modifiers.push_back(Modifier::CapsLock);

    if(mod & KMOD_MODE)
        m_modifiers.push_back(Modifier::AltGr);
}
}
