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

#ifndef IKSDL_WINDOW_EVENT_HPP
#define IKSDL_WINDOW_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"
#include <optional>
#include <cstdint>

extern "C"
{
struct SDL_WindowEvent;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents an event related to a window
/////////////////////////////////////////////////
class WindowEvent : public AbstractEvent
{
    public:

        /////////////////////////////////////////////////
        /// \brief Window event type
        /////////////////////////////////////////////////
        enum class Type { Shown, Hidden, Exposed, Moved, Resized,
                          SizeChanged, Minimized, Maximized, Restored,
                          MouseEntered, MouseLeft, FocusGained, FocusLost, Close,
                          TakeFocus, HitTest };

        /////////////////////////////////////////////////
        /// \brief Constructor from SDL window event
        ///
        /// \param sdlEvent SDL window event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit WindowEvent(const SDL_WindowEvent& sdlEvent);

        /////////////////////////////////////////////////
        /// \brief Make the given handler execute the action related to the keyboard event
        ///
        /// \param handler Event handler that will be asked to consume the window event
        /////////////////////////////////////////////////
        inline virtual void play(EventHandler& handler) const { handler.handleWindowEvent(*this); }

        /////////////////////////////////////////////////
        /// \brief Get the window event type
        ///
        /// \return Window event type
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Type getType() const { return m_type; }

        /////////////////////////////////////////////////
        /// \brief If the window has been moved, get the new position
        ///
        /// \return New window position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const std::optional<Positioni>& getMovedToPosition() const { return m_movedTo; }

        /////////////////////////////////////////////////
        /// \brief If the window has been resized, get the new size
        ///
        /// \return New window size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const std::optional<Sizei>& getResizedToSize() const { return m_resizedTo; }

    private:

        Type m_type;                        ///< Window event type
        std::optional<Positioni> m_movedTo; ///< New window position, if it has been moved
        std::optional<Sizei> m_resizedTo;   ///< New window size, if it has been resized
};

}

#endif // IKSDL_WINDOW_EVENT_HPP
