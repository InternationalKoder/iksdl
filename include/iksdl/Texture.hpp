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

#ifndef IKSDL_TEXTURE_HPP
#define IKSDL_TEXTURE_HPP

#include "iksdl/Color.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <string>

namespace iksdl
{

class Renderer;

/////////////////////////////////////////////////
/// \brief Holds image data
///
/// A texture should not be destroyed while other objects
/// are holding a reference to it.
/////////////////////////////////////////////////
class Texture
{
    friend class Sprite;
    friend class Spritef;

    public:

        /////////////////////////////////////////////////
        /// \brief Constructor loading the texture from a file
        ///
        /// This constructor will throw \a SdlException if the
        /// texture could not be loaded.
        ///
        /// Supported formats: PNG, JPG, TIF, WEBP, BMP
        ///
        /// \param renderer Renderer that will draw the texture
        /// \param filePath Path to image file
        /////////////////////////////////////////////////
        IKSDL_EXPORT Texture(const Renderer& renderer, const std::string& filePath);

        /////////////////////////////////////////////////
        /// \brief Constructor loading the texture from a file and interpret a specific color as transparent
        ///
        /// This constructor will throw \a InvalidParameterException if the
        /// image could not be loaded.
        ///
        /// It may also throw \a SdlException if the texture could
        /// not be created from the loaded image.
        ///
        /// Supported formats: PNG, JPG, TIF, WEBP, BMP
        ///
        /// \param renderer Renderer that will draw the texture
        /// \param filePath Path to image file
        /// \param colorKey Color that will be drawn as transparent
        /////////////////////////////////////////////////
        IKSDL_EXPORT Texture(const Renderer& renderer, const std::string& filePath, const Color& colorKey);

        Texture(const Texture&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Texture to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Texture(Texture&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Texture();

        Texture& operator=(const Texture&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Texture to be moved
        ///
        /// \return Moved texture
        /////////////////////////////////////////////////
        IKSDL_EXPORT Texture& operator=(Texture&& other);

        /////////////////////////////////////////////////
        /// \brief Modulate the texture colors with another color
        ///
        /// \param color Color the texture will be modulated with
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setColorModulation(const Color& color) const
        {
            SDL_SetTextureColorMod(m_texture, color.getRed(), color.getGreen(), color.getBlue());
        }

        /////////////////////////////////////////////////
        /// \brief Blend the texture with transparency
        ///
        /// \param alpha Transparency level
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setAlphaBlending(uint8_t alpha) const
        {
            SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(m_texture, alpha);
        }

        /////////////////////////////////////////////////
        /// \brief Get the size of the texture
        ///
        /// \return Size of texture
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Sizei& getSize() const { return m_size; }

    private:

        SDL_Texture* m_texture; ///< SDL texture
        Sizei m_size;           ///< Texture size
};

}

#endif // IKSDL_TEXTURE_HPP
