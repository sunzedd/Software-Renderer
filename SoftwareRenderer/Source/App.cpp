#include "App.h"

namespace Core
{
	App::App()
		:
		m_windowProps{ DEFAULT_WIDTH, DEFAULT_HEIGHT, "App" },
		m_frameBuffer( DEFAULT_WIDTH, DEFAULT_HEIGHT )
	{
		createGraphics( false );
	}

	App::App( int width, int height, const std::string& title, bool fullscreen )
		:
		m_windowProps{ width, height, title },
		m_frameBuffer( width, height )
	{
		createGraphics( fullscreen );
	}

	App::~App()
	{ }

	void App::run()
	{
		while (m_pWindow->isOpen())
		{
			receiveWindowEvent();

			updateScene();
			updateGraphics();
			updateWindow();
		}
	}

	void App::test()
	{
		m_frameBuffer.fill( Color( 255, 0, 0 ) );
	}

	void App::receiveWindowEvent()
	{
		m_pWindow->pollEvent( m_windowEvent );
		
		if( m_windowEvent.type == sf::Event::Closed )
		{
			m_pWindow->close();
		}
	}

	void App::updateWindow()
	{
		m_backBufferTex.update( ( unsigned char* )m_frameBuffer.pixels() );
		m_pBackBufferSprite->setTexture( m_backBufferTex );
		m_pWindow->draw( *m_pBackBufferSprite );
		m_pWindow->display();
	}

	void App::updateScene()
	{

	}

	void App::updateGraphics()
	{
		test();
	}

	void App::createGraphics(bool fullscreen)
	{
		if( fullscreen )
		{
			m_pWindow = std::make_unique<sf::RenderWindow>(
				sf::VideoMode(m_windowProps.width, m_windowProps.height),
				m_windowProps.title, sf::Style::Fullscreen );
		}
		else
		{
			m_pWindow = std::make_unique<sf::RenderWindow>(
				sf::VideoMode(m_windowProps.width, m_windowProps.height),
				m_windowProps.title, sf::Style::Default );
		}

		
		m_backBufferTex.create( m_windowProps.width, m_windowProps.height );
		m_pBackBufferSprite = std::make_unique<sf::Sprite>( m_backBufferTex );

		if (!m_pWindow) throw Exception( "Could not create window" );
		if (!m_pBackBufferSprite) throw Exception( "Could not create backbuffer sprite" );
	}
}