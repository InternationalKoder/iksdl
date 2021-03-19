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

#ifndef IKSDL_EVENT_SUPPORT_HPP
#define IKSDL_EVENT_SUPPORT_HPP

#include "iksdl/Event.hpp"
#include <algorithm>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Allows to define a set of events to support
///
/// The handling of some types of events may have an impact
/// on performance.
///
/// If performance is an important matter, this structure
/// can be used to enable only some types of events.
///
/// This way, no useless computation is done for events
/// that are not needed.
///
/// \see Window
/////////////////////////////////////////////////
struct EventSupport
{
    /////////////////////////////////////////////////
    /// \brief Constructor defining the supported event types
    ///
    /// All the event types that are not given in this constructor
    /// will not be handled at all.
    ///
    /// \param supportedTypes List of supported event types
    /////////////////////////////////////////////////
    constexpr explicit EventSupport(std::initializer_list<const Event::Type> supportedTypes) :
        windowEventsEnabled(std::find(supportedTypes.begin(), supportedTypes.end(), Event::Type::Window) != supportedTypes.end()),
        keyboardEventsEnabled(std::find(supportedTypes.begin(), supportedTypes.end(), Event::Type::Keyboard) != supportedTypes.end()),
        mouseMotionEventsEnabled(std::find(supportedTypes.begin(), supportedTypes.end(), Event::Type::MouseMotion) != supportedTypes.end()),
        mouseButtonEventsEnabled(std::find(supportedTypes.begin(), supportedTypes.end(), Event::Type::MouseButton) != supportedTypes.end()),
        mouseWheelEventsEnabled(std::find(supportedTypes.begin(), supportedTypes.end(), Event::Type::MouseWheel) != supportedTypes.end())
    {}

    const bool windowEventsEnabled;      ///< Are window events enabled?
    const bool keyboardEventsEnabled;    ///< Are keyboard events enabled?
    const bool mouseMotionEventsEnabled; ///< Are mouse motion events enabled?
    const bool mouseButtonEventsEnabled; ///< Are mouse button events enabled?
    const bool mouseWheelEventsEnabled;  ///< Are mouse wheel events enabled?
};

}

#endif // IKSDL_EVENT_SUPPORT_HPP
