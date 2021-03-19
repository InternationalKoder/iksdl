[![Zlib License](https://img.shields.io/badge/license-Zlib-brightgreen.svg)](https://opensource.org/licenses/Zlib)

# IKSDL

IKSDL is a C++ wrapper for the SDL 2 library and its commonly used extensions: SDL_image, SDL_ttf and SDL_mixer.
Its intent is to provide a clear and safe API for an easy use of the SDL features.
It is written using a modern C++ approach (C++20 support is required).
Attention is focused on performance so that the use of IKSDL adds minimum cost compared to a direct use of SDL 2.

IKSDL is available under the terms of the Zlib license.

## Usage

Since IKSDL uses modern C++20 features, some compilers that have not implemented these features yet may not be able to build it.

The following libraries are required in order to compile IKSDL itself or any program using it:
* SDL 2.0
* SDL_image 2.0
* SDL_ttf 2.0
* SDL_mixer 2.0

Here is an example of a small program using IKSDL:

```c++
#include <iksdl.hpp>

class BasicHandler : public iksdl::EventHandler
{
    public:

        BasicHandler() : m_close(false) {}
        
        inline virtual void handleQuitEvent(const iksdl::QuitEvent&) { m_close = true; }
        
        inline virtual void handleWindowEvent(const iksdl::WindowEvent& event)
        {
            if(event.getType() == iksdl::WindowEvent::Type::Close)
                m_close = true;
        }
        
        inline virtual void handleKeyboardEvent(const iksdl::KeyboardEvent& event) {}
        inline virtual void handleMouseMotionEvent(const iksdl::MouseMotionEvent& event) {}
        inline virtual void handleMouseButtonEvent(const iksdl::MouseButtonEvent& event) {}
        inline virtual void handleMouseWheelEvent(const iksdl::MouseWheelEvent& event) {}
        
        inline bool isClose() const { return m_close; }
    
    private:
    
        bool m_close;
};

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    iksdl::Window window("Example", iksdl::Sizei(800, 600));
    
    iksdl::Texture characterTexture(window, "character.png");
    iksdl::Sprite character(characterTexture, iksdl::Positioni(150, 300));

    BasicHandler handler;

    while(true)
    {
        while(const iksdl::Event event = window.pollEvent())
            event.play(handler);

        if(handler.isClose())
            return EXIT_SUCCESS;

        window.clear();
        window.draw(character);
        window.display();
    }

    return EXIT_FAILURE;
}
```

## Documentation

Full documentation is available at http://internationalkoder.github.io/iksdl.

It is also present in HTML in the `doc/` folder.

## Contribute

IKSDL doesn't cover all the features that SDL 2 offers. Feel free to suggest your contributions, as long as:
* It complies with the nature of the project, which is to be a simple wrapper over SDL features
* It respects the existing code style
