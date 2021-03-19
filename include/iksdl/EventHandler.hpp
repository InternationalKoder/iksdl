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

#ifndef IKSDL_EVENT_HANDLER_HPP
#define IKSDL_EVENT_HANDLER_HPP

namespace iksdl
{

class QuitEvent;
class WindowEvent;
class KeyboardEvent;
class MouseMotionEvent;
class MouseButtonEvent;
class MouseWheelEvent;

/////////////////////////////////////////////////
/// \brief Abstract handler for events
///
/// This class is the one to use when dealing with events.
///
/// It should be extended by a class that implements all
/// the methods.
/////////////////////////////////////////////////
class EventHandler
{
    public:

        /////////////////////////////////////////////////
        /// \brief Handle a quit event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleQuitEvent(const QuitEvent& event) = 0;

        /////////////////////////////////////////////////
        /// \brief Handle a window event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleWindowEvent(const WindowEvent& event) = 0;

        /////////////////////////////////////////////////
        /// \brief Handle a keyboard event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleKeyboardEvent(const KeyboardEvent& event) = 0;

        /////////////////////////////////////////////////
        /// \brief Handle a mouse motion event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleMouseMotionEvent(const MouseMotionEvent& event) = 0;

        /////////////////////////////////////////////////
        /// \brief Handle a mouse button event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleMouseButtonEvent(const MouseButtonEvent& event) = 0;

        /////////////////////////////////////////////////
        /// \brief Handle a mouse wheel event
        ///
        /// \param event Event to handle
        /////////////////////////////////////////////////
        virtual void handleMouseWheelEvent(const MouseWheelEvent& event) = 0;
};

}

#endif // IKSDL_EVENT_HANDLER_HPP
