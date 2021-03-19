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

#ifndef IKSDL_MOUSE_HPP
#define IKSDL_MOUSE_HPP

#include "iksdl/Position.hpp"
#include "iksdl/iksdl_export.hpp"

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Allows to interact with the mouse
/////////////////////////////////////////////////
class Mouse
{
    public:

        /////////////////////////////////////////////////
        /// \brief Mouse buttons
        /////////////////////////////////////////////////
        enum class Button { Left, Middle, Right, X1, X2 };

        /////////////////////////////////////////////////
        /// \brief Check whether a button is pressed
        ///
        /// \param button Button to check
        ///
        /// \return True if the button is currently pressed
        /////////////////////////////////////////////////
        IKSDL_EXPORT static bool isButtonPressed(Button button);

        /////////////////////////////////////////////////
        /// \brief Get mouse position
        ///
        /// \return Current mouse position
        /////////////////////////////////////////////////
        IKSDL_EXPORT static Positioni getPosition();
};

}

#endif // IKSDL_MOUSE_HPP
