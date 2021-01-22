#pragma once
#include <string>
#include <memory>
#include <exception>
#include <SFML/Graphics.hpp>
//#include <imgui.h>
//#include <imgui-SFML.h>

#include "Graphics/Renderer.h"
#include "Window.h"

namespace core {

class App 
{
public:
    App();
    App(int width, int height, const std::string& title, bool fullscreen);
    virtual ~App();

    void run();

protected:
    virtual void update(unsigned int dtime) = 0;
    virtual void render() = 0;

protected:
    Window m_window;
    sf::Event m_event;
    sf::Clock m_timer;
};

} // namespace core
