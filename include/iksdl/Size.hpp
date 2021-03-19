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

#ifndef IKSDL_SIZE_HPP
#define IKSDL_SIZE_HPP

#include "iksdl/common.hpp"
#include "iksdl/iksdl_export.hpp"

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents a 2D size
///
/// \tparam T Type of the size components
/////////////////////////////////////////////////
template<Arithmetic T>
class Size
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that creates a new size
        ///
        /// \param width  Size on X axis
        /// \param height Size on Y axis
        /////////////////////////////////////////////////
        constexpr Size(T width, T height) :
            m_width(width),
            m_height(height)
        {}

        /////////////////////////////////////////////////
        /// \brief Compute the equality between two sizes
        ///
        /// Sizes are equal when both their width and height are equal.
        ///
        /// \param other Size to compare
        ///
        /// \return True if the sizes are equal
        /////////////////////////////////////////////////
        constexpr bool operator==(const Size<T>& other) const { return m_width == other.m_width && m_height == other.m_height; }

        /////////////////////////////////////////////////
        /// \brief Compute the non-quality between two sizes
        ///
        /// Sizes are different when the widths or the heights (or both)
        /// are different.
        ///
        /// \param other Size to compare
        ///
        /// \return True if the sizes are not equal
        /////////////////////////////////////////////////
        constexpr bool operator!=(const Size<T>& other) const { return m_width != other.m_width || m_height != other.m_height; }

        /////////////////////////////////////////////////
        /// \brief Add each component of two sizes to create a new one
        ///
        /// \param other Size to add
        ///
        /// \return New size that is the sum of the current size and the given one
        /////////////////////////////////////////////////
        constexpr Size<T> operator+(const Size<T>& other) const { return Size<T>(m_width + other.m_width, m_height + other.m_height); }

        /////////////////////////////////////////////////
        /// \brief Subtract each component of the given size to the current one
        ///
        /// \param other Size to subtract
        ///
        /// \return New size that is the subtraction of the current size and the given one
        /////////////////////////////////////////////////
        constexpr Size<T> operator-(const Size<T>& other) const { return Size<T>(m_width - other.m_width, m_height - other.m_height); }

        /////////////////////////////////////////////////
        /// \brief Multiply each component of the two sizes to ceate a new one
        ///
        /// \param other Size to multiply
        ///
        /// \return New size that is the multiplication of the current size and the given one
        /////////////////////////////////////////////////
        constexpr Size<T> operator*(const Size<T>& other) const { return Size<T>(m_width * other.m_width, m_height * other.m_height); }

        /////////////////////////////////////////////////
        /// \brief Divide each component of the given size to the current one
        ///
        /// \param other Size to divide
        ///
        /// \return New size that is the division of the current size and the given one
        /////////////////////////////////////////////////
        constexpr Size<T> operator/(const Size<T>& other) const { return Size<T>(m_width / other.m_width, m_height / other.m_height); }

        /////////////////////////////////////////////////
        /// \brief Get size on X axis
        ///
        /// \return Width
        /////////////////////////////////////////////////
        constexpr T getWidth() const { return m_width; }

        /////////////////////////////////////////////////
        /// \brief Get size on Y axis
        ///
        /// \return Height
        /////////////////////////////////////////////////
        constexpr T getHeight() const { return m_height; }

    private:

        T m_width;  ///< Size on X axis
        T m_height; ///< Size on Y axis
};

using Sizei = Size<int>;          ///< Size using \c int type
using Sizeu = Size<unsigned int>; ///< Size using \c unsigned \c int type
using Sizel = Size<long>;         ///< Size using \c long type
using Sizef = Size<float>;        ///< Size using \c float type
using Sized = Size<double>;       ///< Size using \c double type

}

#endif // IKSDL_SIZE_HPP
