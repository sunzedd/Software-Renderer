#include "App.h"

namespace Core {

App::App()
	:
	m_window(),
	m_renderer(m_window.getFrameBuffer())
{}

App::App(int width, int height, const std::string& title, bool fullscreen)
	:
	m_window(width, height, title, fullscreen),
	m_renderer(m_window.getFrameBuffer())
{}

App::~App()
{}

void App::run()
{
	while (m_window.isOpen())
	{
		sf::Time dtime = m_timer.restart();
		m_event = sf::Event();

		update(dtime.asMilliseconds());
		render(dtime.asMilliseconds());
		m_window.pollEvent(m_event);
		m_window.update(dtime);
	}
}

} // namespace Core