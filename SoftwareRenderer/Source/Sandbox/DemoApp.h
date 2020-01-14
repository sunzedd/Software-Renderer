#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Vertex.h"

class DemoApp : public Core::App
{
private:
	std::vector<Core::Vertex> m_vertexBuffer;
	std::vector<unsigned short> m_indexBuffer;

public:
	DemoApp()
		:
		App()
	{ 
		m_pWindow->setSize(sf::Vector2u(1280, 720));

		m_vertexBuffer = 
		{
			//  pos		  // normal	    // uv	// color
			{ { 0, 0, 0}, {0, 0, 0, 1}, {0, 0}, {1, 0, 0, 1} },
			{ { 0, 0, 0}, {0, 0, 0, 1}, {0, 0}, {1, 0, 0, 1} },
			{ { 0, 0, 0}, {0, 0, 0, 1}, {0, 0}, {1, 0, 0, 1} }
		};

		m_indexBuffer =
		{
			0, 1, 2
		};
	} 

	void render()
	{
		//m_renderer.run(m_vertexBuffer, m_indexBuffer);
	}

	void updateGraphics(unsigned int dtime) override
	{
		unsigned int fps = 1 / (static_cast<double>(dtime) / 1000);

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		render();

		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", resWidth.c_str(), resHeight.c_str());
		ImGui::Text("FPS: %s", std::to_string(fps).c_str());
		ImGui::End();
	}
};