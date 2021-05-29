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

#ifndef IKSDL_TEXTF_HPP
#define IKSDL_TEXTF_HPP

#include "iksdl/BaseText.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Size.hpp"
#include "iksdl_export.hpp"
#include <SDL.h>

namespace iksdl
{

class Renderer;
class Font;

/////////////////////////////////////////////////
/// \brief A text that can be drawn using \c float coordinates
/////////////////////////////////////////////////
class Textf : public BaseText
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor with given encoding and render mode
        ///
        /// The font must not be destroyed while a text is using it.
        ///
        /// \param renderer   Renderer that will handle the drawing
        /// \param font       Font that will be used to render the text
        /// \param text       Text string
        /// \param position   Position where the text will be drawn (top-left corner)
        /// \param color      Text color
        /// \param encoding   String encoding
        /// \param renderMode Rendering mode to use when drawing the text
        /////////////////////////////////////////////////
        IKSDL_EXPORT Textf(const Renderer& renderer, const Font& font, std::string text, const Positionf& position,
                           const Color& color, Encoding encoding = Encoding::Latin1, RenderMode renderMode = RenderMode::Blended);

        /////////////////////////////////////////////////
        /// \brief Constructor with given encoding and shaded render mode
        ///
        /// The font must not be destroyed while a text is using it.
        ///
        /// \param renderer        Renderer that will handle the drawing
        /// \param font            Font that will be used to render the text
        /// \param text            Text string
        /// \param position        Position where the text will be drawn (top-left corner)
        /// \param color           Text color
        /// \param backgroundColor Color of the background rectangle
        /// \param encoding        String encoding
        /////////////////////////////////////////////////
        IKSDL_EXPORT Textf(const Renderer& renderer, const Font& font, std::string text, const Positionf& position,
                           const Color& color, const Color& backgroundColor, Encoding encoding = Encoding::Latin1);

        /////////////////////////////////////////////////
        /// \brief Constructor with unicode encoding and given render mode
        ///
        /// The font must not be destroyed while a text is using it.
        ///
        /// \param renderer   Renderer that will handle the drawing
        /// \param font       Font that will be used to render the text
        /// \param text       Text string
        /// \param position   Position where the text will be drawn (top-left corner)
        /// \param color      Text color
        /// \param renderMode Rendering mode to use when drawing the text
        /////////////////////////////////////////////////
        IKSDL_EXPORT Textf(const Renderer& renderer, const Font& font, const std::u16string& text, const Positionf& position,
                           const Color& color, RenderMode renderMode = RenderMode::Blended);

        /////////////////////////////////////////////////
        /// \brief Constructor with unicode encoding and shaded render mode
        ///
        /// \param renderer        Renderer that will handle the drawing
        /// \param font            Font that will be used to render the text
        /// \param text            Text string
        /// \param position        Position where the text will be drawn (top-left corner)
        /// \param color           Text color
        /// \param backgroundColor Color of the background rectangle
        /////////////////////////////////////////////////
        IKSDL_EXPORT Textf(const Renderer& renderer, const Font& font, const std::u16string& text, const Positionf& position,
                           const Color& color, const Color& backgroundColor);

        /////////////////////////////////////////////////
        /// \brief Move the text to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Moveement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(const Positionf& delta) { m_rect.x += delta.getX(); m_rect.y += delta.getY(); }

        /////////////////////////////////////////////////
        /// \brief Draw the text
        ///
        /// \param renderer Renderer that will handle the drawing
        /////////////////////////////////////////////////
        IKSDL_EXPORT virtual void draw(SDL_Renderer* const renderer) const;

        /////////////////////////////////////////////////
        /// \brief Get the position and size
        ///
        /// \return Current position and size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Rectf getRect() const { return Rectf(m_rect.x, m_rect.y, m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Get the position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positionf getPosition() const { return Positionf(m_rect.x, m_rect.y); }

        /////////////////////////////////////////////////
        /// \brief Get the size
        ///
        /// \return Current size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Sizef getSize() const { return Sizef(m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Change position of the text
        ///
        /// The given position defines the top-left corner of the text.
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(const Positionf& position) { m_rect.x = position.getX(); m_rect.y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the center point that is used to apply rotation
        ///
        /// \param center New center point for rotations
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setCenter(const Positionf& center);

        /////////////////////////////////////////////////
        /// \brief Change the rotation center point to default
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void resetCenter() { m_centerPtr = nullptr; };

    private:

        /////////////////////////////////////////////////
        /// \brief Change the text's rect size
        ///
        /// \param width New rect width
        /// \param height New rect height
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline virtual void setRect(int width, int height)
        {
            m_rect.w = static_cast<float>(width);
            m_rect.h = static_cast<float>(height);
        }

        SDL_FRect m_rect; ///< Position and size of the text

        SDL_FPoint m_center;     ///< Rotation center point
        SDL_FPoint* m_centerPtr; ///< Pointer to rotation center point, or nullptr to use default center
};

}

#endif // IKSDL_TEXTF_HPP
