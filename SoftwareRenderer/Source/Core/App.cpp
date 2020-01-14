#include "App.h"

namespace Core
{
	App::App()
		:
		m_windowProps{ DEFAULT_WIDTH, DEFAULT_HEIGHT, "App" },
		m_frameBuffer( DEFAULT_WIDTH, DEFAULT_HEIGHT ),
		m_renderer( m_frameBuffer )
	{
		createGraphics( false );
	}

	App::App( int width, int height, const std::string& title, bool fullscreen )
		:
		m_windowProps{ width, height, title },
		m_frameBuffer( width, height ),
		m_renderer( m_frameBuffer )
	{
		createGraphics( fullscreen );
	}

	App::~App()
	{ 
		ImGui::SFML::Shutdown();
	}

	void App::run()
	{
		while (m_pWindow->isOpen())
		{
			receiveWindowEvent();

			sf::Time dtime = m_timer.restart();

			ImGui::SFML::Update( *m_pWindow, dtime );
			updateScene( dtime.asMilliseconds() );
			updateGraphics( dtime.asMilliseconds() );
			updateWindow();
		}
	}

	void App::test()
	{
		m_frameBuffer.fill( Color( 0, 0, 0 ) );

		for( int i = 0; i < 100; i++ )
		{
			m_frameBuffer.setPixel( i, 100, Vec4( 0, 0, 1, 1 ) );
		}
	}

	void App::receiveWindowEvent()
	{
		while (m_pWindow->pollEvent(m_windowEvent))
		{
			if (m_windowEvent.type == sf::Event::Closed)
				m_pWindow->close();
		}

		ImGui::SFML::ProcessEvent(m_windowEvent);
	}

	void App::updateWindow()
	{
		m_backBufferTex.update( ( unsigned char* )m_frameBuffer.pixels() );
		m_pBackBufferSprite->setTexture( m_backBufferTex );
		m_pWindow->draw( *m_pBackBufferSprite );

		ImGui::SFML::Render( *m_pWindow );

		m_pWindow->display();
	}

	void App::updateScene( unsigned int dtime )
	{ }

	void App::updateGraphics( unsigned int dtime )
	{
		unsigned int fps = 1 / ( static_cast<double>(dtime) / 1000 );

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		test();

		ImGui::Begin( "Properties" );
		ImGui::Text( "Resolution: %s x %s", resWidth.c_str(), resHeight.c_str() );
		ImGui::Text( "FPS: %s", std::to_string(fps).c_str() );
		ImGui::End();
	}

	void App::createGraphics( bool fullscreen )
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

		ImGui::SFML::Init(*m_pWindow);
	}
}