#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Vertex.h"
#include "../Core/Graphics/Shaders/TextureShader.h"
#include "../Core/Graphics/Mesh.h"
#include "../Core/Scene/Scene.h"

namespace cr = Core;

class DemoApp : public Core::App
{
public:
	DemoApp()
		:
		App()
	{ 
		m_pWindow->setSize(sf::Vector2u(1600, 900));
		initScene();
	} 

	void updateScene(unsigned int dtime) override
	{
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	 rot.x += dtime * 0.035;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	 rot.x -= dtime * 0.035;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rot.z += dtime * 0.035;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	 rot.z -= dtime * 0.035;
		//
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.z += dtime * 0.003;
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.z -= dtime * 0.003;
	}

	void updateGraphics(unsigned int dtime) override
	{
		unsigned int fps = 1 / (static_cast<double>(dtime) / 1000);

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		m_scene.render(m_renderer);

		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", resWidth.c_str(), resHeight.c_str());
		ImGui::Text("FPS: %s", std::to_string(fps).c_str());
		ImGui::End();
	}

private:
	void initScene()
	{
		// Texture loading
		auto boxTexture  = std::make_shared<sf::Image>();
		auto metalTexture = std::make_shared<sf::Image>();
		boxTexture->loadFromFile("assets/box.jpg");
		metalTexture->loadFromFile("assets/metal.jpg");

		// Texture shader setup
		auto texShader1 = std::make_shared<cr::TextureShader>();
		auto texShader2 = std::make_shared<cr::TextureShader>();
		texShader1->bindTexture(boxTexture);
		texShader1->bindTexture(metalTexture);

		// Meshes creation
		auto cubeMesh1 = cr::Mesh::cube();
		auto cubeMesh2 = cr::Mesh::cube();

		// Entities creation
		auto cube1 = std::make_shared<cr::Entity>(cubeMesh1, cr::Vec3());
		auto cube2 = std::make_shared<cr::Entity>(cubeMesh2, cr::Vec3(2, 0, -3));

		// Attach shaders to entities
		cube1->attachShader(texShader1);
		cube2->attachShader(texShader2);

		// Insert entities to the scene;
		m_scene.add("cube1", cube1);
		m_scene.add("cube2", cube2);
	}
};
