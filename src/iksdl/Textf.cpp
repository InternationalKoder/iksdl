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

#include "iksdl/Textf.hpp"
#include <SDL_ttf.h>

namespace iksdl
{
Textf::Textf(const Renderer& renderer, const Font& font, std::string text, const Positionf& position,
             const Color& color, Encoding encoding, RenderMode renderMode) :
    BaseText(renderer, font, text, color, encoding, renderMode),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_centerPtr(nullptr)
{
    refreshTexture();
}

Textf::Textf(const Renderer& renderer, const Font& font, std::string text, const Positionf& position,
             const Color& color, const Color& backgroundColor, Encoding encoding) :
    BaseText(renderer, font, text, color, backgroundColor, encoding),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_centerPtr(nullptr)
{
    refreshTexture();
}

Textf::Textf(const Renderer& renderer, const Font& font, const std::u16string& text, const Positionf& position,
             const Color& color, RenderMode renderMode) :
    BaseText(renderer, font, text, color, renderMode),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_centerPtr(nullptr)
{
    refreshTexture();
}

Textf::Textf(const Renderer& renderer, const Font& font, const std::u16string& text, const Positionf& position,
             const Color& color, const Color& backgroundColor) :
    BaseText(renderer, font, text, color, backgroundColor),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_centerPtr(nullptr)
{
    refreshTexture();
}

void Textf::draw(SDL_Renderer* const renderer) const
{
    if(m_rotation == 0.0 && m_flip == SDL_FLIP_NONE)
        SDL_RenderCopyF(renderer, m_texture, nullptr, &m_rect);
    else
        SDL_RenderCopyExF(renderer, m_texture, nullptr, &m_rect, m_rotation, m_centerPtr, m_flip);
}

void Textf::setCenter(const Positionf& center)
{
    m_center = SDL_FPoint { .x = center.getX(), .y = center.getY() };
    m_centerPtr = &m_center;
}
}
