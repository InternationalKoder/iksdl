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

#include "iksdl/Window.hpp"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace iksdl
{
Window::Window(const std::string& title, const Sizei& size, const WindowOptions& options,
               const RendererOptions& rendererOptions, const Positioni& position) :
    Window(*createWindow(title, size, options, position), rendererOptions)
{}

Window::Window(Window&& other) :
    Renderer(*other.m_window),
    m_window(std::exchange(other.m_window, nullptr))
{}

Window::~Window()
{
    SDL_DestroyWindow(m_window);

    // Destroy SDL context and image loaders if there is not more window
    --windowsCount();
    if(windowsCount() == 0)
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

Window& Window::operator=(Window&& other)
{
    if(this == &other)
        return *this;

    SDL_DestroyWindow(m_window);
    m_window = std::exchange(other.m_window, nullptr);

    return *this;
}

Window::Window(SDL_Window& sdlWindow, const RendererOptions& rendererOptions) :
    Renderer(sdlWindow, rendererOptions),
    m_window(&sdlWindow),
    m_windowId(SDL_GetWindowID(m_window))
{
    ++windowsCount();
}

SDL_Window* Window::createWindow(const std::string& title, const Sizei& size,
                                 const WindowOptions& options, const Positioni& position)
{
    // Initialize SDL context and image loaders
    if(windowsCount() == 0)
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            throw SdlException(std::string(CREATE_CONTEXT_ERROR) + SDL_GetError());

        if(!(IMG_Init(IMG_LIBRARIES) & IMG_LIBRARIES))
            throw SdlException(std::string(CREATE_IMAGE_LOADERS_ERROR) + IMG_GetError());

        if(TTF_Init() < 0)
            throw SdlException(std::string(CREATE_FONT_LOADERS_ERROR) + TTF_GetError());

        if(Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, AUDIO_CHUNK_SIZE) < 0)
            throw SdlException(std::string(CREATE_AUDIO_LOADERS_ERROR) + Mix_GetError());
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(title.c_str(), position.getX(), position.getY(),
                                          size.getWidth(), size.getHeight(), options.m_sdlFlags);

    if(window == nullptr)
        throw SdlException(std::string(CREATE_WINDOW_ERROR) + SDL_GetError());

    return window;
}

Positioni Window::getPosition() const
{
    int x = 0, y = 0;
    SDL_GetWindowPosition(m_window, &x, &y);

    return Positioni(x, y);
}

Sizei Window::getSize() const
{
    int w = 0, h = 0;
    SDL_GetWindowSize(m_window, &w, &h);

    return Sizei(w, h);
}
}
