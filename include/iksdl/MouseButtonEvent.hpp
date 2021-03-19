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

#ifndef IKSDL_MOUSE_BUTTON_EVENT_HPP
#define IKSDL_MOUSE_BUTTON_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Mouse.hpp"
#include "iksdl/iksdl_export.hpp"
#include <cstdint>

extern "C"
{
struct SDL_MouseButtonEvent;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents an event related to mouse buttons
/////////////////////////////////////////////////
class MouseButtonEvent: public AbstractEvent
{
    public:

        /////////////////////////////////////////////////
        /// \brief Mouse button state
        /////////////////////////////////////////////////
        enum class State { Pressed, Released };

        /////////////////////////////////////////////////
        /// \brief Constructor from SDL mouse button event
        ///
        /// \param sdlEvent SDL mouse button event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit MouseButtonEvent(const SDL_MouseButtonEvent& sdlEvent);

        /////////////////////////////////////////////////
        /// \brief Make the given handler execute the action related to the mouse button event
        ///
        /// \param handler Event handler that will be asked to consume the mouse button event
        /////////////////////////////////////////////////
        inline virtual void play(EventHandler& handler) const { handler.handleMouseButtonEvent(*this); }

        /////////////////////////////////////////////////
        /// \brief Get the mouse button that the event is about
        ///
        /// \return The mouse button
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Mouse::Button getButton() const { return m_button; }

        /////////////////////////////////////////////////
        /// \brief Get the mouse button state
        ///
        /// \return Mouse button state
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline State getButtonState() const { return m_buttonState; }

        /////////////////////////////////////////////////
        /// \brief Get the number of clicks on the button
        ///
        /// \return Number of clicks
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline uint8_t getClicksCount() const { return m_clicksCount; }

        /////////////////////////////////////////////////
        /// \brief Get the mouse position when the event occurred
        ///
        /// \return Mouse position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Positioni& getMousePosition() const { return m_mousePosition; }

    private:

        Mouse::Button m_button;    ///< Mouse button that the event is about
        State m_buttonState;       ///< State of the mouse button
        uint8_t m_clicksCount;     ///< Number of mouse button clicks
        Positioni m_mousePosition; ///< Mouse position when the event occurred
};

}

#endif // IKSDL_MOUSE_BUTTON_EVENT_HPP
