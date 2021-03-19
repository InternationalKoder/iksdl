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

#ifndef IKSDL_WINDOW_OPTIONS
#define IKSDL_WINDOW_OPTIONS

#include "iksdl_export.hpp"
#include <SDL.h>
#include <cstdint>

namespace iksdl
{

class Window;

/////////////////////////////////////////////////
/// \brief Allows to set options for window
///
/// This class works with builder methods, it is possible
/// to chain the calls to build the full set of options
/////////////////////////////////////////////////
class WindowOptions
{
    friend class Window;

    public:

        /////////////////////////////////////////////////
        /// \brief Default constructor with no option activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions() : m_sdlFlags(0) {}

        /////////////////////////////////////////////////
        /// \brief Activate full screen mode
        ///
        /// \return Options with full screen mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& fullScreen() { m_sdlFlags |= SDL_WINDOW_FULLSCREEN; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate OpenGL rendering
        ///
        /// \return Options with OpenGL rendering activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& opengl() { m_sdlFlags |= SDL_WINDOW_OPENGL; return *this; }

        /////////////////////////////////////////////////
        /// \brief Show the window
        ///
        /// \return Options with shown window
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& shown() { m_sdlFlags |= SDL_WINDOW_SHOWN; return *this; }

        /////////////////////////////////////////////////
        /// \brief Hide the window
        ///
        /// \return Options with hidden window
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& hidden() { m_sdlFlags |= SDL_WINDOW_HIDDEN; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate borderless window mode
        ///
        /// \return Options with borderless mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& borderless() { m_sdlFlags |= SDL_WINDOW_BORDERLESS; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate resizable window mode
        ///
        /// \return Options with resizable window mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& resizable() { m_sdlFlags |= SDL_WINDOW_RESIZABLE; return *this; }

        /////////////////////////////////////////////////
        /// \brief Minimize the window
        ///
        /// \return Options with minimized window
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& minimized() { m_sdlFlags |= SDL_WINDOW_MINIMIZED; return *this; }

        /////////////////////////////////////////////////
        /// \brief Maximize the window
        ///
        /// \return Options with maximized window
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& maximized() { m_sdlFlags |= SDL_WINDOW_MAXIMIZED; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate input grab focus
        ///
        /// \return Options with input grab focus activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& inputGrabbed() { m_sdlFlags |= SDL_WINDOW_INPUT_GRABBED; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate input focus
        ///
        /// \return Options with input focus activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& inputFocus() { m_sdlFlags |= SDL_WINDOW_INPUT_FOCUS; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate mouse focus
        ///
        /// \return Options with mouse focus activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& mouseFocus() { m_sdlFlags |= SDL_WINDOW_MOUSE_FOCUS; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate full screen mode for desktop
        ///
        /// \return Options with full screen mode for desktop activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& fullscreenDesktop() { m_sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; return *this; }

        /////////////////////////////////////////////////
        /// \brief Window not created by SDL
        ///
        /// \return Options with window not created by SDL
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& foreign() { m_sdlFlags |= SDL_WINDOW_FOREIGN; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate high DPI mode if available
        ///
        /// \return Options with high DPI mode activated if available
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& allowHighDpi() { m_sdlFlags |= SDL_WINDOW_ALLOW_HIGHDPI; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate mouse capture
        ///
        /// \return Options with mouse capture activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& mouseCapture() { m_sdlFlags |= SDL_WINDOW_MOUSE_CAPTURE; return *this; }

        /////////////////////////////////////////////////
        /// \brief Window always on top
        ///
        /// \return Options with window always on top
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& alwaysOnTop() { m_sdlFlags |= SDL_WINDOW_ALWAYS_ON_TOP; return *this; }

        /////////////////////////////////////////////////
        /// \brief Window not added to task bar
        ///
        /// \return Options with window not added to task bar
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& skipTaskBar() { m_sdlFlags |= SDL_WINDOW_SKIP_TASKBAR; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate utility window mode
        ///
        /// \return Options with utility window mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& utility() { m_sdlFlags |= SDL_WINDOW_UTILITY; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate tooltip window mode
        ///
        /// \return Options with tooltip window mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& tooltip() { m_sdlFlags |= SDL_WINDOW_TOOLTIP; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate popup menu window mode
        ///
        /// \return Options with popup menu window mode activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& popupMenu() { m_sdlFlags |= SDL_WINDOW_POPUP_MENU; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate Vulkan support
        ///
        /// \return Options with Vulkan support activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& vulkan() { m_sdlFlags |= SDL_WINDOW_VULKAN; return *this; }

#if SDL_VERSION_ATLEAST(2, 0, 14)
        /////////////////////////////////////////////////
        /// \brief Activate Metal support
        ///
        /// \warning Available only with SDL 2.0.14 or higher
        ///
        /// \return Options with Metal support activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr WindowOptions& metal() { m_sdlFlags |= SDL_WINDOW_METAL; return *this; }
#endif

    private:

        uint32_t m_sdlFlags; ///< SDL option flags
};

}

#endif // IKSDL_WINDOW_OPTIONS
