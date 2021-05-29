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

#ifndef IKSDL_SPRITEF_HPP
#define IKSDL_SPRITEF_HPP

#include "iksdl/BaseSprite.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>

namespace iksdl
{

class Texture;

/////////////////////////////////////////////////
/// \brief An image that can be drawn using \c float coordinates
/////////////////////////////////////////////////
class Spritef : public BaseSprite
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that sets the sprite at the given position
        ///
        /// The texture must not be destroyed while a sprite is using it.
        ///
        /// \param texture  Texture containing the image data to draw
        /// \param position Position where the sprite will be drawn (top-left corner)
        /////////////////////////////////////////////////
        IKSDL_EXPORT Spritef(const Texture& texture, const Positionf& position);

        /////////////////////////////////////////////////
        /// \brief Constructor that uses only a part of the texture
        ///
        /// The texture must not be destroyed while a sprite is using it.
        ///
        /// \param texture     Texture containing the image data to draw
        /// \param position    Position where the sprite will be drawn (top-left corner)
        /// \param textureRect Part of the texture to draw for this sprite
        /////////////////////////////////////////////////
        IKSDL_EXPORT Spritef(const Texture& texture, const Positionf& position, const Recti& textureRect);

        /////////////////////////////////////////////////
        /// \brief Move the sprite to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Movement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(const Positionf& delta) { m_rect.x += delta.getX(); m_rect.y += delta.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size by using a scale factor
        ///
        /// The scaling is relative to the current size.
        ///
        /// \param delta Scaling factor to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void scale(const Sizef& delta);

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
        IKSDL_EXPORT inline Rectf getRect() const { return Rectf(m_rect.x, m_rect.y, m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Get the position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positionf getPosition() const { return Positionf(m_rect.x, m_rect.y); }

        /////////////////////////////////////////////////
        /// \brief Get the size
        ///
        /// \return Current size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Sizef getSize() const { return Sizef(m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Change the position of the sprite
        ///
        /// The given position defines the top-left corner of the sprite.
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(const Positionf& position) { m_rect.x = position.getX(); m_rect.y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the part of texture to draw
        ///
        /// \param rect Area from the texture to draw
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void setTextureRect(const Recti& rect);

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
        IKSDL_EXPORT void setCenter(const Positionf& center);

        /////////////////////////////////////////////////
        /// \brief Use the full texture to draw the sprite
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void resetTextureRect();

        /////////////////////////////////////////////////
        /// \brief Change the rotation center point to default
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void resetCenter() { m_centerPtr = nullptr; };

    private:

        SDL_FRect m_rect; ///< Position and size of the sprite

        SDL_FPoint m_center;     ///< Rotation center point
        SDL_FPoint* m_centerPtr; ///< Pointer to rotation center point, or nullptr to use default center
};

}

#endif // IKSDL_SPRITEF_HPP
