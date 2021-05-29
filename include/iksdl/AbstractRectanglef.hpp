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

#ifndef IKSDL_ABSTRACT_RECTANGLEF_HPP
#define IKSDL_ABSTRACT_RECTANGLEF_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Color.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Gathers the common code related to the drawing of rectangles using \c float coordinates
/////////////////////////////////////////////////
class AbstractRectanglef : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that creates the base of a rectangle to draw
        ///
        /// The given position defines the top-left corner of the rectangle.
        ///
        /// \param rect  Position and size of the rectangle to draw
        /// \param color Drawing color
        /////////////////////////////////////////////////
        IKSDL_EXPORT AbstractRectanglef(const Rectf& rect, Color color);

        /////////////////////////////////////////////////
        /// \brief Constructor that creates the base of a rectangle to draw
        ///
        /// The given position defines the top-left corner of the rectangle.
        ///
        /// \param position Position of the rectangle to draw
        /// \param size     Size of the rectangle to draw
        /// \param color    Drawing color
        /////////////////////////////////////////////////
        IKSDL_EXPORT AbstractRectanglef(const Positionf& position, const Sizef& size, Color color);

        /////////////////////////////////////////////////
        /// \brief Move the rectangle to another position
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
        /// \param factor Scaling factor to apply
        ///
        /// \see setSize
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void scale(float factor) { m_rect.w *= factor; m_rect.h *= factor; }

        /////////////////////////////////////////////////
        /// \brief Get the current position
        ///
        /// \return The current position of the top-left corner
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positionf getPosition() const { return Positionf(m_rect.x, m_rect.y); }

        /////////////////////////////////////////////////
        /// \brief Get the current size
        ///
        /// \return The current size of the rectangle
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Sizef getSize() const { return Sizef(m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Get the current drawing color
        ///
        /// \return The current color used to draw the rectangle
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Color& getColor() const { return m_color; }

        /////////////////////////////////////////////////
        /// \brief Change the position of the rectangle
        ///
        /// The given position defines the top-left corner of the rectangle.
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(const Positionf& position) { m_rect.x = position.getX(); m_rect.y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size of the rectangle
        ///
        /// \param size New size
        ///
        /// \see scale
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setSize(const Sizef& size) { m_rect.w = size.getWidth(); m_rect.h = size.getHeight(); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color
        ///
        /// \param color New color
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setColor(Color color) { m_color = std::move(color); }

    protected:

        SDL_FRect m_rect; ///< Position and size
        Color m_color;   ///< Drawing color
};

}

#endif // IKSDL_ABSTRACT_RECTANGLEF_HPP
