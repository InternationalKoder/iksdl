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

#include "iksdl/AbstractRectanglef.hpp"

namespace iksdl
{
AbstractRectanglef::AbstractRectanglef(const Rectf& rect, Color color) :
    m_rect{ .x = rect.getX(), .y = rect.getY(), .w = rect.getWidth(), .h = rect.getHeight() },
    m_color(std::move(color))
{}

AbstractRectanglef::AbstractRectanglef(const Positionf& position, const Sizef& size, Color color) :
    m_rect{ .x = position.getX(), .y = position.getY(), .w = size.getWidth(), .h = size.getHeight() },
    m_color(std::move(color))
{}
}