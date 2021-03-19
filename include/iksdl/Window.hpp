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

#ifndef IKSDL_WINDOW_HPP
#define IKSDL_WINDOW_HPP

#include "iksdl/Size.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Color.hpp"
#include "iksdl/Event.hpp"
#include "iksdl/EventSupport.hpp"
#include "iksdl/QuitEvent.hpp"
#include "iksdl/WindowEvent.hpp"
#include "iksdl/KeyboardEvent.hpp"
#include "iksdl/MouseButtonEvent.hpp"
#include "iksdl/MouseMotionEvent.hpp"
#include "iksdl/MouseWheelEvent.hpp"
#include "iksdl/Renderer.hpp"
#include "iksdl/Texture.hpp"
#include "iksdl/SdlException.hpp"
#include "iksdl/RendererOptions.hpp"
#include "iksdl/WindowOptions.hpp"
#include "iksdl/iksdl_export.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Window that can render graphics
/////////////////////////////////////////////////
class Window : public Renderer
{
    public:

        static constexpr EventSupport ALL_EVENTS_SUPPORT = EventSupport(
                    { Event::Type::Window, Event::Type::Keyboard,
                      Event::Type::MouseMotion, Event::Type::MouseButton, Event::Type::MouseWheel }); ///< Support all events

        static constexpr WindowOptions DEFAULT_OPTIONS = WindowOptions().shown(); ///< Default window options

        /////////////////////////////////////////////////
        /// \brief Constructor allowing to set all the parameters for the window
        ///
        /// This constructor will throw \a SdlException if
        /// the initialization fails.
        ///
        /// \param title           Window title
        /// \param size            Window size
        /// \param options         Window options
        /// \param rendererOptions Rendering options
        /// \param position        Window position (top-left corner)
        /////////////////////////////////////////////////
        IKSDL_EXPORT Window(const std::string& title, const Sizei& size, const WindowOptions& options = DEFAULT_OPTIONS,
                            const RendererOptions& rendererOptions = Renderer::DEFAULT_OPTIONS,
                            const Positioni& position = UNDEFINED_POSITION);

        Window(const Window&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Window to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Window(Window&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Window();

        Window& operator=(const Window&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Window to be moved
        ///
        /// \return Moved window
        /////////////////////////////////////////////////
        IKSDL_EXPORT Window& operator=(Window&& other);


        /////////////////////////////////////////////////
        /// \brief Fetch an event that has not been handled yet
        ///
        /// This method always return immediately, it never
        /// waits, event if there is not pending event.
        ///
        /// \tparam E Type of events to fetch
        ///
        /// \return Event ready to be handled
        /////////////////////////////////////////////////
        template<EventSupport E = ALL_EVENTS_SUPPORT>
        Event pollEvent() const
        {
            SDL_Event event;

            if(SDL_PollEvent(&event) && event.window.windowID == m_windowId)
                return buildEvent<E>(event);

            return Event(nullptr);
        }

        /////////////////////////////////////////////////
        /// \brief Wait for an event that has not been handled yet
        ///
        /// If an event is ready to be handled, this method returns
        /// immediately. Otherwise, it waits for an event to be ready.
        ///
        /// This method may throw \a SdlException if it
        /// failed waiting.
        ///
        /// \tparam E Type of events to fetch
        ///
        /// \return Event ready to be handled
        /////////////////////////////////////////////////
        template<EventSupport E = ALL_EVENTS_SUPPORT>
        Event waitEvent() const
        {
            SDL_Event event;

            if(SDL_WaitEvent(&event) && event.window.windowID == m_windowId)
                return buildEvent<E>(event);

            if(event.window.windowID == m_windowId)
                throw SdlException(std::string(WAIT_EVENT_ERROR) + SDL_GetError());
        }

        /////////////////////////////////////////////////
        /// \brief Get window position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT Positioni getPosition() const;

        /////////////////////////////////////////////////
        /// \brief Get window size
        ///
        /// \return Current size
        /////////////////////////////////////////////////
        IKSDL_EXPORT Sizei getSize() const;

    private:

        static constexpr std::string_view CREATE_CONTEXT_ERROR = "Could not create SDL context.\nCause: ";
        static constexpr std::string_view CREATE_IMAGE_LOADERS_ERROR = "Could not load image loaders.\nCause: ";
        static constexpr std::string_view CREATE_FONT_LOADERS_ERROR = "Could not load font loaders.\nCause: ";
        static constexpr std::string_view CREATE_AUDIO_LOADERS_ERROR = "Could not load audio loaders.\nCause: ";
        static constexpr std::string_view CREATE_WINDOW_ERROR = "Could not create window.\nCause: ";
        static constexpr std::string_view WAIT_EVENT_ERROR = "Error while waiting for an event.\nCause: ";

        static constexpr Positioni UNDEFINED_POSITION = Positioni(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
        static constexpr int IMG_LIBRARIES = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
        static constexpr int AUDIO_FREQUENCY = 44100;
        static constexpr int AUDIO_CHUNK_SIZE = 2048;

        /////////////////////////////////////////////////
        /// \brief Constructor from a SDL window
        ///
        /// \param sdlWindow       SDL window
        /// \param rendererOptions Rendering options
        /////////////////////////////////////////////////
        Window(SDL_Window& sdlWindow, const RendererOptions& rendererOptions);

        /////////////////////////////////////////////////
        /// \brief Create a new window
        ///
        /// \param title    Window title
        /// \param size     Window size
        /// \param options  Window options
        /// \param position Window position (top-left corner)
        ///
        /// \return New window
        /////////////////////////////////////////////////
        static SDL_Window* createWindow(const std::string& title, const Sizei& size,
                                        const WindowOptions& options, const Positioni& position);

        /////////////////////////////////////////////////
        /// \brief Build a \a iksdl::event from a SDL event
        ///
        /// \tparam E Event types to handle, other types are ignored
        ///
        /// \param sdlEvent SDL event to transform
        ///
        /// \return Transformed event
        /////////////////////////////////////////////////
        template<EventSupport E>
        Event buildEvent(const SDL_Event sdlEvent) const
        {
            try
            {
                if constexpr(E.mouseMotionEventsEnabled)
                {
                    if(sdlEvent.type == SDL_MOUSEMOTION)
                        return Event(std::make_unique<MouseMotionEvent>(MouseMotionEvent(sdlEvent.motion)));
                }

                if constexpr(E.mouseButtonEventsEnabled)
                {
                    if(sdlEvent.type == SDL_MOUSEBUTTONDOWN || sdlEvent.type == SDL_MOUSEBUTTONUP)
                        return Event(std::make_unique<MouseButtonEvent>(MouseButtonEvent(sdlEvent.button)));
                }

                if constexpr(E.keyboardEventsEnabled)
                {
                    if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
                        return Event(std::make_unique<KeyboardEvent>(KeyboardEvent(sdlEvent.key)));
                }

                if constexpr(E.mouseWheelEventsEnabled)
                {
                    if(sdlEvent.type == SDL_MOUSEWHEEL)
                        return Event(std::make_unique<MouseWheelEvent>(MouseWheelEvent(sdlEvent.wheel)));
                }

                if constexpr(E.windowEventsEnabled)
                {
                    if(sdlEvent.type == SDL_WINDOWEVENT)
                        return Event(std::make_unique<WindowEvent>(WindowEvent(sdlEvent.window)));
                }

                if(sdlEvent.type == SDL_QUIT)
                    return Event(std::make_unique<QuitEvent>());

                return Event(nullptr);
            }
            catch(const SdlException&)
            {
                return Event(nullptr);
            }
        }

        /////////////////////////////////////////////////
        /// \brief Get number of opened windows
        ///
        /// \return Number of windows
        /////////////////////////////////////////////////
        inline static unsigned int& windowsCount() { static unsigned int count = 0; return count; }

        SDL_Window* m_window; ///< SDL window
        uint32_t m_windowId;  ///< Window identifier
};

}

#endif // IKSDL_WINDOW_HPP
