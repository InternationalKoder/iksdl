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

#include "iksdl/Sprite.hpp"

namespace iksdl
{
Sprite::Sprite(const Texture& texture, const Positioni& position) :
    m_texture(&texture),
    m_rect({ .x = position.getX(), .y = position.getY(),
           .w = m_texture->m_size.getWidth(), .h = m_texture->m_size.getHeight() }),
    m_textureRectPtr(nullptr),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{}

Sprite::Sprite(const Texture& texture, const Positioni& position, const Recti& textureRect) :
    m_texture(&texture),
    m_rect({ .x = position.getX(), .y = position.getY(),
           .w = m_texture->m_size.getWidth(), .h = m_texture->m_size.getHeight() }),
    m_textureRectPtr(nullptr),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{
    setTextureRect(textureRect);
}

void Sprite::scale(const Sizef& delta)
{
    m_rect.w = static_cast<int>(static_cast<float>(m_rect.w) * delta.getWidth());
    m_rect.h = static_cast<int>(static_cast<float>(m_rect.h) * delta.getHeight());
    m_scale = m_scale * delta;
}

void Sprite::draw(SDL_Renderer* const renderer) const
{
    if(m_rotation == 0.0 && m_flip == SDL_FLIP_NONE)
        SDL_RenderCopy(renderer, m_texture->m_texture, m_textureRectPtr, &m_rect);
    else
        SDL_RenderCopyEx(renderer, m_texture->m_texture, m_textureRectPtr, &m_rect, m_rotation, m_centerPtr, m_flip);
}

void Sprite::setTextureRect(const Recti& rect)
{
    // Update the rect to match the new texture rect's size
    if(rect.getWidth() != m_rect.w || rect.getHeight() != m_rect.h)
    {
        const float fw = static_cast<float>(m_rect.w);
        const float fh = static_cast<float>(m_rect.h);
        m_rect.w = static_cast<int>(fw / (fw / static_cast<float>(rect.getWidth())));
        m_rect.h = static_cast<int>(fh / (fh / static_cast<float>(rect.getHeight())));
    }

    // Apply current scale
    m_rect.w = static_cast<int>(static_cast<float>(m_rect.w) * m_scale.getWidth());
    m_rect.h = static_cast<int>(static_cast<float>(m_rect.h) * m_scale.getHeight());

    // Change texture rect
    m_textureRect = { .x = rect.getX(), .y = rect.getY(), .w = rect.getWidth(), .h = rect.getHeight() };
    m_textureRectPtr = &m_textureRect;
}

void Sprite::resetTextureRect()
{
    // Update the rect to match the full texture's size and apply current scale
    const Sizei& textureSize = m_texture->getSize();
    m_rect.w = static_cast<int>(static_cast<float>(textureSize.getWidth()) * m_scale.getWidth());
    m_rect.h = static_cast<int>(static_cast<float>(textureSize.getHeight()) * m_scale.getHeight());

    // Ignore currently set texture rect
    m_textureRectPtr = nullptr;
}

void Sprite::setCenter(const Positioni& center)
{
    m_center = SDL_Point { .x = center.getX(), .y = center.getY() };
    m_centerPtr = &m_center;
}

void Sprite::setFlip(Flip flip)
{
    switch(flip)
    {
        case Flip::None:
            m_flip = SDL_FLIP_NONE;
            break;
        case Flip::Horizontal:
            m_flip = SDL_FLIP_HORIZONTAL;
            break;
        case Flip::Vertical:
            m_flip = SDL_FLIP_VERTICAL;
            break;
        case Flip::Both:
            m_flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
            break;
    }
}
}
