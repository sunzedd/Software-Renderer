#pragma once
#include "../Core/App.h"
#include "../Core/Scene/Entity.h"
#include "../Core/Graphics/Shaders/GouraudTextureShader.h"

namespace cr = Core;

class DemoApp_Entities : public cr::App
{
private:
	std::shared_ptr<cr::Entity> cube_entity;
	std::shared_ptr<cr::GouraudTextureShader> cube_shader;

public:
	DemoApp_Entities()
	{
		m_pWindow->setSize(sf::Vector2u(1600, 900));

		cube_shader = std::make_shared<cr::GouraudTextureShader>();
		cube_entity = std::make_shared<cr::Entity>(cr::Mesh::cube(), cube_shader);
		std::shared_ptr<sf::Image> cube_tex = std::make_shared<sf::Image>();

		cube_tex->loadFromFile("assets/box.jpg");

		cr::Mat4 proj = cr::Mat4::perspective(60.0f, (float)16 / (float)9, 0.001f, 100.0f);

		cube_shader->bindProjectionMatrix(proj);
		cube_shader->bindLightDirection(cr::Vec3(0, 0, 1));
		cube_shader->bindTexture(cube_tex);

		cube_entity->setPosition(cr::Vec3(0, 0, -2));
	}

	void render()
	{
		m_renderer.beginFrame();
		cube_entity->render(m_renderer);
	}

	void updateScene(unsigned int dtime) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		cube_entity->rotate(cr::Vec3(0, dtime * 0.035, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		cube_entity->rotate(cr::Vec3(0, -(dtime * 0.035), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	cube_entity->rotate(cr::Vec3(dtime * 0.035, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		cube_entity->rotate(cr::Vec3(-(dtime * 0.035), 0, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		cube_entity->move(cr::Vec3(0, 0, -(dtime * 0.003)));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		cube_entity->move(cr::Vec3(0, 0,  (dtime * 0.003)));
	}

	void updateGraphics(unsigned int dtime) override
	{
		render();
	}
};