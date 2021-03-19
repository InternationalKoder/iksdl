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

#include "iksdl/Text.hpp"
#include "iksdl/Font.hpp"
#include "iksdl/InvalidParameterException.hpp"
#include "iksdl/SdlException.hpp"
#include "iksdl/Renderer.hpp"
#include <SDL_ttf.h>

namespace iksdl
{
Text::Text(const Renderer& renderer, const Font& font, std::string text, const Positioni& position,
           const Color& color, Encoding encoding, RenderMode renderMode) :
    m_renderer(&renderer),
    m_font(&font),
    m_color({ .r = color.getRed(), .g = color.getGreen(), .b = color.getBlue(), .a = color.getAlpha() }),
    m_backgroundColor(std::nullopt),
    m_encoding(std::move(encoding)),
    m_renderMode(std::move(renderMode)),
    m_text(std::move(text)),
    m_unicodeText(std::nullopt),
    m_texture(nullptr),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{
    refreshTexture();
}

Text::Text(const Renderer& renderer, const Font& font, std::string text, const Positioni& position,
           const Color& color, const Color& backgroundColor, Encoding encoding) :
    m_renderer(&renderer),
    m_font(&font),
    m_color({ .r = color.getRed(), .g = color.getGreen(), .b = color.getBlue(), .a = color.getAlpha() }),
    m_backgroundColor({ .r = backgroundColor.getRed(), .g = backgroundColor.getGreen(), .b = backgroundColor.getBlue(), .a = backgroundColor.getAlpha() }),
    m_encoding(std::move(encoding)),
    m_renderMode(RenderMode::Solid),
    m_text(std::move(text)),
    m_unicodeText(std::nullopt),
    m_texture(nullptr),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{
    refreshTexture();
}

Text::Text(const Renderer& renderer, const Font& font, const std::u16string& text, const Positioni& position,
           const Color& color, RenderMode renderMode) :
    m_renderer(&renderer),
    m_font(&font),
    m_color({ .r = color.getRed(), .g = color.getGreen(), .b = color.getBlue(), .a = color.getAlpha() }),
    m_backgroundColor(std::nullopt),
    m_encoding(Encoding::Latin1),
    m_renderMode(std::move(renderMode)),
    m_text(std::nullopt),
    m_unicodeText(convertUnicodeString(text)),
    m_texture(nullptr),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{
    refreshTexture();
}

Text::Text(const Renderer& renderer, const Font& font, const std::u16string& text, const Positioni& position,
           const Color& color, const Color& backgroundColor) :
    m_renderer(&renderer),
    m_font(&font),
    m_color({ .r = color.getRed(), .g = color.getGreen(), .b = color.getBlue(), .a = color.getAlpha() }),
    m_backgroundColor({ .r = backgroundColor.getRed(), .g = backgroundColor.getGreen(), .b = backgroundColor.getBlue(), .a = backgroundColor.getAlpha() }),
    m_encoding(Encoding::Latin1),
    m_renderMode(RenderMode::Solid),
    m_text(std::nullopt),
    m_unicodeText(convertUnicodeString(text)),
    m_texture(nullptr),
    m_rect({ .x = position.getX(), .y = position.getY() }),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0),
    m_centerPtr(nullptr),
    m_flip(SDL_FLIP_NONE)
{
    refreshTexture();
}

Text::~Text()
{
    SDL_DestroyTexture(m_texture);
}

void Text::draw(SDL_Renderer* const renderer) const
{
    if(m_rotation == 0.0 && m_flip == SDL_FLIP_NONE)
        SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
    else
        SDL_RenderCopyEx(renderer, m_texture, nullptr, &m_rect, m_rotation, m_centerPtr, m_flip);
}

void Text::setCenter(const Positioni& center)
{
    m_center = SDL_Point { .x = center.getX(), .y = center.getY() };
    m_centerPtr = &m_center;
}

void Text::setFlip(Flip flip)
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

void Text::setText(std::string text)
{
    m_text = std::move(text);
    m_unicodeText = std::nullopt;
    refreshTexture();
}

void Text::setText(const std::u16string& text)
{
    m_unicodeText = convertUnicodeString(text);
    m_text = std::nullopt;
    refreshTexture();
}

void Text::setColor(const Color& color)
{
    m_color = { .r = color.getRed(), .g = color.getGreen(), .b = color.getBlue(), .a = color.getAlpha() };
    refreshTexture();
}

void Text::setBackgroundColor(const Color& backgroundColor)
{
    m_backgroundColor = { .r = backgroundColor.getRed(), .g = backgroundColor.getGreen(),
                          .b = backgroundColor.getBlue(), .a = backgroundColor.getAlpha() };
    refreshTexture();
}

void Text::refreshTexture()
{
    SDL_Surface* surface = nullptr;

    if(m_text.has_value())
    {
        if(!m_backgroundColor.has_value() && m_renderMode == RenderMode::Solid)
        {
            if(m_encoding == Encoding::Latin1)
                surface = TTF_RenderText_Solid(m_font->m_font, m_text->c_str(), m_color);
            else
                surface = TTF_RenderUTF8_Solid(m_font->m_font, m_text->c_str(), m_color);
        }
        else if(!m_backgroundColor.has_value())
        {
            if(m_encoding == Encoding::Latin1)
                surface = TTF_RenderText_Blended(m_font->m_font, m_text->c_str(), m_color);
            else
                surface = TTF_RenderUTF8_Blended(m_font->m_font, m_text->c_str(), m_color);
        }
        else
        {
            if(m_encoding == Encoding::Latin1)
                surface = TTF_RenderText_Shaded(m_font->m_font, m_text->c_str(), m_color, m_backgroundColor.value());
            else
                surface = TTF_RenderUTF8_Shaded(m_font->m_font, m_text->c_str(), m_color, m_backgroundColor.value());
        }
    }
    else if(m_unicodeText.has_value())
    {
        if(!m_backgroundColor.has_value() && m_renderMode == RenderMode::Solid)
            surface = TTF_RenderUNICODE_Solid(m_font->m_font, m_unicodeText->data(), m_color);
        else if(!m_backgroundColor.has_value())
            surface = TTF_RenderUNICODE_Blended(m_font->m_font, m_unicodeText->data(), m_color);
        else
            surface = TTF_RenderUNICODE_Shaded(m_font->m_font, m_unicodeText->data(), m_color, m_backgroundColor.value());
    }
    else
        return;

    if(surface == nullptr)
        throw InvalidParameterException(std::string(CREATE_TEXT_FAILURE) + TTF_GetError());

    if(m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer->m_renderer, surface);

    const int width = surface->w;
    const int height = surface->h;

    SDL_FreeSurface(surface);

    if(m_texture == nullptr)
        throw SdlException(std::string(CREATE_TEXTURE_FAILURE) + SDL_GetError());

    m_rect.w = width;
    m_rect.h = height;
}

std::vector<uint16_t> Text::convertUnicodeString(const std::u16string& str)
{
    std::vector<std::uint16_t> intStr;
    intStr.reserve(str.size());

    for(const auto& character : str)
        intStr.push_back(character);

    intStr.shrink_to_fit();

    return intStr;
}
}
