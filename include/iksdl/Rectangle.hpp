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

#ifndef IKSDL_RECTANGLE_HPP
#define IKSDL_RECTANGLE_HPP

#include "iksdl/AbstractRectangle.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Size.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Color.hpp"
#include "iksdl/iksdl_export.hpp"

extern "C"
{
struct SDL_Renderer;
}

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief The borders of a rectangle that can be drawn using \c int coordinates
///
/// \note When handling several rectangles with same color,
/// prefer \c RectangleArray for better performance
///
/// \see RectangleArray, FillRectangle
/////////////////////////////////////////////////
class Rectangle : public AbstractRectangle
{
    using AbstractRectangle::AbstractRectangle;

    public:

        /////////////////////////////////////////////////
        /// \brief Draw the rectangle
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void draw(SDL_Renderer* const renderer) const;
};

}

#endif // IKSDL_RECTANGLE_HPP
