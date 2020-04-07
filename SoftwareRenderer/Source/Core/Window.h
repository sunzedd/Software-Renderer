#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Defines.h"
#include "Exceptions.h"
#include "Graphics/FrameBuffer.h"

namespace core {

class Window
{
    struct _Properties
    {
        int width;
        int height;
        bool fullscreen;
        std::string title;
    };

    struct _GraphicContext
    {
        FrameBuffer       frameBufferObject;
        sf::RenderWindow  nativeWindow;
        sf::Texture       frameBufferTexture;
        sf::Sprite        frameBufferSprite;
        sf::Text          fpsLabel;

        _GraphicContext(int width, int height);
        void init(const _Properties& props);
        void update(unsigned int fps);
    };

public:
    Window();
    Window(int width, int height, const std::string& title, bool fullscreen = false);
    ~Window();

    FrameBuffer& getFrameBuffer();
    bool isOpen() const;

    void pollEvent(sf::Event& e);
    void update(sf::Time deltaTime);

private:
    void createGraphics();

private:
    _Properties m_properties;
    _GraphicContext m_graphics;

    sf::Event m_event;
    sf::Font m_font;
};

} // namespace core
