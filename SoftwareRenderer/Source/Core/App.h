#pragma once
#include <string>
#include <memory>
#include <exception>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Graphics/FrameBuffer.h"
#include "Graphics/RenderPipeline.h"
#include "Window.h"

#define DEFAULT_WIDTH  800
#define DEFAULT_HEIGHT 600

namespace Core {
class App 
{
public:
	class Exception;

	App();
	App(int width, int height, const std::string& title, bool fullscreen);
	virtual ~App();

	void run();

protected:
	virtual void update(unsigned int dtime);
	virtual void render(unsigned int dtime);

protected:
	Window m_window;
	sf::Event& m_windowEvent;
	sf::Clock m_timer;
	RenderPipeline m_renderer;
};

class App::Exception : public std::exception
{
public:
	Exception(const std::string& msg)
		:
		exception(msg.c_str()) { }
};
} // namespace Core