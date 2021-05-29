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

#include "iksdl/Spritef.hpp"
#include "iksdl/Texture.hpp"

namespace iksdl
{
Spritef::Spritef(const Texture& texture, const Positionf& position) :
    BaseSprite(texture),
    m_rect({ .x = position.getX(), .y = position.getY(),
           .w = static_cast<float>(m_texture->m_size.getWidth()), .h = static_cast<float>(m_texture->m_size.getHeight()) }),
    m_centerPtr(nullptr)
{}

Spritef::Spritef(const Texture& texture, const Positionf& position, const Recti& textureRect) :
    BaseSprite(texture),
    m_rect({ .x = position.getX(), .y = position.getY(),
           .w = static_cast<float>(m_texture->m_size.getWidth()), .h = static_cast<float>(m_texture->m_size.getHeight()) }),
    m_centerPtr(nullptr)
{
    Spritef::setTextureRect(textureRect);
}

void Spritef::scale(const Sizef& delta)
{
    m_rect.w *= delta.getWidth();
    m_rect.h *= delta.getHeight();
    m_scale = m_scale * delta;
}

void Spritef::draw(SDL_Renderer* const renderer) const
{
    if(m_rotation == 0.0 && m_flip == SDL_FLIP_NONE)
        SDL_RenderCopyF(renderer, m_texture->m_texture, m_textureRectPtr, &m_rect);
    else
        SDL_RenderCopyExF(renderer, m_texture->m_texture, m_textureRectPtr, &m_rect, m_rotation, m_centerPtr, m_flip);
}

void Spritef::setTextureRect(const Recti& rect)
{
    // Update the rect to match the new texture rect's size
    if(rect.getWidth() != m_rect.w || rect.getHeight() != m_rect.h)
    {
        m_rect.w /= m_rect.w / rect.getWidth();
        m_rect.h /= m_rect.h / rect.getHeight();
    }

    // Apply current scale
    m_rect.w *= m_scale.getWidth();
    m_rect.h *= m_scale.getHeight();

    // Change texture rect
    m_textureRect = { .x = rect.getX(), .y = rect.getY(), .w = rect.getWidth(), .h = rect.getHeight() };
    m_textureRectPtr = &m_textureRect;
}

void Spritef::resetTextureRect()
{
    // Update the rect to match the full texture's size and apply current scale
    const Sizei& textureSize = m_texture->getSize();
    m_rect.w = static_cast<float>(textureSize.getWidth()) * m_scale.getWidth();
    m_rect.h = static_cast<float>(textureSize.getHeight()) * m_scale.getHeight();

    // Ignore currently set texture rect
    m_textureRectPtr = nullptr;
}

void Spritef::setCenter(const Positionf& center)
{
    m_center = SDL_FPoint { .x = center.getX(), .y = center.getY() };
    m_centerPtr = &m_center;
}
}
