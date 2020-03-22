#include "App.h"

namespace core {

App::App()
	:
	m_window()
{
	RenderManager::initRenderSystem(m_window);
}

App::App(int width, int height, const std::string& title, bool fullscreen)
	:
	m_window(width, height, title, fullscreen)
{
	RenderManager::initRenderSystem(m_window);
}

App::~App()
{}

void App::run()
{
	while (m_window.isOpen())
	{
		sf::Time dtime = m_timer.restart();
		m_event = sf::Event();

		update(dtime.asMilliseconds());
		render();
		m_window.pollEvent(m_event);
		m_window.update(dtime);
	}
}

} // namespace core
