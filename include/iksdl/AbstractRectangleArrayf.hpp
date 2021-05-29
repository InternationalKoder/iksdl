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

#ifndef IKSDL_ABSTRACT_RECTANGLE_ARRAYF_HPP
#define IKSDL_ABSTRACT_RECTANGLE_ARRAYF_HPP

#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Color.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <vector>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Gathers the common code related to the drawing of rectangle arrays using \c float coordinates
///
/// This is the recommended approach when drawing several rectangles.
/// It is faster than drawing all the rectangles individually,
/// since only one single call is made to draw all the rectangles.
///
/// \warning All the rectangles in the array are drawn with the same color
/////////////////////////////////////////////////
class AbstractRectangleArrayf : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor to define an empty array
        ///
        /// \param color Drawing color for all the rectangles
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit AbstractRectangleArrayf(Color color);

        /////////////////////////////////////////////////
        /// \brief Constructor to define a populated array
        ///
        /// \param rects Rectangles to draw
        /// \param color Drawing color for all the rectangles
        /////////////////////////////////////////////////
        IKSDL_EXPORT AbstractRectangleArrayf(const std::vector<Rectf>& rects, Color color);

        /////////////////////////////////////////////////
        /// \brief Add a new rectangle at the end of the array
        ///
        /// \param rect New rectangle to draw
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void pushBack(const Rectf& rect) { m_rects.push_back(rectToSdl(rect)); }

        /////////////////////////////////////////////////
        /// \brief Remove the last rectangle from the array
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void popBack() { m_rects.pop_back(); }

        /////////////////////////////////////////////////
        /// \brief Remove rectangle at the given position
        ///
        /// \param index Array index of the rectangle to remove
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void remove(size_t index) { m_rects.erase(m_rects.begin() + index); }

        /////////////////////////////////////////////////
        /// \brief Get the rectangle at the given array index
        ///
        /// \param index Array index of the rectangle to get
        ///
        /// \return Position and size of the rectangle at the given array index
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Rectf operator[](size_t index) const { return Rectf(m_rects[index].x, m_rects[index].y, m_rects[index].w, m_rects[index].h); }

        /////////////////////////////////////////////////
        /// \brief Move a rectangle to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param index Array index of the rectangle to move
        /// \param delta Movement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(size_t index, const Positionf& delta) { m_rects[index].x += delta.getX(); m_rects[index].y += delta.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size of a rectangle by using a scale factor
        ///
        /// The scaling is relative to the current size.
        ///
        /// \param index  Array index of the rectangle to scale
        /// \param factor Scaling factor to apply
        ///
        /// \see setSize
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void scale(size_t index, float factor) { m_rects[index].w *= factor; m_rects[index].h *= factor; }

        /////////////////////////////////////////////////
        /// \brief Get the current drawing color
        ///
        /// \return The current color used to draw all the rectangles
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline const Color& getColor() const { return m_color; }

        /////////////////////////////////////////////////
        /// \brief Change the position of a rectangle
        ///
        /// \param index    Array index of the rectangle
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(size_t index, const Positionf& position) { m_rects[index].x = position.getX(); m_rects[index].y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size of a rectangle
        ///
        /// \param index Array index of the rectangle
        /// \param size  New size
        ///
        /// \see scale
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setSize(size_t index, const Sizef& size) { m_rects[index].w = size.getWidth(); m_rects[index].h = size.getHeight(); }

        /////////////////////////////////////////////////
        /// \brief Change the drawing color
        ///
        /// \param color New color
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setColor(Color color) { m_color = std::move(color); }

    protected:

        std::vector<SDL_FRect> m_rects; ///< Array of the rectangles
        Color m_color;                  ///< Drawing color

    private:

        /////////////////////////////////////////////////
        /// \brief Transform a \a iksdl::Rectf to a \a SDL_FRect
        ///
        /// \param rect Rect to transform
        ///
        /// \return Same rect in the SDL structure
        /////////////////////////////////////////////////
        static inline SDL_FRect rectToSdl(const Rectf& rect)
        {
            return SDL_FRect({ .x = rect.getX(), .y = rect.getY(), .w = rect.getWidth(), .h = rect.getHeight() });
        }
};

}

#endif // IKSDL_ABSTRACT_RECTANGLE_ARRAYF_HPP
