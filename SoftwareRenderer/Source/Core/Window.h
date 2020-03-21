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
	struct _Properties
	{
		int	width;
		int	height;
		bool fullscreen;
		std::string title;
	};

public:
	Window();
	Window(int width, int height, const std::string& title, bool fullscreen = false);
	~Window();

	FrameBuffer& getFrameBuffer() { return m_frameBuffer; }
	const sf::Event& getEvent() const { return m_event; }

	bool isOpen() const { return m_nativeWindow.isOpen(); }
	void update(sf::Time deltaTime);

private:
	void createGraphics(bool fullscreen);

private:
	_Properties	m_properties;

	FrameBuffer m_frameBuffer;
	
	sf::RenderWindow m_nativeWindow;
	sf::Texture m_frameBufferTexture;
	sf::Sprite m_frameBufferSprite;

	sf::Event m_event;
};

} // namespace Core