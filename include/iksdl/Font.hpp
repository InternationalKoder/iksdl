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

#ifndef IKSDL_FONT_HPP
#define IKSDL_FONT_HPP

#include "iksdl_export.hpp"
#include <SDL_ttf.h>
#include <string>

namespace iksdl
{

class Text;

/////////////////////////////////////////////////
/// \brief Represents a text font
///
/// This class holds the font definition and should
/// be kept alive while there is text using it.
///
/// \see Text
/////////////////////////////////////////////////
class Font
{
    friend class BaseText;

    public:

        /////////////////////////////////////////////////
        /// \brief Constructor loading the font from a file
        ///
        /// This constructor will throw \a InvalidParameterException if
        /// the font could not be loaded.
        ///
        /// Supported formats: TTF and FON
        ///
        /// \param filePath Path to font file
        /// \param ptSize   Point size to load font as
        /////////////////////////////////////////////////
        IKSDL_EXPORT Font(const std::string& filePath, int ptSize);

        Font(const Font&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move constructor
        ///
        /// \param other Font to be moved
        /////////////////////////////////////////////////
        IKSDL_EXPORT Font(Font&& other);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Font();

        Font& operator=(const Font&) = delete;

        /////////////////////////////////////////////////
        /// \brief Move assignment operator
        ///
        /// \param other Font to be moved
        ///
        /// \return Moved font
        /////////////////////////////////////////////////
        IKSDL_EXPORT Font& operator=(Font&& other);

    private:

        TTF_Font* m_font; ///< SDL font
};

}

#endif // IKSDL_FONT_HPP
