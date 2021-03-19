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

#ifndef IKSDL_MOUSE_WHEEL_EVENT_HPP
#define IKSDL_MOUSE_WHEEL_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"

extern "C"
{
struct SDL_MouseWheelEvent;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents an event related to mouse wheel
/////////////////////////////////////////////////
class MouseWheelEvent: public AbstractEvent
{
    public:

        /////////////////////////////////////////////////
        /// \brief Mouse wheel directions
        /////////////////////////////////////////////////
        enum class WheelDirection { Normal, Flipped };

        /////////////////////////////////////////////////
        /// \brief Constructor from SDL mouse wheel event
        ///
        /// \param sdlEvent SDK mouse wheel event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit MouseWheelEvent(const SDL_MouseWheelEvent& sdlEvent);

        /////////////////////////////////////////////////
        /// \brief Make the given handler execute the action related to the mouse wheel event
        ///
        /// \param handler Event handler that will be asked to consume the mouse wheel event
        /////////////////////////////////////////////////
        inline virtual void play(EventHandler& handler) const { handler.handleMouseWheelEvent(*this); }

        /////////////////////////////////////////////////
        /// \brief Get the movement done by the mouse wheel
        ///
        /// \return Scroll amount
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Sizei& getScrollAmount() const { return m_scrollAmount; }

        /////////////////////////////////////////////////
        /// \brief Get the wheel scroll direction
        ///
        /// \return Wheel direction
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline WheelDirection getWheelDirection() const { return m_wheelDirection; }

    private:

        Sizei m_scrollAmount;            ///< Scroll amount
        WheelDirection m_wheelDirection; ///< Wheel direction
};

}

#endif // IKSDL_MOUSE_WHEEL_EVENT_HPP
