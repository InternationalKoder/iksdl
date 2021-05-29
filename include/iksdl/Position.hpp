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

#ifndef IKSDL_POSITION_HPP
#define IKSDL_POSITION_HPP

#include "iksdl/common.hpp"

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Represents a 2D position
///
/// \tparam T Type of the position components
/////////////////////////////////////////////////
template<Arithmetic T>
class Position
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that creates a new position from its components
        ///
        /// \param x Position on X axis
        /// \param y Position on Y axis
        /////////////////////////////////////////////////
        constexpr Position(T x, T y) :
            m_x(x),
            m_y(y)
        {}

        /////////////////////////////////////////////////
        /// \brief Compute the equality between two positions
        ///
        /// Positions are equal when both X and Y coordinates are equal.
        ///
        /// \param other Position to compare
        ///
        /// \return True if the positions are equal
        /////////////////////////////////////////////////
        constexpr bool operator==(const Position<T>& other) const { return m_x == other.m_x && m_y == other.m_y; }

        /////////////////////////////////////////////////
        /// \brief Compute the non-equality between two positions
        ///
        /// Positions are different when at least one coordinate
        /// has a different value in both positions.
        ///
        /// \param other Position to compare
        ///
        /// \return True if the positions are not equal
        /////////////////////////////////////////////////
        constexpr bool operator!=(const Position<T>& other) const { return m_x != other.m_x || m_y != other.m_y; }

        /////////////////////////////////////////////////
        /// \brief Add each coordinate of two positions to create a new one
        ///
        /// \param other Position to add
        ///
        /// \return New position that is the sum of the current position and the given one
        /////////////////////////////////////////////////
        constexpr Position<T> operator+(const Position<T>& other) const { return Position<T>(m_x + other.m_x, m_y + other.m_y); }

        /////////////////////////////////////////////////
        /// \brief Subtract each coordinate of the given position to the current one
        ///
        /// \param other Position to subtract
        ///
        /// \return New position that is the subtraction of the current position and the given one
        /////////////////////////////////////////////////
        constexpr Position<T> operator-(const Position<T>& other) const { return Position<T>(m_x - other.m_x, m_y - other.m_y); }

        /////////////////////////////////////////////////
        /// \brief Multiply each coordinate of the two positions to create a new one
        ///
        /// \param other Position to multiply
        ///
        /// \return New position that is the multiplication of the current position and the given one
        /////////////////////////////////////////////////
        constexpr Position<T> operator*(const Position<T>& other) const { return Position<T>(m_x * other.m_x, m_y * other.m_y); }

        /////////////////////////////////////////////////
        /// \brief Divide each coordinate of the given position to the current one
        ///
        /// \param other Position to divide
        ///
        /// \return New position that is the divison of the current position and the given one
        /////////////////////////////////////////////////
        constexpr Position<T> operator/(const Position<T>& other) const { return Position<T>(m_x / other.m_x, m_y / other.m_y); }

        /////////////////////////////////////////////////
        /// \brief Get X coordinate
        ///
        /// \return X coordinate
        /////////////////////////////////////////////////
        constexpr T getX() const { return m_x; }

        /////////////////////////////////////////////////
        /// \brief Get Y coordinate
        ///
        /// \return Y coordinate
        /////////////////////////////////////////////////
        constexpr T getY() const { return m_y; }

    private:

        T m_x; ///< X coordinate
        T m_y; ///< Y coordinate
};

using Positioni = Position<int>;          ///< Position using \c int type
using Positionu = Position<unsigned int>; ///< Position using \c unsigned \c int type
using Positionl = Position<long>;         ///< Position using \c long type
using Positionf = Position<float>;        ///< Position using \c float type
using Positiond = Position<double>;       ///< Position using \c double type

template<typename T>
concept DrawablePosition = std::is_same_v<T, Positioni> || std::is_same_v<T, Positionf>;

}

#endif // IKSDL_POSITION_HPP
