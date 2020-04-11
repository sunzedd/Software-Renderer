#include "App.h"

namespace core {

App::App()
    :
    m_window()
{
    Renderer::create(m_window);
    m_timer.reset(Timer::getInstance());
}

App::App(int width, int height, const std::string& title, bool fullscreen)
    :
    m_window(width, height, title, fullscreen)
{
    Renderer::create(m_window);
    m_timer.reset(Timer::getInstance());
}

App::~App()
{
    Renderer::destroy();
}

void App::run()
{
    while (m_window.isOpen())
    {
        m_timer->restart();
        m_event = sf::Event(); // refresh event
        m_window.pollEvent(m_event);

        update(m_timer->deltaTimeMiliseconds());
        render();
        m_window.update(m_timer->deltaTimeMiliseconds());
    }
}

} // namespace core
