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

#ifndef IKSDL_SPRITE_HPP
#define IKSDL_SPRITE_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/Texture.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief An image that can be drawn
/////////////////////////////////////////////////
class Sprite : public Drawable
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
        /// \param position Position where the sprite will be drawn (top-left corner)
        /////////////////////////////////////////////////
        IKSDL_EXPORT Sprite(const Texture& texture, const Positioni& position);

        /////////////////////////////////////////////////
        /// \brief Constructor that uses only a part of the texture
        ///
        /// The texture must not be destroyed while a sprite is using it.
        ///
        /// \param texture     Texture containing the image data to draw
        /// \param position    Position where the sprite will be drawn (top-left corner)
        /// \param textureRect Part of the texture to draw for this sprite
        /////////////////////////////////////////////////
        IKSDL_EXPORT Sprite(const Texture& texture, const Positioni& position, const Recti& textureRect);

        /////////////////////////////////////////////////
        /// \brief Move the sprite to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Movement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(const Positioni& delta) { m_rect.x += delta.getX(); m_rect.y += delta.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size by using a scale factor
        ///
        /// The scaling is relative to the current size.
        ///
        /// \param delta Scaling factor to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT void scale(const Sizef& delta);

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
        IKSDL_EXPORT virtual void draw(SDL_Renderer* const renderer) const;

        /////////////////////////////////////////////////
        /// \brief Get the position and size
        ///
        /// \return Current position and size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Recti getRect() const { return Recti(m_rect.x, m_rect.y, m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Get the position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positioni getPosition() const { return Positioni(m_rect.x, m_rect.y); }

        /////////////////////////////////////////////////
        /// \brief Get the size
        ///
        /// \return Current size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Sizei getSize() const { return Sizei(m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Change the position of the sprite
        ///
        /// The given position defines the top-left corner of the sprite.
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(const Positioni& position) { m_rect.x = position.getX(); m_rect.y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the part of texture to draw
        ///
        /// \param rect Area from the texture to draw
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setTextureRect(const Recti& rect);

        /////////////////////////////////////////////////
        /// \brief Change the rotation of the sprite
        ///
        /// \param rotation New rotation
        ///
        /// \see rotate
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setRotation(double rotation) { m_rotation = rotation; }

        /////////////////////////////////////////////////
        /// \brief Change the center point that is used to apply rotation
        ///
        /// \param center New center point for rotations
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setCenter(const Positioni& center);

        /////////////////////////////////////////////////
        /// \brief Flip the sprite
        ///
        /// \param flip Type of flip to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setFlip(Flip flip);

        /////////////////////////////////////////////////
        /// \brief Use the full texture to draw the sprite
        /////////////////////////////////////////////////
        IKSDL_EXPORT void resetTextureRect();

        /////////////////////////////////////////////////
        /// \brief Change the rotation center point to default
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void resetCenter() { m_centerPtr = nullptr; };

    private:

        const Texture* const m_texture; ///< Texture holding the image data
        SDL_Rect m_rect;                ///< Position and size of the sprite
        SDL_Rect m_textureRect;         ///< Position and size of the texture to draw
        SDL_Rect* m_textureRectPtr;     ///< Pointer to texture rect, or nullptr to draw full texture

        Sizef m_scale;           ///< Sprite scale
        double m_rotation;       ///< Sprite rotation
        SDL_Point m_center;      ///< Rotation center point
        SDL_Point* m_centerPtr;  ///< Pointer to rotation center point, or nullptr to use default center
        SDL_RendererFlip m_flip; ///< Flip the sprite when drawing
};

}

#endif // IKSDL_SPRITE_HPP
