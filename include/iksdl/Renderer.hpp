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

#ifndef IKSDL_RENDERER_HPP
#define IKSDL_RENDERER_HPP

#include "iksdl/Color.hpp"
#include "iksdl/Drawable.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/RendererOptions.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <string>

namespace iksdl
{

class Window;
class Texture;
class Text;

/////////////////////////////////////////////////
/// \brief Component that is able to draw entities using hardware acceleation
/////////////////////////////////////////////////
class Renderer
{
    friend class Texture;
    friend class Text;

    public:

        static constexpr RendererOptions DEFAULT_OPTIONS = RendererOptions().accelerated(); ///< Default renderer options

        Renderer(const Renderer&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Renderer to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Renderer(Renderer&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Renderer();

        Renderer& operator=(const Renderer&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Renderer to be moved
        ///
        /// \return Moved renderer
        /////////////////////////////////////////////////
        IKSDL_EXPORT Renderer& operator=(Renderer&& other);

        /////////////////////////////////////////////////
        /// \brief Clear the rendering area
        ///
        /// \param clearColor Color that will fill the cleaned area
        /////////////////////////////////////////////////
        IKSDL_EXPORT void clear(const Color& clearColor = Color(0, 0, 0)) const;

        /////////////////////////////////////////////////
        /// \brief Render the drawn entities
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void display() const { SDL_RenderPresent(m_renderer); }

        /////////////////////////////////////////////////
        /// \brief Draw an entity
        ///
        /// \param drawable Entity to draw
        /////////////////////////////////////////////////
        inline void draw(const Drawable& drawable) { drawable.draw(m_renderer); }

        /////////////////////////////////////////////////
        /// \brief Change the viewport
        ///
        /// \param viewport New viewport
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setViewport(const Recti& viewport);

        /////////////////////////////////////////////////
        /// \brief Change to the default viewport
        /////////////////////////////////////////////////
        IKSDL_EXPORT void resetViewport() { SDL_RenderSetViewport(m_renderer, nullptr); }

    protected:

        /////////////////////////////////////////////////
        /// \brief Constructor that makes the renderer work in a window
        ///
        /// \param sdlWindow Window as SDL struct
        /// \param options   Rendering options
        /////////////////////////////////////////////////
        explicit Renderer(SDL_Window& sdlWindow, const RendererOptions& options = DEFAULT_OPTIONS);

    private:

        static constexpr std::string_view CREATE_RENDERER_ERROR = "Could not create renderer.\nCause: ";

        SDL_Renderer* m_renderer; ///< SDL renderer
        SDL_Rect m_viewport;      ///< Current viewport
};

}

#endif // IKSDL_RENDERER_HPP
