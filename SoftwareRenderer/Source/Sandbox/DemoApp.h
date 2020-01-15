#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Vertex.h"
#include "../Core/Graphics/Shaders/DefaultShader.h"

namespace cr = Core;

class DemoApp : public Core::App
{
private:
	std::vector<cr::Vertex> vertexBuffer;
	std::vector<unsigned short> indexBuffer;
	std::shared_ptr<cr::IShaderProgram> shader;

	cr::Vec3 rot;
	cr::Vec3 pos = {0, 0, -3};

public:
	DemoApp()
		:
		App()
	{ 
		m_pWindow->setSize(sf::Vector2u(1280, 720));

		vertexBuffer =  
		{
			//  pos		  // normal	    // uv	// color
			{ {  0,    0.5, 0 },  { 0, 0, 0, 0 }, { 0, 0 }, { 1, 0, 0, 1 } },
			{ {  0.5, -0.5, 0 },  { 0, 0, 0, 0 }, { 0, 0 }, { 0, 1, 0, 1 } },
			{ { -0.5, -0.5, 0 },  { 0, 0, 0, 0 }, { 0, 0 }, { 0, 0, 1, 1 } }
		};

		indexBuffer =
		{
			2, 1, 0
		};

		shader = std::make_shared<cr::DefaultShader>();

		std::dynamic_pointer_cast<cr::DefaultShader>(shader)->bindViewMatrix(cr::Mat4());
		std::dynamic_pointer_cast<cr::DefaultShader>(shader)->bindProjectionMatrix(cr::Mat4::perspective(50.0f, 16.0 / 9.0, 0.1, 10.0f));
	} 

	void render()
	{
		m_renderer.bindShaderProgram(shader);
		m_renderer.wireframeRendering(false);
		m_renderer.backFaceCulling(false);

		cr::Mat4 rotM = cr::Mat4::rotationX(rot.x) * cr::Mat4::rotationY(rot.y) * cr::Mat4::rotationZ(rot.z);
		cr::Mat4 posM = cr::Mat4::translation(pos);

		cr::Mat4 modelM = rotM * posM;
		std::dynamic_pointer_cast<cr::DefaultShader>( shader )->bindModelMatrix( modelM );

		m_renderer.beginFrame();
		m_renderer.run(vertexBuffer, indexBuffer);
	}

	void updateScene(unsigned int dtime) override
	{
		rot.x += dtime * 0.05;
		rot.y += dtime * 0.05;
		rot.z += dtime * 0.05;
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