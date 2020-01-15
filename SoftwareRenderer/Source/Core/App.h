#pragma once
#include <string>
#include <memory>
#include <exception>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Graphics/FrameBuffer.h"
#include "Graphics/RenderPipeline.h"

#include "Scene/Scene.h"

#define DEFAULT_WIDTH  800
#define DEFAULT_HEIGHT 600

namespace Core 
{
	class App 
	{
	public:
		class Exception : public std::exception 
		{
		public:
			Exception(const std::string& msg)
				:
				exception(msg.c_str()) { }
		};

	public:
		App();
		App( int width, int height, const std::string& title, bool fullscreen );
		virtual ~App();

		void run();

	protected:
		virtual void receiveWindowEvent();
		virtual void updateScene( unsigned int dtime );
		virtual void updateGraphics( unsigned int dtime );

	private:
		void updateWindow();
		void createGraphics( bool fullscreen );
	
	protected:
		struct 
		{
			int width;
			int height;
			std::string title;
		}
		m_windowProps;

		std::unique_ptr<sf::RenderWindow> m_pWindow;
		FrameBuffer m_frameBuffer;
		sf::Texture m_backBufferTex;
		std::unique_ptr<sf::Sprite> m_pBackBufferSprite;

		sf::Event m_windowEvent;
		sf::Clock m_timer;

		Scene m_scene;

		RenderPipeline m_renderer;
	};
}