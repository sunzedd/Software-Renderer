#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Shaders/GouraudTextureShader.h"
#include "../Core/Graphics/Shaders/PointLightShader.h"
#include "../Core/Graphics/Shaders/PointLightTextureShader.h"
#include "../Core/Scene/World.h"

namespace cr = Core;

class DemoApp_Scene : public cr::App
{
private:
	std::shared_ptr<cr::Entity> cube_entity;
	std::shared_ptr<cr::PointLightTextureShader> cube_shader;
	cr::World level;

public:
	DemoApp_Scene()
	{
		m_pWindow->setSize(sf::Vector2u(1280, 720));

		cube_shader = std::make_shared<cr::PointLightTextureShader>();
		cube_entity = std::make_shared<cr::Entity>(cr::Mesh::cube(), cube_shader);
		auto cube_tex = std::make_shared<sf::Image>();

		cube_tex->loadFromFile("assets/box.jpg");

		cr::Mat4 proj = cr::Mat4::perspective(60.0f, (float)16 / (float)9, 0.001f, 100.0f);

		cube_shader->bindProjectionMatrix(proj);
		cube_shader->bindLightPosition(cr::Vec3(0, 0, 0));
		cube_shader->bindTexture(std::move(cube_tex));

		cube_entity->setPosition(cr::Vec3(0, 0, -2));

		level.getScene().push_back(cube_entity);
	}

	void render()
	{
		m_renderer.beginFrame();

		for (auto& e : level.getScene())
			e->render(m_renderer);
	}

	void updateScene(unsigned int dtime) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		level.getScene()[0]->rotate(cr::Vec3(0, dtime * 0.035, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		level.getScene()[0]->rotate(cr::Vec3(0, -(dtime * 0.035), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	level.getScene()[0]->rotate(cr::Vec3(dtime * 0.035, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		level.getScene()[0]->rotate(cr::Vec3(-(dtime * 0.035), 0, 0));
																
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		level.getScene()[0]->move(cr::Vec3(0, 0, -(dtime * 0.003)));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		level.getScene()[0]->move(cr::Vec3(0, 0, (dtime * 0.003)));

		level.update(dtime);
	}

	void updateGraphics(unsigned int dtime) override
	{
		render();
	}
};
