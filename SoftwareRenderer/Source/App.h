#pragma once
#include <string>
#include <memory>
#include <exception>
#include <SFML/Graphics.hpp>

#include "Graphics/FrameBuffer.h"

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
		void test();

	protected:
		void receiveWindowEvent();
		void updateWindow();
		virtual void updateScene();
		virtual void updateGraphics();

	private:
		void createGraphics( bool fullscreen );
	
	protected:
		struct 
		{
			int width;
			int height;
			std::string title;
		} m_windowProps;

		std::unique_ptr<sf::RenderWindow> m_pWindow;
		FrameBuffer m_frameBuffer;
		sf::Texture m_backBufferTex;
		std::unique_ptr<sf::Sprite> m_pBackBufferSprite;

		sf::Event m_windowEvent;
	};
}