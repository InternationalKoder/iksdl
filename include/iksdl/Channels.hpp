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

#ifndef IKSDL_CHANNELS_HPP
#define IKSDL_CHANNELS_HPP

#include <vector>

namespace iksdl::priv
{

/////////////////////////////////////////////////
/// \brief Singleton that handles the use of audio channels
///
/// \warning This is IKSDL internal code that should not be
/// used outside of the library
/////////////////////////////////////////////////
class Channels
{
    public:

        /////////////////////////////////////////////////
        /// \brief Get the singleton instance
        ///
        /// \return Singleton instance
        /////////////////////////////////////////////////
        inline static Channels* getInstance() { static Channels channels; return &channels; }

        /////////////////////////////////////////////////
        /// \brief Reserve an audio channel
        ///
        /// Finds an audio channel that is not currently
        /// reserved, and reserve it to avoid multiple usages
        /// of the same channel.
        ///
        /// If all the allocated audio channels are already reserved,
        /// new audio channels are allocated. One of these
        /// newly allocated channels is then reserved.
        ///
        /// Once the audio channel is not longer in use, it
        /// should be freed.
        ///
        /// \return Reserved audio channel ID
        ///
        /// \see free
        /////////////////////////////////////////////////
        int reserve();

        /////////////////////////////////////////////////
        /// \brief Free a reserved audio channel
        ///
        /// This is required in order for the audio channel
        /// to be reserved again for another use.
        ///
        /// If the channel is already freed when this method
        /// is called, nothing happens.
        ///
        /// \param channel Audio channel ID to free
        /////////////////////////////////////////////////
        inline void free(int channel) { m_channels[channel] = false; };

    private:

        /////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////
        Channels();

        static constexpr unsigned int ALLOCATION_STEP = 2; ///< Number of channels to allocate when none is available

        std::vector<bool> m_channels; ///< Reservation state of the audio channels
};

/////////////////////////////////////////////////
/// \brief Free a reserved audio channel
///
/// This function is a short way to call \a isdkl::Channels::free
/// without explicitely getting the \a isdkl::Channels singleton
///
/// \param channel Audio channel ID to free
///
/// \see isdkl::Channels::free
/////////////////////////////////////////////////
inline void freeChannel(int channel) { Channels::getInstance()->free(channel); }

}

#endif // IKSDL_CHANNELS_HPP
