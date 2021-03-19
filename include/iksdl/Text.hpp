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

#ifndef IKSDL_TEXT_HPP
#define IKSDL_TEXT_HPP

#include "iksdl/Color.hpp"
#include "iksdl/Drawable.hpp"
#include "iksdl/Position.hpp"
#include "iksdl/Rect.hpp"
#include "iksdl/Size.hpp"
#include "iksdl_export.hpp"
#include <SDL.h>
#include <string>
#include <optional>
#include <vector>

extern "C"
{
struct SDL_Texture;
struct SDL_Surface;
}

namespace iksdl
{

class Renderer;
class Font;

/////////////////////////////////////////////////
/// \brief A text that can be drawn
/////////////////////////////////////////////////
class Text : public Drawable
{
    public:

        /////////////////////////////////////////////////
        /// \brief Available string encodings
        ///
        /// Unicode is also available, but is handled through specific methods.
        /////////////////////////////////////////////////
        enum class Encoding { Latin1, Utf8 };

        /////////////////////////////////////////////////
        /// \brief Available rendering modes
        ///
        /// * Solid is the fastest but has lowest quality
        /// * Blended is best quality but slowest
        ///
        /// Shaded is also available, but handled through specific methods.
        /// It is best quality and quite fast, but has a background rectangle.
        /////////////////////////////////////////////////
        enum class RenderMode { Solid, Blended };

        /////////////////////////////////////////////////
        /// \brief Flipping modes for text
        /////////////////////////////////////////////////
        enum class Flip { None, Horizontal, Vertical, Both };

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
        IKSDL_EXPORT Text(const Renderer& renderer, const Font& font, std::string text, const Positioni& position,
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
        IKSDL_EXPORT Text(const Renderer& renderer, const Font& font, std::string text, const Positioni& position,
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
        IKSDL_EXPORT Text(const Renderer& renderer, const Font& font, const std::u16string& text, const Positioni& position,
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
        IKSDL_EXPORT Text(const Renderer& renderer, const Font& font, const std::u16string& text, const Positioni& position,
                          const Color& color, const Color& backgroundColor);

        /////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////
        IKSDL_EXPORT ~Text();

        /////////////////////////////////////////////////
        /// \brief Move the text to another position
        ///
        /// The movement is relative to the current position.
        ///
        /// \param delta Moveement to apply
        ///
        /// \see setPosition
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void move(const Positioni& delta) { m_rect.x += delta.getX(); m_rect.y += delta.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the size by using a scale factor
        ///
        /// The scaling is relative to the current size.
        ///
        /// \param delta Scaling factor to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT void scale(const Sizef& delta);

        /////////////////////////////////////////////////
        /// \brief Rotate the text
        ///
        /// The rotation is relative to the current orientation.
        ///
        /// \param delta Angle difference to apply
        ///
        /// \see setRotation
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void rotate(double delta) { m_rotation += delta; }

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
        IKSDL_EXPORT inline Recti getRect() const { return Recti(m_rect.x, m_rect.y, m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Get the position
        ///
        /// \return Current position
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Positioni getPosition() const { return Positioni(m_rect.x, m_rect.y); }

        /////////////////////////////////////////////////
        /// \brief Get the size
        ///
        /// \return Current size
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline Sizei getSize() const { return Sizei(m_rect.w, m_rect.h); }

        /////////////////////////////////////////////////
        /// \brief Change position of the text
        ///
        /// The given position defines the top-left corner of the text.
        ///
        /// \param position New position
        ///
        /// \see move
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setPosition(const Positioni& position) { m_rect.x = position.getX(); m_rect.y = position.getY(); }

        /////////////////////////////////////////////////
        /// \brief Change the rotation of the sprite
        ///
        /// \param rotation New rotation
        ///
        /// \see rotate
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setRotation(double rotation) { m_rotation = rotation; }

        /////////////////////////////////////////////////
        /// \brief Change the center point that is used to apply rotation
        ///
        /// \param center New center point for rotations
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setCenter(const Positioni& center);

        /////////////////////////////////////////////////
        /// \brief Flip the text
        ///
        /// \param flip Type of flip to apply
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setFlip(Flip flip);

        /////////////////////////////////////////////////
        /// \brief Change the text string for Latin1 or UTF-8 encodings
        ///
        /// Initial encoding and render mode are preserved.
        ///
        /// In the case of shaded rendering, the background color is also preserved.
        ///
        /// \param text New text string
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setText(std::string text);

        // Encoding = Unicode ; keep initial RenderMode, with the same background color in the case of shaded rendering
        /////////////////////////////////////////////////
        /// \brief Change the text string for Unicode encoding
        ///
        /// Initial render mode is preserved.
        ///
        /// In the case of shaded rendering, the background color is also preserved.
        ///
        /// \param text New text string
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setText(const std::u16string& text);

        /////////////////////////////////////////////////
        /// \brief Change font that is used to render the text
        ///
        /// \param font New font
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void setFont(const Font& font) { m_font = &font; refreshTexture(); }

        /////////////////////////////////////////////////
        /// \brief Change text color
        ///
        /// \param color New text color
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setColor(const Color& color);

        /////////////////////////////////////////////////
        /// \brief Change background rectangle color
        ///
        /// This method sets the render mode to shaded.
        ///
        /// \param backgroundColor New background color
        /////////////////////////////////////////////////
        IKSDL_EXPORT void setBackgroundColor(const Color& backgroundColor);

        /////////////////////////////////////////////////
        /// \brief Remove the background color by changing the render mode if it was shaded
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void removeBackgroundColor() { m_backgroundColor = std::nullopt; refreshTexture(); }

        /////////////////////////////////////////////////
        /// \brief Change the rotation center point to default
        /////////////////////////////////////////////////
        IKSDL_EXPORT inline void resetCenter() { m_centerPtr = nullptr; };

    private:

        static constexpr std::string_view CREATE_TEXT_FAILURE = "Failed to create a text from font. Cause: ";
        static constexpr std::string_view CREATE_TEXTURE_FAILURE = "Failed to create a texture from text. Cause: ";

        /////////////////////////////////////////////////
        /// \brief Generate the text to render with current parameters
        /////////////////////////////////////////////////
        IKSDL_EXPORT void refreshTexture();

        /////////////////////////////////////////////////
        /// \brief Transform a string from unicode to an array of numbers
        ///
        /// \param str String to transform
        ///
        /// \return Same string as numbers
        /////////////////////////////////////////////////
        IKSDL_EXPORT static std::vector<uint16_t> convertUnicodeString(const std::u16string& str);

        const Renderer* const m_renderer;                   ///< Renderer for the text
        const Font* m_font;                                 ///< Text font
        SDL_Color m_color;                                  ///< Text color
        std::optional<SDL_Color> m_backgroundColor;         ///< Background color when using shaded rendering
        Encoding m_encoding;                                ///< Encoding when not unicode
        RenderMode m_renderMode;                            ///< Rendering mode
        std::optional<std::string> m_text;                  ///< Text string when encoding is not unicode
        std::optional<std::vector<uint16_t>> m_unicodeText; ///< Unicode text string as numbers

        SDL_Texture* m_texture; ///< SDL texture holding the rendered text
        SDL_Rect m_rect;        ///< Position and size of the text

        Sizef m_scale;           ///< Text scale
        double m_rotation;       ///< Text rotation
        SDL_Point m_center;      ///< Rotation center point
        SDL_Point* m_centerPtr;  ///< Pointer to rotation center point, or nullptr to use default center
        SDL_RendererFlip m_flip; ///< Flip the text when drawing
};

}

#endif // IKSDL_TEXT_HPP
