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

#ifndef IKSDL_POINT_HPP
#define IKSDL_POINT_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Color.hpp"
#include <SDL.h>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief A point that can be drawn
///
/// \note When handling several points with same color,
/// prefer \c PointArray for better performance
///
/// \see PointArray
/////////////////////////////////////////////////
template<DrawablePosition T>
class BasePoint : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor from a position and a color
        ///
        /// \param position Position of the point
        /// \param color    Drawing color
        /////////////////////////////////////////////////
        BasePoint(T position, Color color) :
            m_position(std::move(position)),
            m_color(std::move(color))
        {}

        /////////////////////////////////////////////////
        /// \brief Move the point to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Movement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        inline void move(const T& delta) { m_position = m_position + delta; }

        /////////////////////////////////////////////////
        /// \brief Draw the point
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        virtual void draw(SDL_Renderer* const renderer) const
        {
            SDL_SetRenderDrawColor(renderer, m_color.getRed(), m_color.getGreen(), m_color.getBlue(), m_color.getAlpha());

            if constexpr(std::is_same_v<T, Positioni>)
                SDL_RenderDrawPoint(renderer, m_position.getX(), m_position.getY());
            else
                SDL_RenderDrawPointF(renderer, m_position.getX(), m_position.getY());
        }

        /////////////////////////////////////////////////
        /// \brief Get the current position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        inline const T& getPosition() const { return m_position; }

        /////////////////////////////////////////////////
        /// \brief Get the drawing color
        ///
        /// \return Drawing color
        /////////////////////////////////////////////////
        inline const Color& getColor() const { return m_color; }

        /////////////////////////////////////////////////
        /// \brief Change the position of the point
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        inline void setPosition(T position) { m_position = std::move(position); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color
        ///
        /// \param color New color
        /////////////////////////////////////////////////
        inline void setColor(Color color) { m_color = std::move(color); }

    private:

        T m_position;  ///< Position of the point
        Color m_color; ///< Drawing color
};

using Point  = BasePoint<Positioni>; ///< Point using \c int coordinates
using Pointf = BasePoint<Positionf>; ///< Point using \c float coordinates

}

#endif // IKSDL_POINT_HPP
