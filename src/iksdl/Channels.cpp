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

#include "iksdl/Channels.hpp"
#include <SDL_mixer.h>

namespace iksdl::priv
{
Channels::Channels() :
    m_channels(Mix_AllocateChannels(-1), false)
{
    Mix_ChannelFinished(freeChannel);
}

int Channels::reserve()
{
    const size_t channelsCount = m_channels.size();
    for(size_t i = 0 ; i < channelsCount ; ++i)
    {
        if(!m_channels[i])
        {
            m_channels[i] = true;
            return static_cast<int>(i);
        }
    }

    // If we arrive here, it means that we could not find an available channel
    Mix_AllocateChannels(static_cast<int>(channelsCount) + ALLOCATION_STEP);
    m_channels.push_back(true);
    m_channels.push_back(false);

    return static_cast<int>(channelsCount);
}
}
