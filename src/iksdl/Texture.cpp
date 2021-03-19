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

#include "iksdl/Texture.hpp"
#include "iksdl/Window.hpp"
#include "iksdl/InvalidParameterException.hpp"
#include "iksdl/SdlException.hpp"
#include <SDL_image.h>

namespace iksdl
{
Texture::Texture(const Renderer& renderer, const std::string& filePath) :
    m_texture(nullptr),
    m_size(0, 0)
{
    // Load the image in GPU
    m_texture = IMG_LoadTexture(renderer.m_renderer, filePath.c_str());
    if(m_texture == nullptr)
        throw SdlException("Failed to create texture from path " + filePath + ". Cause: " + SDL_GetError());

    int w, h;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);
    m_size = Sizei(w, h);
}

Texture::Texture(const Renderer& renderer, const std::string& filePath, const Color& colorKey) :
    m_texture(nullptr),
    m_size(0, 0)
{
    // Load the image in memory
    SDL_Surface* const surface = IMG_Load(filePath.c_str());
    if(surface == nullptr)
        throw InvalidParameterException("Unable to load image at path " + filePath + ". Cause: " + IMG_GetError());

    m_size = Sizei(surface->w, surface->h);

    // Color key the image
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, colorKey.getRed(), colorKey.getGreen(), colorKey.getBlue()));

    // Load the image from memory to GPU
    m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

    // Free the image from memory
    SDL_FreeSurface(surface);

    if(m_texture == nullptr)
        throw SdlException("Failed to create texture for image from path " + filePath + ". Cause: " + SDL_GetError());
}

Texture::Texture(Texture&& other) :
    m_texture(std::exchange(other.m_texture, nullptr)),
    m_size(other.m_size)
{}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

Texture& Texture::operator=(Texture&& other)
{
    if(this == &other)
        return *this;

    SDL_DestroyTexture(m_texture);
    m_texture = std::exchange(other.m_texture, nullptr);

    return *this;
}
}
