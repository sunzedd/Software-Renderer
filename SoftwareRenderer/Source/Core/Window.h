#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Graphics/FrameBuffer.h"
#include "Defines.h"

namespace Core {
class Window
{
public:
	Window();
	Window(int width, int height, const std::string& title, bool fullscreen = false);
	~Window();

	FrameBuffer& getFrameBuffer() { return m_frameBuffer; }
	sf::Event&   getEvent() { return m_event; }

	bool isOpen() const { return m_nativeWindow->isOpen(); }
	void update(sf::Time deltaTime);

private:
	void createGraphics(bool fullscreen);

	sf::Event m_event;

	struct 
	{
		int			width;
		int			height;
		bool		fullscreen;
		std::string title;
	}
	m_properties;

	std::unique_ptr<sf::RenderWindow> m_nativeWindow;
	FrameBuffer					m_frameBuffer;
	sf::Texture					m_frameBufferTexture;
	std::unique_ptr<sf::Sprite> m_frameBufferSprite;
};
} // namespace Core