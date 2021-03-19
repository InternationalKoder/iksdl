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

#ifndef IKSDL_SOUND_HPP
#define IKSDL_SOUND_HPP

#include "iksdl/Channels.hpp"
#include "iksdl_export.hpp"
#include <SDL_mixer.h>
#include <string>
#include <optional>
#include <chrono>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Handles sound to play
///
/// Multiple sounds can be played at a time.
///
/// \see Music
/////////////////////////////////////////////////
class Sound
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that loads the sound from a file
        ///
        /// This constructor will throw \a InvalidParameterException if
        /// the sound could not be loaded.
        ///
        /// Supported formats: WAVE, AIFF, RIFF, OGG, VOC
        ///
        /// \param filePath Path to audio file
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit Sound(const std::string& filePath);

        Sound(const Sound&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Sound to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Sound(Sound&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Sound();

        Sound& operator=(const Sound&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Sound to be moved
        ///
        /// \return Moved sound
        /////////////////////////////////////////////////
        IKSDL_EXPORT Sound& operator=(Sound&& other);

        /////////////////////////////////////////////////
        /// \brief Play the sound
        ///
        /// By default the sound is played once.
        /// Set the \a loops parameter to change this behaviour.
        /// When \a loops is set to -1, the sound will be infinitely repeated.
        ///
        /// \param loops Number of times to play the sound
        /////////////////////////////////////////////////
        IKSDL_EXPORT void play(int loops = 0);

        /////////////////////////////////////////////////
        /// \brief Play the sound for a limited amount of time
        ///
        /// By default the sound is played once (fully or partially).
        /// Set the \a loops parameter to change this behaviour.
        /// When \a loops is set to -1, the sound will be infinitely repeated
        /// until the time limit is reached.
        ///
        /// \param time  Maximum time to play the sound
        /// \param loops Maximum number of times to play the sound
        /////////////////////////////////////////////////
        IKSDL_EXPORT void play(std::chrono::milliseconds time, int loops = 0);

        /////////////////////////////////////////////////
        /// \brief Pause the sound
        /////////////////////////////////////////////////
        inline void pause() const { if(m_channel.has_value()) Mix_Pause(m_channel.value()); }

        /////////////////////////////////////////////////
        /// \brief Resume the sound
        /////////////////////////////////////////////////
        inline void resume() const { if(m_channel.has_value()) Mix_Resume(m_channel.value()); }

        /////////////////////////////////////////////////
        /// \brief Change the sound volume
        ///
        /// \param volume New volume, between 0 and 128
        /////////////////////////////////////////////////
        inline void setVolume(int volume) const { Mix_VolumeChunk(m_chunk, volume); }

        /////////////////////////////////////////////////
        /// \brief Is the sound currently being played?
        ///
        /// \return True if the sound is playing
        /////////////////////////////////////////////////
        inline bool isPlaying() const { return m_channel.has_value() && Mix_Playing(m_channel.value()) != 0; }

        /////////////////////////////////////////////////
        /// \brief Is the sound currently paused?
        ///
        /// \return True if the sound is paused
        /////////////////////////////////////////////////
        inline bool isPaused() const { return m_channel.has_value() && Mix_Paused(m_channel.value()) != 0; }

        /////////////////////////////////////////////////
        /// \brief Pause all the sounds
        /////////////////////////////////////////////////
        IKSDL_EXPORT static void pauseAll() { Mix_Pause(-1); }

    private:

        priv::Channels* m_channels;   ///< Audio channels manager
        Mix_Chunk* m_chunk;           ///< SDL sound that can be played
        std::optional<int> m_channel; ///< Audio channel that the sound plays on
};

}

#endif // IKSDL_SOUND_HPP
