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

#ifndef IKSDL_COLOR_HPP
#define IKSDL_COLOR_HPP

#include "iksdl/iksdl_export.hpp"
#include <algorithm>
#include <string>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Defines a color
/////////////////////////////////////////////////
class Color
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that creates a new color from its components
        ///
        /// \param red   Quantity of red, between 0 and 255 included
        /// \param green Quantity of green, between 0 and 255 included
        /// \param blue  Quantity of blue, between 0 and 255 included
        /// \param alpha Quantity of alpha (transparency), between 0 and 255 included
        /////////////////////////////////////////////////
        constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) :
            m_red(red),
            m_green(green),
            m_blue(blue),
            m_alpha(alpha)
        {}

        /////////////////////////////////////////////////
        /// \brief Add each component of two colors to create a new one
        ///
        /// The sum is capped at 255 for each component.
        ///
        /// \param other Color to add
        ///
        /// \return New color that is the sum of the current color and the given one
        /////////////////////////////////////////////////
        constexpr Color operator+(const Color& other) const
        {
            return Color(std::min(static_cast<unsigned int>(m_red) + static_cast<unsigned int>(other.m_red), 255u),
                         std::min(static_cast<unsigned int>(m_green) + static_cast<unsigned int>(other.m_green), 255u),
                         std::min(static_cast<unsigned int>(m_blue) + static_cast<unsigned int>(other.m_blue), 255u),
                         std::min(static_cast<unsigned int>(m_alpha) + static_cast<unsigned int>(other.m_alpha), 255u));
        }

        /////////////////////////////////////////////////
        /// \brief Subtract each component of the given color to the current one
        ///
        /// The subtraction is capped at 0 for each component.
        ///
        /// \param other Color to subtract
        ///
        /// \return New color that is the subtraction of the current color and the given one
        /////////////////////////////////////////////////
        constexpr Color operator-(const Color& other) const
        {
            return Color(m_red > other.m_red ? m_red - other.m_red : 0u,
                         m_green > other.m_green ? m_green - other.m_green : 0u,
                         m_blue > other.m_blue ? m_blue - other.m_blue : 0u,
                         m_alpha > other.m_alpha ? m_alpha - other.m_alpha : 0u);
        }

        /////////////////////////////////////////////////
        /// \brief Compute the equality between two colors
        ///
        /// Colors are equal when each of the 4 components have
        /// the same value for both colors.
        ///
        /// \param other Color to compare
        ///
        /// \return True if the colors are equal
        /////////////////////////////////////////////////
        constexpr bool operator==(const Color& other) const
        {
            return m_red == other.m_red &&
                    m_green == other.m_green &&
                    m_blue == other.m_blue &&
                    m_alpha == other.m_alpha;
        };

        /////////////////////////////////////////////////
        /// \brief Compute the non-equality between two colors
        ///
        /// Colors are different when at least one of the 4 components
        /// has different values in both colors.
        ///
        /// \param other Color to compare
        ///
        /// \return True if the colors are not equal
        /////////////////////////////////////////////////
        constexpr bool operator!=(const Color& other) const
        {
            return m_red != other.m_red ||
                    m_green != other.m_green ||
                    m_blue != other.m_blue ||
                    m_alpha != other.m_alpha;
        };

        /////////////////////////////////////////////////
        /// \brief Get the red component
        ///
        /// \return Value of the red component, between 0 and 255
        /////////////////////////////////////////////////
        constexpr uint8_t getRed() const { return m_red; }

        /////////////////////////////////////////////////
        /// \brief Get the green component
        ///
        /// \return Value of the green component, between 0 and 255
        /////////////////////////////////////////////////
        constexpr uint8_t getGreen() const { return m_green; }

        /////////////////////////////////////////////////
        /// \brief Get the blue component
        ///
        /// \return Value of the blue component, between 0 and 255
        /////////////////////////////////////////////////
        constexpr uint8_t getBlue() const { return m_blue; }

        /////////////////////////////////////////////////
        /// \brief Get the alpha component
        ///
        /// \return Value of the alpha component, between 0 and 255
        /////////////////////////////////////////////////
        constexpr uint8_t getAlpha() const { return m_alpha; }

    private:

        uint8_t m_red;   ///< Red component
        uint8_t m_green; ///< Green component
        uint8_t m_blue;  ///< Blue component
        uint8_t m_alpha; ///< Alpha component
};

}

#endif // IKSDL_COLOR_HPP
