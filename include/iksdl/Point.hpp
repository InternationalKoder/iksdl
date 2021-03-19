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
#include "iksdl/iksdl_export.hpp"

extern "C"
{
struct SDL_Renderer;
}

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
class Point : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor from a position and a color
        ///
        /// \param position Position of the point
        /// \param color    Drawing color
        /////////////////////////////////////////////////
        IKSDL_EXPORT Point(Positioni position, Color color);

        /////////////////////////////////////////////////
        /// \brief Move the point to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Movement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(const Positioni& delta) { m_position = m_position + delta; }

        /////////////////////////////////////////////////
        /// \brief Draw the point
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void draw(SDL_Renderer* const renderer) const;

        /////////////////////////////////////////////////
        /// \brief Get the current position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Positioni& getPosition() const { return m_position; }

        /////////////////////////////////////////////////
        /// \brief Get the drawing color
        ///
        /// \return Drawing color
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Color& getColor() const { return m_color; }

        /////////////////////////////////////////////////
        /// \brief Change the position of the point
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(Positioni position) { m_position = std::move(position); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color
        ///
        /// \param color New color
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setColor(Color color) { m_color = std::move(color); }

    private:

        Positioni m_position; ///< Position of the point
        Color m_color;        ///< Drawing color
};

}

#endif // IKSDL_POINT_HPP
