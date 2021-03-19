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

#ifndef IKSDL_RECT_HPP
#define IKSDL_RECT_HPP

#include "iksdl/common.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/iksdl_export.hpp"
#include <algorithm>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents a 2D rect
///
/// A rect is a position and a size.
///
/// \tparam T Type of the position and size components
///
/// \see Position, Size
/////////////////////////////////////////////////
template<Arithmetic T>
class Rect
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor with detailed position and size components
        ///
        /// \param x      Position of the top-left corner on X axis
        /// \param y      Position of the top-left corner on Y axis
        /// \param width  Size on X axis
        /// \param height Size on Y axis
        /////////////////////////////////////////////////
        constexpr Rect(T x, T y, T width, T height) :
            m_position(x, y),
            m_size(width, height)
        {}

        /////////////////////////////////////////////////
        /// \brief Constructor with already existing position and size
        ///
        /// \param position Position of the top-left corner
        /// \param size     Size
        /////////////////////////////////////////////////
        constexpr Rect(Position<T> position, Size<T> size) :
            m_position(std::move(position)),
            m_size(std::move(size))
        {}

        /////////////////////////////////////////////////
        /// \brief Is the given position inside the rect?
        ///
        /// \param position Position to check
        ///
        /// \return True if the position is inside the rect
        /////////////////////////////////////////////////
        constexpr bool contains(const Position<T>& position) const
        {
            return position.getX() >= m_position.getX() && position.getX() <= m_position.getX() + m_size.getWidth() &&
                    position.getY() >= m_position.getY() && position.getY() <= m_position.getY() + m_size.getHeight();
        }

        /////////////////////////////////////////////////
        /// \brief Do the rects intersect?
        ///
        /// \param rect Rect to check
        ///
        /// \return True if the rects intersect
        /////////////////////////////////////////////////
        constexpr bool intersects(const Rect<T>& rect) const
        {
            const T maxLeft = std::max(m_position.getX(), rect.m_position.getX());
            const T minRight = std::min(m_position.getX() + m_size.getWidth(), rect.m_position.getX() + rect.m_size.getWidth());

            if(maxLeft >= minRight)
                return false;

            const T maxTop = std::max(m_position.getY(), rect.m_position.getY());
            const T minBottom = std::min(m_position.getY() + m_size.getHeight(), rect.m_position.getY() + rect.m_size.getHeight());

            return maxTop < minBottom;
        }

        /////////////////////////////////////////////////
        /// \brief Compute the equality between two rects
        ///
        /// Rects are equal when both their positions and size are equal.
        ///
        /// \param other Rect to compare
        ///
        /// \return True if the rects are equal
        /////////////////////////////////////////////////
        constexpr bool operator==(const Rect& other) const { return m_position == other.m_position && m_size == other.m_size; }

        /////////////////////////////////////////////////
        /// \brief Compute the non-equality between two rects
        ///
        /// Rects are different when the positions or the sizes (or both)
        /// are different.
        ///
        /// \param other Rect to compare
        ///
        /// \return True if the rects are not equal
        /////////////////////////////////////////////////
        constexpr bool operator!=(const Rect& other) const { return m_position != other.m_position || m_size != other.m_size; }

        /////////////////////////////////////////////////
        /// \brief Get the full position
        ///
        /// \return Position on both X and Y axes
        /////////////////////////////////////////////////
        constexpr const Position<T>& getPosition() const { return m_position; }

        /////////////////////////////////////////////////
        /// \brief Get the full size
        ///
        /// \return Size on both X and Y axes
        /////////////////////////////////////////////////
        constexpr const Size<T>& getSize() const { return m_size; }

        /////////////////////////////////////////////////
        /// \brief Get the position on X axis
        ///
        /// \return Position on X axis
        /////////////////////////////////////////////////
        constexpr T getX() const { return m_position.getX(); }

        /////////////////////////////////////////////////
        /// \brief Get the position on Y axis
        ///
        /// \return Position on Y axis
        /////////////////////////////////////////////////
        constexpr T getY() const { return m_position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Get the width
        ///
        /// \return Size on X axis
        /////////////////////////////////////////////////
        constexpr T getWidth() const { return m_size.getWidth(); }

        /////////////////////////////////////////////////
        /// \brief Get the height
        ///
        /// \return Size on Y axis
        /////////////////////////////////////////////////
        constexpr T getHeight() const { return m_size.getHeight(); }

        /////////////////////////////////////////////////
        /// \brief Create a new rect by changing the position only
        ///
        /// The size is the same as the existing rect.
        ///
        /// \param position New position
        ///
        /// \return New rect with a new position
        /////////////////////////////////////////////////
        constexpr Rect<T> withPosition(Position<T> position) { return Rect<T>(std::move(position), std::move(m_size)); }

        /////////////////////////////////////////////////
        /// \brief Create a new rect by changing the size only
        ///
        /// The position is the same as the existing rect.
        ///
        /// \param size New size
        ///
        /// \return New rect with a new size
        /////////////////////////////////////////////////
        constexpr Rect<T> withSize(Size<T> size) { return Rect<T>(std::move(m_position), std::move(size)); }

    private:

        Position<T> m_position; ///< Full position
        Size<T> m_size;         ///< Full size
};

using Recti = Rect<int>;          ///< Rect using \c int type
using Rectu = Rect<unsigned int>; ///< Rect using \c unsigned \c int type
using Rectl = Rect<long>;         ///< Rect using \c long type
using Rectf = Rect<float>;        ///< Rect using \c float type
using Rectd = Rect<double>;       ///< Rect using \c double type

}

#endif // IKSDL_RECT_HPP
