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

#ifndef IKSDL_KEYBOARD_HPP
#define IKSDL_KEYBOARD_HPP

#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <utility>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Allows to interact with the keyboard
/////////////////////////////////////////////////
class Keyboard
{
    public:

        /////////////////////////////////////////////////
        /// \brief Keyboard keys
        /////////////////////////////////////////////////
        enum class Key
        {
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
            Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
            DownArrow, UpArrow, LeftArrow, RightArrow,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            Quote, Backslash, Comma, Equals, BackQuote, NumDivide, NumMinus, NumMultiply, NumPlus, NumPeriod,
            LeftBracket, Minus, Numlock, Period, RightBracket, SemiColon, Slash,
            Application, Backspace, CapsLock, Delete, End, Escape, Insert, NumEnter, LeftAlt, LeftCtrl, LeftShift,
            PageUp, PageDown, Pause, PrintScreen, RightAlt, RightCtrl, Return, RightShift, ScrollLock, Space, Tab
        };

        /////////////////////////////////////////////////
        /// \brief Check whether a key is pressed
        ///
        /// \param key Key to check
        ///
        /// \return True if the key is currently pressed
        /////////////////////////////////////////////////
        IKSDL_EXPORT static bool isKeyPressed(Key key);
};

}

#endif // IKSDL_KEYBOARD_HPP
