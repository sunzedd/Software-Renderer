#include "Window.h"

namespace Core {

Window::Window()
	:
	m_properties({ CORE_DEFAULT_WIDTH, CORE_DEFAULT_HEIGHT, false, "CoreApp" }),
	m_frameBuffer(CORE_DEFAULT_WIDTH, CORE_DEFAULT_HEIGHT)
{
	createGraphics(m_properties.fullscreen);
}

Window::Window(int width, int height, const std::string& title, bool fullscreen)
	:
	m_properties({width, height, fullscreen, title}),
	m_frameBuffer(width, height)
{
	createGraphics(m_properties.fullscreen);
}

Window::~Window()
{
	ImGui::SFML::Shutdown();
}

void Window::update(sf::Time deltaTime)
{
	while (m_nativeWindow.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed) m_nativeWindow.close();
	}
	ImGui::SFML::ProcessEvent(m_event);
	ImGui::SFML::Update(m_nativeWindow, deltaTime);

	m_frameBufferTexture.update((sf::Uint8*)m_frameBuffer.pixels());
	m_frameBufferSprite.setTexture(m_frameBufferTexture);

	m_nativeWindow.clear();
	m_nativeWindow.draw(m_frameBufferSprite);
	ImGui::SFML::Render(m_nativeWindow);
	m_nativeWindow.display();
}

void Window::createGraphics(bool fullscreen)
{
	if (fullscreen)
	{
		m_nativeWindow.create(sf::VideoMode(m_properties.width, m_properties.height),
			m_properties.title, sf::Style::Fullscreen);
	}
	else
	{
		m_nativeWindow.create(sf::VideoMode(m_properties.width, m_properties.height),
			m_properties.title, sf::Style::Default);
	}

	m_frameBufferTexture.create(m_properties.width, m_properties.height);
	m_frameBufferSprite = sf::Sprite(m_frameBufferTexture);

	ImGui::SFML::Init(m_nativeWindow);
}

} // namespace Core