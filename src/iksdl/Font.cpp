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

#include "iksdl/Font.hpp"
#include "iksdl/InvalidParameterException.hpp"
#include <SDL_ttf.h>
#include <SDL.h>

namespace iksdl
{
Font::Font(const std::string& filePath, int ptSize) :
    m_font(nullptr)
{
    m_font = TTF_OpenFont(filePath.c_str(), ptSize);
    if(m_font == nullptr)
        throw InvalidParameterException("Unable to load font at path " + filePath + ". Cause: " + TTF_GetError());
}

Font::Font(Font&& other) :
    m_font(std::exchange(m_font, other.m_font))
{}

Font::~Font()
{
    TTF_CloseFont(m_font);
}

Font& Font::operator=(Font&& other)
{
    if(this == &other)
        return *this;

    TTF_CloseFont(m_font);
    m_font = std::exchange(m_font, other.m_font);

    return *this;
}
}
