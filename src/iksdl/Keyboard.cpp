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

#include "iksdl/Keyboard.hpp"
#include "iksdl/common.hpp"
#include <vector>
#include <algorithm>

namespace iksdl
{
bool Keyboard::isKeyPressed(Key key)
{
    // Mapping for key
    static const std::vector<std::pair<Key, int>> keyMap = [] ()
    {
        std::vector<std::pair<Key, int>> map(
        {
            { Key::A, SDL_SCANCODE_A },
            { Key::B, SDL_SCANCODE_B },
            { Key::C, SDL_SCANCODE_C },
            { Key::D, SDL_SCANCODE_D },
            { Key::E, SDL_SCANCODE_E },
            { Key::F, SDL_SCANCODE_F },
            { Key::G, SDL_SCANCODE_G },
            { Key::H, SDL_SCANCODE_H },
            { Key::I, SDL_SCANCODE_I },
            { Key::J, SDL_SCANCODE_J },
            { Key::K, SDL_SCANCODE_K },
            { Key::L, SDL_SCANCODE_L },
            { Key::M, SDL_SCANCODE_M },
            { Key::N, SDL_SCANCODE_N },
            { Key::O, SDL_SCANCODE_O },
            { Key::P, SDL_SCANCODE_P },
            { Key::Q, SDL_SCANCODE_Q },
            { Key::R, SDL_SCANCODE_R },
            { Key::S, SDL_SCANCODE_S },
            { Key::T, SDL_SCANCODE_T },
            { Key::U, SDL_SCANCODE_U },
            { Key::V, SDL_SCANCODE_V },
            { Key::W, SDL_SCANCODE_W },
            { Key::X, SDL_SCANCODE_X },
            { Key::Y, SDL_SCANCODE_Y },
            { Key::Z, SDL_SCANCODE_Z },
            { Key::Zero, SDL_SCANCODE_0 },
            { Key::One, SDL_SCANCODE_1 },
            { Key::Two, SDL_SCANCODE_2 },
            { Key::Three, SDL_SCANCODE_3 },
            { Key::Four, SDL_SCANCODE_4 },
            { Key::Five, SDL_SCANCODE_5 },
            { Key::Six, SDL_SCANCODE_6 },
            { Key::Seven, SDL_SCANCODE_7 },
            { Key::Eight, SDL_SCANCODE_8 },
            { Key::Nine, SDL_SCANCODE_9 },
            { Key::Num0, SDL_SCANCODE_KP_0 },
            { Key::Num1, SDL_SCANCODE_KP_1 },
            { Key::Num2, SDL_SCANCODE_KP_2 },
            { Key::Num3, SDL_SCANCODE_KP_3 },
            { Key::Num4, SDL_SCANCODE_KP_4 },
            { Key::Num5, SDL_SCANCODE_KP_5 },
            { Key::Num6, SDL_SCANCODE_KP_6 },
            { Key::Num7, SDL_SCANCODE_KP_7 },
            { Key::Num8, SDL_SCANCODE_KP_8 },
            { Key::Num9, SDL_SCANCODE_KP_9 },
            { Key::DownArrow, SDL_SCANCODE_DOWN },
            { Key::UpArrow, SDL_SCANCODE_UP },
            { Key::LeftArrow, SDL_SCANCODE_LEFT },
            { Key::RightArrow, SDL_SCANCODE_RIGHT },
            { Key::F1, SDL_SCANCODE_F1 },
            { Key::F2, SDL_SCANCODE_F2 },
            { Key::F3, SDL_SCANCODE_F3 },
            { Key::F4, SDL_SCANCODE_F4 },
            { Key::F5, SDL_SCANCODE_F5 },
            { Key::F6, SDL_SCANCODE_F6 },
            { Key::F7, SDL_SCANCODE_F7 },
            { Key::F8, SDL_SCANCODE_F8 },
            { Key::F9, SDL_SCANCODE_F9 },
            { Key::F10, SDL_SCANCODE_F10 },
            { Key::F11, SDL_SCANCODE_F11 },
            { Key::F12, SDL_SCANCODE_F12 },
            { Key::Quote, SDL_SCANCODE_APOSTROPHE },
            { Key::Backslash, SDL_SCANCODE_BACKSLASH },
            { Key::Comma, SDL_SCANCODE_COMMA },
            { Key::Equals, SDL_SCANCODE_EQUALS },
            { Key::BackQuote, SDL_SCANCODE_GRAVE },
            { Key::NumDivide, SDL_SCANCODE_KP_DIVIDE },
            { Key::NumMinus, SDL_SCANCODE_KP_MINUS },
            { Key::NumMultiply, SDL_SCANCODE_KP_MULTIPLY },
            { Key::NumPlus, SDL_SCANCODE_KP_PLUS },
            { Key::NumPeriod, SDL_SCANCODE_KP_PERIOD },
            { Key::LeftBracket, SDL_SCANCODE_LEFTBRACKET },
            { Key::Minus, SDL_SCANCODE_MINUS },
            { Key::Numlock, SDL_SCANCODE_NUMLOCKCLEAR },
            { Key::Period, SDL_SCANCODE_PERIOD },
            { Key::RightBracket, SDL_SCANCODE_RIGHTBRACKET },
            { Key::SemiColon, SDL_SCANCODE_SEMICOLON },
            { Key::Slash, SDL_SCANCODE_SLASH },
            { Key::Application, SDL_SCANCODE_APPLICATION },
            { Key::Backspace, SDL_SCANCODE_BACKSPACE },
            { Key::CapsLock, SDL_SCANCODE_CAPSLOCK },
            { Key::Delete, SDL_SCANCODE_DELETE },
            { Key::End, SDL_SCANCODE_END },
            { Key::Escape, SDL_SCANCODE_ESCAPE },
            { Key::Insert, SDL_SCANCODE_INSERT },
            { Key::NumEnter, SDL_SCANCODE_KP_ENTER },
            { Key::LeftAlt, SDL_SCANCODE_LALT },
            { Key::LeftCtrl, SDL_SCANCODE_LCTRL },
            { Key::LeftShift, SDL_SCANCODE_LSHIFT },
            { Key::PageUp, SDL_SCANCODE_PAGEUP },
            { Key::PageDown, SDL_SCANCODE_PAGEDOWN },
            { Key::Pause, SDL_SCANCODE_PAUSE },
            { Key::PrintScreen, SDL_SCANCODE_PRINTSCREEN },
            { Key::RightAlt, SDL_SCANCODE_RALT },
            { Key::RightCtrl, SDL_SCANCODE_RCTRL },
            { Key::Return, SDL_SCANCODE_RETURN },
            { Key::RightShift, SDL_SCANCODE_RSHIFT },
            { Key::ScrollLock, SDL_SCANCODE_SCROLLLOCK },
            { Key::Space, SDL_SCANCODE_SPACE },
            { Key::Tab, SDL_SCANCODE_TAB }
        });

        std::sort(map.begin(), map.end(), comparePairKeys<Key, int>);

        return map;
    }();

    const auto it = std::lower_bound(keyMap.begin(), keyMap.end(), std::make_pair(key, SDL_SCANCODE_A), comparePairKeys<Key, int>);

    if(it == keyMap.end() || it->first != key)
        return false;

    static const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
    SDL_PumpEvents();

    return keyboardState[it->second];
}
}
