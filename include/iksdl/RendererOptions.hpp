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

#ifndef IKSDL_RENDERER_OPTIONS
#define IKSDL_RENDERER_OPTIONS

#include "iksdl_export.hpp"
#include <SDL.h>
#include <cstdint>

namespace iksdl
{

class Renderer;

/////////////////////////////////////////////////
/// \brief Allows to set options for graphics rendering
///
/// This class works with builder methods, it is possible
/// to chain the calls to build the full set of options
/////////////////////////////////////////////////
class RendererOptions
{
    friend class Renderer;

    public:

        /////////////////////////////////////////////////
        /// \brief Default constructor with no option activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr RendererOptions() : m_sdlFlags(0) {}

        /////////////////////////////////////////////////
        /// \brief Activate software rendering
        ///
        /// \return Options with software rendering activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr RendererOptions& software() { m_sdlFlags |= SDL_RENDERER_SOFTWARE; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate accelerated rendering
        ///
        /// \return Options with accelerated rendering activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr RendererOptions& accelerated() { m_sdlFlags |= SDL_RENDERER_ACCELERATED; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate VSync: synchronize renderer with refresh rate
        ///
        /// \return Options with VSync activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr RendererOptions& vsync() { m_sdlFlags |= SDL_RENDERER_PRESENTVSYNC; return *this; }

        /////////////////////////////////////////////////
        /// \brief Activate render to textures
        ///
        /// \return Options with texture rendering activated
        /////////////////////////////////////////////////
        IKSDL_EXPORT constexpr RendererOptions& targetTexture() { m_sdlFlags |= SDL_RENDERER_TARGETTEXTURE; return *this; }

    private:

        uint32_t m_sdlFlags; ///< SDL option flags
};

}

#endif // IKSDL_RENDERER_OPTIONS
