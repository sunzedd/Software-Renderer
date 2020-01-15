#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Vertex.h"
#include "../Core/Graphics/Shaders/TextureShader.h"
#include "../Core/Graphics/Mesh.h"

namespace cr = Core;

class DemoApp : public Core::App
{
private:
	std::shared_ptr<cr::Mesh> cubeMesh1;
	std::shared_ptr<sf::Image> boxTexture;
	std::shared_ptr<cr::TextureShader> texShader;
	cr::Vec3 rot;
	cr::Vec3 pos = cr::Vec3(0, 0, -2);
	
public:
	DemoApp()
		:
		App()
	{ 
		m_pWindow->setSize(sf::Vector2u(1600, 900));
		initScene();
	} 

	void render()
	{
		m_renderer.beginFrame();
		cubeMesh1->render(m_renderer);
	}

	void updateScene(unsigned int dtime) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	 rot.x += dtime * 0.035;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	 rot.x -= dtime * 0.035;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rot.z += dtime * 0.035;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	 rot.z -= dtime * 0.035;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.z -= dtime * 0.003;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.z += dtime * 0.003;

		cr::Mat4 position = cr::Mat4::translation(pos);
		cr::Mat4 rotation = cr::Mat4::rotationXYZ(rot);
		cr::Mat4 scale;
		cr::Mat4 model = scale * rotation * position;

		texShader->bindModelMatrix(model);
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

private:
	void initScene()
	{
		// Texture loading
		boxTexture  = std::make_shared<sf::Image>();
		boxTexture->loadFromFile("assets/box.jpg");

		// Texture shader setup
		texShader = std::make_shared<cr::TextureShader>();
		texShader->bindTexture(boxTexture);

		// Meshes creation
		cubeMesh1 = cr::Mesh::cube();

		m_renderer.bindShaderProgram(texShader);

		texShader->bindProjectionMatrix(cr::Mat4::perspective(45.0f, 16.0f / 9.0f, 0.0001, 100.0f));
		texShader->bindViewMatrix(cr::Mat4());
	}
};
