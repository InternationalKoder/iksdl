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

#include "iksdl/Renderer.hpp"
#include "iksdl/SdlException.hpp"
#include <SDL.h>
#include <string>

namespace iksdl
{
Renderer::Renderer(SDL_Window& window, const RendererOptions& options) :
    m_renderer(nullptr)
{
    m_renderer = SDL_CreateRenderer(&window, -1, options.m_sdlFlags);
    if(m_renderer == nullptr)
        throw SdlException(std::string(CREATE_RENDERER_ERROR) + SDL_GetError());
}

Renderer::Renderer(Renderer&& other) :
    m_renderer(std::exchange(other.m_renderer, nullptr)),
    m_viewport(std::move(other.m_viewport))
{}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

Renderer& Renderer::operator=(Renderer&& other)
{
    if(this == &other)
        return *this;

    SDL_DestroyRenderer(m_renderer);
    m_renderer = std::exchange(other.m_renderer, nullptr);
    m_viewport = std::move(other.m_viewport);

    return *this;
}

void Renderer::clear(const Color& clearColor) const
{
    SDL_SetRenderDrawColor(m_renderer, clearColor.getRed(), clearColor.getGreen(),
                           clearColor.getBlue(), clearColor.getAlpha());
    SDL_RenderClear(m_renderer);
}

void Renderer::setViewport(const Recti& viewport)
{
    m_viewport = { .x = viewport.getX(), .y = viewport.getY(),
                   .w = viewport.getWidth(), .h = viewport.getHeight() };

    SDL_RenderSetViewport(m_renderer, &m_viewport);
}
}
