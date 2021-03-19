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

#ifndef IKSDL_POINT_ARRAY_HPP
#define IKSDL_POINT_ARRAY_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Color.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <vector>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief An array of points that can be drawn
///
/// This is the recommended approach when drawing several points.
/// It is faster that drawing all the points individually,
/// since only one single call is made to draw all the points.
///
/// \warning All the points in the array are drawn with the same color
///
/// \see Point
/////////////////////////////////////////////////
class PointArray : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor to define an empty array
        ///
        /// \param color Drawing color for all the points
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit PointArray(Color color);

        /////////////////////////////////////////////////
        /// \brief Constructor to define a populated array
        ///
        /// \param positions Position of the points to draw
        /// \param color     Drawing color for all the points
        /////////////////////////////////////////////////
        IKSDL_EXPORT PointArray(const std::vector<Positioni>& positions, Color color);

        /////////////////////////////////////////////////
        /// \brief Add a new point at the end of the array
        ///
        /// \param position Position for the new point to draw
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void pushBack(const Positioni& position) { m_points.push_back(positionToSdl(position)); }

        /////////////////////////////////////////////////
        /// \brief Remove the last point from the array
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void popBack() { m_points.pop_back(); }

        /////////////////////////////////////////////////
        /// \brief Remove a point at the given array index
        ///
        /// \param index Array index of the point to remove
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void remove(size_t index) { m_points.erase(m_points.begin() + index); }

        /////////////////////////////////////////////////
        /// \brief Get the position of the point at the given array index
        ///
        /// \param index Array index of the point to get
        ///
        /// \return Position of the point at the given array index
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positioni operator[](size_t index) const { return Positioni(m_points[index].x, m_points[index].y); }

        /////////////////////////////////////////////////
        /// \brief setChange the position of the point at the given array index
        ///
        /// \param index    Array index of the point to change
        /// \param position New position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(size_t index, const Positioni position) { m_points[index] = positionToSdl(position); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color of all the points
        ///
        /// \param color New drawing color
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setColor(Color color) { m_color = std::move(color); }

        /////////////////////////////////////////////////
        /// \brief Draw all the points
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void draw(SDL_Renderer* const renderer) const;

    private:

        /////////////////////////////////////////////////
        /// \brief Transform a \a iksdl::Positioni to a \a SDL_Point
        ///
        /// \param position Position to transform
        ///
        /// \return Same position in the SDL structure
        /////////////////////////////////////////////////
        static inline SDL_Point positionToSdl(const Positioni& position)
        {
            return SDL_Point({ .x = position.getX(), .y = position.getY() });
        }

        std::vector<SDL_Point> m_points; ///< Array of points
        Color m_color;                   ///< Drawing color
};

}

#endif // IKSDL_POINT_ARRAY_HPP
