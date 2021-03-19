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

#include "iksdl/WindowEvent.hpp"
#include "iksdl/SdlException.hpp"
#include "iksdl/common.hpp"
#include <SDL.h>
#include <vector>
#include <algorithm>

namespace iksdl
{
WindowEvent::WindowEvent(const SDL_WindowEvent& sdlEvent) :
    m_movedTo(std::nullopt),
    m_resizedTo(std::nullopt)
{
    // Mapping for event type
    static const std::vector<std::pair<uint8_t, Type>> typeMap = [] ()
    {
        std::vector<std::pair<uint8_t, Type>> map(
        {
            { SDL_WINDOWEVENT_SHOWN, Type::Shown },
            { SDL_WINDOWEVENT_HIDDEN, Type::Hidden },
            { SDL_WINDOWEVENT_EXPOSED, Type::Exposed },
            { SDL_WINDOWEVENT_MOVED, Type::Moved },
            { SDL_WINDOWEVENT_RESIZED, Type::Resized },
            { SDL_WINDOWEVENT_SIZE_CHANGED, Type::SizeChanged },
            { SDL_WINDOWEVENT_MINIMIZED, Type::Minimized },
            { SDL_WINDOWEVENT_MAXIMIZED, Type::Maximized },
            { SDL_WINDOWEVENT_RESTORED, Type::Restored },
            { SDL_WINDOWEVENT_ENTER, Type::MouseEntered },
            { SDL_WINDOWEVENT_LEAVE, Type::MouseLeft },
            { SDL_WINDOWEVENT_FOCUS_GAINED, Type::FocusGained },
            { SDL_WINDOWEVENT_FOCUS_LOST, Type::FocusLost },
            { SDL_WINDOWEVENT_CLOSE, Type::Close },
            { SDL_WINDOWEVENT_TAKE_FOCUS, Type::TakeFocus },
            { SDL_WINDOWEVENT_HIT_TEST, Type::HitTest }
        });

        std::sort(map.begin(), map.end(), comparePairKeys<uint8_t, Type>);
        map.shrink_to_fit();

        return map;
    }();

    // Set event type
    const auto it = std::lower_bound(typeMap.begin(), typeMap.end(), std::make_pair(sdlEvent.event, Type::Shown),
                                     comparePairKeys<uint8_t, Type>);

    if(it != typeMap.end() && it->first == sdlEvent.event)
        m_type = it->second;
    else
        throw SdlException(UNKNOWN_EVENT_TYPE.data());

    // Set moved to position
    if(m_type == Type::Moved)
        m_movedTo = std::make_optional(Positioni(sdlEvent.data1, sdlEvent.data2));

    // Set resized to size
    else if(m_type == Type::Resized)
        m_resizedTo = std::make_optional(Sizei(sdlEvent.data1, sdlEvent.data2));
}
}
