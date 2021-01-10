#include "Window.h"

namespace core {

Window::Window()
    :
    m_properties({ CORE_DEFAULT_WIDTH, CORE_DEFAULT_HEIGHT, false, "CoreApp" }),
    m_graphics(CORE_DEFAULT_WIDTH, CORE_DEFAULT_HEIGHT)
{
    createGraphics();
}

Window::Window(int width, int height, const std::string& title, bool fullscreen)
    :
    m_properties({width, height, fullscreen, title}),
    m_graphics(width, height)
{
    createGraphics();
}

Window::~Window()
{
    ImGui::SFML::Shutdown();
}

FrameBuffer& Window::getFrameBuffer()
{
    return m_graphics.frameBufferObject;
}

bool Window::isOpen() const
{
    return m_graphics.nativeWindow.isOpen();
}

void Window::pollEvent(sf::Event& e)
{
    while (m_graphics.nativeWindow.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_graphics.nativeWindow.close();
    }
}

void Window::update(sf::Time deltaTime)
{
    int fps = 1000 / static_cast<float>(deltaTime.asMilliseconds());
    m_graphics.update(fps);
}


void Window::createGraphics()
{
    m_graphics.init(m_properties);

    if (!m_font.loadFromFile("Resources\\font.ttf"))
    {
        throw CouldNotLoadAssetException("Could not find font file 'font.ttf' \
                                          in Resources folder");
    }
    m_graphics.fpsLabel.setFont(m_font);

    ImGui::SFML::Init(m_graphics.nativeWindow); 
}



// ****************************** Graphics Context **************************************
Window::_GraphicsContext::_GraphicsContext(int width, int height)
    :
    frameBufferObject(width, height)
{}

void Window::_GraphicsContext::init(const _Properties& props)
{
    if (props.fullscreen)
    {
        nativeWindow.create(sf::VideoMode(props.width, props.height),
            props.title, sf::Style::Fullscreen);
    }
    else
    {
        nativeWindow.create(sf::VideoMode(props.width, props.height),
            props.title, sf::Style::Default);
    }

    frameBufferTexture.create(props.width, props.height);
    frameBufferSprite = sf::Sprite(frameBufferTexture);
}

void Window::_GraphicsContext::update(unsigned int fps)
{
    frameBufferTexture.update((sf::Uint8*)frameBufferObject.pixels());
    frameBufferSprite.setTexture(frameBufferTexture);
    fpsLabel.setString(std::to_string(fps));

    nativeWindow.clear();
    nativeWindow.draw(frameBufferSprite);
    nativeWindow.draw(fpsLabel);
    nativeWindow.display();
}

} // namespace core
