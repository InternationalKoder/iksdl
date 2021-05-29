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

#ifndef IKSDL_LINE_HPP
#define IKSDL_LINE_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Color.hpp"

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief A line that can be drawn
///
/// \note When handling several connected lines with same color,
/// prefer \c LineArray for better performance
///
/// \see LineArray
/////////////////////////////////////////////////
template<DrawablePosition T>
class BaseLine : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor from two positions and a color
        ///
        /// \param position1 Position of first extremity
        /// \param position2 Position of second extremity
        /// \param color     Drawing color
        /////////////////////////////////////////////////
        BaseLine(T position1, T position2, Color color) :
            m_position1(std::move(position1)),
            m_position2(std::move(position2)),
            m_color(std::move(color))
        {}

        /////////////////////////////////////////////////
        /// \brief Move the line to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Movement to apply
        ///
        /// \see setPosition1, setPosition2
        /////////////////////////////////////////////////
        inline void move(const T& delta) { m_position1 = m_position1 + delta; m_position2 = m_position2 + delta; }

        /////////////////////////////////////////////////
        /// \brief Draw the line
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        virtual void draw(SDL_Renderer* const renderer) const
        {
            SDL_SetRenderDrawColor(renderer, m_color.getRed(), m_color.getGreen(), m_color.getBlue(), m_color.getAlpha());

            if constexpr(std::is_same_v<T, Positioni>)
                SDL_RenderDrawLine(renderer, m_position1.getX(), m_position1.getY(), m_position2.getX(), m_position2.getY());
            else
                SDL_RenderDrawLineF(renderer, m_position1.getX(), m_position1.getY(), m_position2.getX(), m_position2.getY());
        }

        /////////////////////////////////////////////////
        /// \brief Get the position of first extremity
        ///
        /// \return Position of first extremity
        /////////////////////////////////////////////////
        inline const T& getPosition1() const { return m_position1; }

        /////////////////////////////////////////////////
        /// \brief Get the position of second extremity
        ///
        /// \return Position of second extremity
        /////////////////////////////////////////////////
        inline const T& getPosition2() const { return m_position2; }

        /////////////////////////////////////////////////
        /// \brief Get the drawing color
        ///
        /// \return Drawing color
        /////////////////////////////////////////////////
        inline const Color& getColor() const { return m_color; }

        /////////////////////////////////////////////////
        /// \brief Change the position of first extremity
        ///
        /// \param position New position
        ///
        /// \see move, setPosition2
        /////////////////////////////////////////////////
        inline void setPosition1(T position) { m_position1 = std::move(position); }

        /////////////////////////////////////////////////
        /// \brief Change the position of second extremity
        ///
        /// \param position New position
        ///
        /// \see move, setPosition1
        /////////////////////////////////////////////////
        inline void setPosition2(T position) { m_position2 = std::move(position); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color
        ///
        /// \param color New color
        /////////////////////////////////////////////////
        inline void setColor(Color color) { m_color = std::move(color); }

    private:

        T m_position1; ///< Position of first extremity
        T m_position2; ///< Position of second extremity
        Color m_color; ///< Drawing color
};

using Line  = BaseLine<Positioni>; ///< Line using \c int coordinates
using Linef = BaseLine<Positionf>; ///< Line using \c float coordinates

}

#endif // IKSDL_LINE_HPP
