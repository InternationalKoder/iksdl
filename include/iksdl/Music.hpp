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

#ifndef IKSDL_MUSIC_HPP
#define IKSDL_MUSIC_HPP

#include "iksdl_export.hpp"
#include <SDL_mixer.h>
#include <string>

namespace iksdl
{

/////////////////////////////////////////////////
/// \brief Handles music to play
///
/// Only one music can be played at a time.
///
/// \see Sound
/////////////////////////////////////////////////
class Music
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor that loads the music from a file
        ///
        /// This constructor will throw \a InvalidParameterException if
        /// the music could not be loaded.
        ///
        /// Supported formats: WAVE, MOD, MIDI, OGG, MP3, FLAC
        ///
        /// \param filePath Path to audio file
        /////////////////////////////////////////////////
        IKSDL_EXPORT explicit Music(const std::string& filePath);


        Music(const Music&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Music to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Music(Music&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Music();

        Music& operator=(const Music&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Music to be moved
        ///
        /// \return Moved music
        /////////////////////////////////////////////////
        IKSDL_EXPORT Music& operator=(Music&& other);

        /////////////////////////////////////////////////
        /// \brief Play the music
        ///
        /// By default the music is replayed continuously.
        /// Set the \a loops parameter to change this behaviour.
        ///
        /// \param loops Number of times to play the music
        /////////////////////////////////////////////////
        inline void play(int loops = -1) const { Mix_PlayMusic(m_music, loops); }

        /////////////////////////////////////////////////
        /// \brief Is there music being played?
        ///
        /// \return True if music is currently playing
        /////////////////////////////////////////////////
        static inline bool isAnyPlaying() { return Mix_PlayingMusic() != 0; }

        /////////////////////////////////////////////////
        /// \brief Is the music paused?
        ///
        /// \return True if music is paused
        /////////////////////////////////////////////////
        static inline bool isAnyPaused() { return Mix_PausedMusic() != 0; }

        /////////////////////////////////////////////////
        /// \brief Change the music volume
        ///
        /// \param volume New volume, between 0 and 128
        /////////////////////////////////////////////////
        static inline void setVolume(int volume) { Mix_VolumeMusic(volume); }

    private:

        Mix_Music* m_music; ///< SDL music that can be played
};

}

#endif // IKSDL_MUSIC_HPP
