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

#ifndef IKSDL_BASE_SPRITE_HPP
#define IKSDL_BASE_SPRITE_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>

namespace iksdl
{

class Texture;

/////////////////////////////////////////////////
/// \brief Abstract base class for a sprite
/////////////////////////////////////////////////
class BaseSprite : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Flipping modes for a sprite
        /////////////////////////////////////////////////
        enum class Flip { None, Horizontal, Vertical, Both };

        /////////////////////////////////////////////////
        /// \brief Constructor that sets the sprite at the given position
        ///
        /// The texture must not be destroyed while a sprite is using it.
        ///
        /// \param texture  Texture containing the image data to draw
        /////////////////////////////////////////////////
        IKSDL_EXPORT BaseSprite(const Texture& texture);

        /////////////////////////////////////////////////
        /// \brief Change the size by using a scale factor
        ///
        /// The scaling is relative to the current size.
        ///
        /// \param delta Scaling factor to apply
        /////////////////////////////////////////////////
        virtual void scale(const Sizef& delta) = 0;

        /////////////////////////////////////////////////
        /// \brief Rotate the sprite
        ///
        /// The rotation is relative to the current orientation.
        ///
        /// \param delta Angle difference to apply
        ///
        /// \see setRotation
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void rotate(double delta) { m_rotation += delta; }

        /////////////////////////////////////////////////
        /// \brief Draw the sprite
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        virtual void draw(SDL_Renderer* const renderer) const = 0;

        /////////////////////////////////////////////////
        /// \brief Change the part of texture to draw
        ///
        /// \param rect Area from the texture to draw
        /////////////////////////////////////////////////
        virtual void setTextureRect(const Recti& rect) = 0;

        /////////////////////////////////////////////////
        /// \brief Change the rotation of the sprite
        ///
        /// \param rotation New rotation
        ///
        /// \see rotate
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setRotation(double rotation) { m_rotation = rotation; }

        /////////////////////////////////////////////////
        /// \brief Flip the sprite
        ///
        /// \param flip Type of flip to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setFlip(Flip flip);

        /////////////////////////////////////////////////
        /// \brief Use the full texture to draw the sprite
        /////////////////////////////////////////////////
        virtual void resetTextureRect() = 0;

    protected:

        const Texture* const m_texture; ///< Texture holding the image data
        SDL_Rect m_textureRect;         ///< Position and size of the texture to draw
        SDL_Rect* m_textureRectPtr;     ///< Pointer to texture rect, or nullptr to draw full texture

        Sizef m_scale;           ///< Sprite scale
        double m_rotation;       ///< Sprite rotation
        SDL_RendererFlip m_flip; ///< Flip the sprite when drawing
};

}

#endif // IKSDL_BASE_SPRITE_HPP
