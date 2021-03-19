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

#ifndef IKSDL_KEYBOARD_EVENT_HPP
#define IKSDL_KEYBOARD_EVENT_HPP

#include "iksdl/AbstractEvent.hpp"
#include "iksdl/EventHandler.hpp"
#include "iksdl/Keyboard.hpp"
#include "iksdl/iksdl_export.hpp"
#include <vector>

extern "C"
{
struct SDL_KeyboardEvent;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents an event related to the keyboard
/////////////////////////////////////////////////
class KeyboardEvent : public AbstractEvent
{
    public:

        /////////////////////////////////////////////////
        /// \brief Keyboard event type
        /////////////////////////////////////////////////
        enum class Type { KeyDown, KeyUp };

        /////////////////////////////////////////////////
        /// \brief Key state
        /////////////////////////////////////////////////
        enum class KeyState { Pressed, Released };

        /////////////////////////////////////////////////
        /// \brief Key modifier
        /////////////////////////////////////////////////
        enum class Modifier { LeftShift, RightShift, AnyShift,
                              LeftCtrl, RightCtrl, AnyCtrl,
                              LeftAlt, RightAlt, AnyAlt,
                              NumLock, CapsLock, AltGr };

        /////////////////////////////////////////////////
        /// \brief Constructor from SDL keyboard event
        ///
        /// \param sdlEvent SDL keyboard event
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit KeyboardEvent(const SDL_KeyboardEvent& sdlEvent);

        /////////////////////////////////////////////////
        /// \brief Make the given handler execute the action related to the keyboard event
        ///
        /// \param handler Event handler that will be asked to consume the keyboard event
        /////////////////////////////////////////////////
        inline virtual void play(EventHandler& handler) const { handler.handleKeyboardEvent(*this); }

        /////////////////////////////////////////////////
        /// \brief Get the keybaord event type
        ///
        /// \return Keyboard event type
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Type getType() const { return m_type; }

        /////////////////////////////////////////////////
        /// \brief Get the key state
        ///
        /// \return Key state
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline KeyState getKeyState() const { return m_keyState; }

        /////////////////////////////////////////////////
        /// \brief Get the key that the event is about
        ///
        /// \return The key
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Keyboard::Key getKey() const { return m_key; }

        /////////////////////////////////////////////////
        /// \brief Is the given modifier active in the event?
        ///
        /// \param modifier Modifier to check
        ///
        /// \return True if the modifier is active
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline bool hasModifier(Modifier modifier) const { return std::find(m_modifiers.begin(), m_modifiers.end(), modifier) != m_modifiers.end(); }

        /////////////////////////////////////////////////
        /// \brief Is the event repeating?
        ///
        /// \return True if the event is repeating
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline bool isRepeat() const { return m_repeat; }

    private:

        Type m_type;                       ///< Keyboard event type
        KeyState m_keyState;               ///< State of the key
        Keyboard::Key m_key;               ///< Key that the event is about
        std::vector<Modifier> m_modifiers; ///< List of active modifiers
        bool m_repeat;                     ///< Is the event repeating?
};

}

#endif // IKSDL_KEYBOARD_EVENT_HPP
