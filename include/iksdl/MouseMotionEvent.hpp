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

#ifndef IKSDL_MOUSE_MOTION_EVENT_HPP
#define IKSDL_MOUSE_MOTION_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/iksdl_export.hpp"

extern "C"
{
struct SDL_MouseMotionEvent;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents an event related to a mouse movement
/////////////////////////////////////////////////
class MouseMotionEvent: public AbstractEvent
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor from SDL mouse motion event
        ///
        /// \param sdlEvent SDL mouse motion event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit MouseMotionEvent(const SDL_MouseMotionEvent& sdlEvent);

        /////////////////////////////////////////////////
        /// \brief Make the fiven handler execute the action related to the mouse motion event
        ///
        /// \param handler Event handler that will be asked to consume the mouse motion event
        /////////////////////////////////////////////////
        inline virtual void play(EventHandler& handler) const { handler.handleMouseMotionEvent(*this); }

        /////////////////////////////////////////////////
        /// \brief Get the new mouse position, after the movement
        ///
        /// \return New mouse position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Positioni& getMousePosition() const { return m_mousePosition; }

        /////////////////////////////////////////////////
        /// \brief Get the mouse movement relative to the previous position
        ///
        /// \return Mouse relative movement
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Positioni& getMouseRelativeMovement() const { return m_mouseRelativeMovement; }

    private:

        Positioni m_mousePosition;         ///< New mouse position
        Positioni m_mouseRelativeMovement; ///< Mouse relative movement
};

}

#endif // IKSDL_MOUSE_MOTION_EVENT_HPP
