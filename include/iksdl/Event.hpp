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

#ifndef IKSDL_EVENT_HPP
#define IKSDL_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/iksdl_export.hpp"
#include <memory>

namespace iksdl
{
class EventHandler;

/////////////////////////////////////////////////
/// \brief Represents an event that can be handled
///
/// It is not the event itself, but a container of an event.
/////////////////////////////////////////////////
class Event
{
    public:

        /////////////////////////////////////////////////
        /// \brief Type of event
        /////////////////////////////////////////////////
        enum class Type { Window, Keyboard, MouseMotion, MouseButton, MouseWheel };

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// \param event Underlying event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit Event(std::unique_ptr<AbstractEvent> event);

        /////////////////////////////////////////////////
        /// \brief Make the given handler execute the action related to the contained event
        ///
        /// \param handler Event handler that will be asked to consume the event
        /////////////////////////////////////////////////
        inline void play(EventHandler& handler) const { if(m_event != nullptr) m_event->play(handler); }

        /////////////////////////////////////////////////
        /// \brief Does this container really contain an event?
        ///
        /// \return True if an event is present
        /////////////////////////////////////////////////
        inline bool isPresent() const { return m_event != nullptr; }

        /////////////////////////////////////////////////
        /// \brief Check whether an event is present
        ///
        /// Allows to check whether an event is present, without
        /// explicitely calling the \c isPresent method.
        ///
        /// \see isPresent
        /////////////////////////////////////////////////
        inline explicit operator bool() const { return m_event != nullptr; }

    private:

        std::unique_ptr<AbstractEvent> m_event; ///< Contained event
};

}

#endif // IKSDL_EVENT_HPP
