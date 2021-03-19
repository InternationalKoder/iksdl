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

#include "iksdl/Sound.hpp"
#include "iksdl/InvalidParameterException.hpp"

namespace iksdl
{
Sound::Sound(const std::string& filePath) :
    m_channels(priv::Channels::getInstance()),
    m_chunk(nullptr),
    m_channel(std::nullopt)
{
    m_chunk = Mix_LoadWAV(filePath.c_str());

    if(m_chunk == nullptr)
        throw InvalidParameterException("Failed to load sound from path " + filePath + ". Cause: " + Mix_GetError());
}

Sound::Sound(Sound&& other) :
    m_chunk(std::exchange(m_chunk, other.m_chunk)),
    m_channel(std::exchange(m_channel, other.m_channel))
{}

Sound::~Sound()
{
    Mix_FreeChunk(m_chunk);
}

Sound& Sound::operator=(Sound&& other)
{
    if(this == &other)
        return *this;

    Mix_FreeChunk(m_chunk);
    m_chunk = std::exchange(m_chunk, other.m_chunk);

    m_channel = std::exchange(m_channel, other.m_channel);

    return *this;
}

void Sound::play(int loops)
{
    const int channel = m_channels->reserve();
    m_channel = channel;
    Mix_PlayChannel(channel, m_chunk, loops);
}

void Sound::play(std::chrono::milliseconds time, int loops)
{
    const int channel = m_channels->reserve();
    m_channel = channel;
    Mix_PlayChannelTimed(channel, m_chunk, loops, static_cast<int>(time.count()));
}
}
