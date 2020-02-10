#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Shaders/GouraudTextureShader.h"
#include "../Core/Graphics/Shaders/PointLightShader.h"
#include "../Core/Graphics/Shaders/PointLightTextureShader.h"
#include "../Core/World/World.h"
#include "../Core/World/Camera.h"

namespace cr = Core;

class DemoApp_Camera : public cr::App
{
private:
	std::shared_ptr<cr::Entity> cube_entity;
	std::shared_ptr<cr::PointLightTextureShader> cube_shader;
	cr::World level;
	cr::Camera camera;

public:
	DemoApp_Camera()
	{
		m_pWindow->setSize(sf::Vector2u(1280, 720));

		cube_shader = std::make_shared<cr::PointLightTextureShader>();
		cube_entity = std::make_shared<cr::Entity>(cr::Mesh::cube(), cube_shader);
		auto cube_tex = std::make_shared<sf::Image>();

		cube_tex->loadFromFile("assets/box.jpg");

		// camera 
		camera.setup(45.0f, 0.001f, 100.0f, 16.0f / 9.0f);
		cube_shader->bindProjectionMatrix(camera.getProjMatrix());
		cube_shader->bindViewMatrix(camera.getViewMatrix());

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
		float dRot = dtime * 0.035;
		float dMove = dtime * 0.003;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		level.getScene()[0]->rotate(cr::Vec3(0, dRot, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		level.getScene()[0]->rotate(cr::Vec3(0, -(dRot), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	level.getScene()[0]->rotate(cr::Vec3(dRot, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		level.getScene()[0]->rotate(cr::Vec3(-(dRot), 0, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		camera.move(cr::Direction::Left, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		camera.move(cr::Direction::Right, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		camera.move(cr::Direction::Forward, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		camera.move(cr::Direction::Backward, dMove);

		// mouse movement
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			static int lastMouseX = sf::Mouse::getPosition().x;
			static int lastMouseY = sf::Mouse::getPosition().y;
			
			int curMouseX = sf::Mouse::getPosition().x;
			int curMouseY = sf::Mouse::getPosition().y;
		
			camera.rotate(cr::Vec2(lastMouseX - curMouseX, lastMouseY - curMouseY));

			lastMouseX = curMouseX;
			lastMouseY = curMouseY;
		}

		level.update(dtime);
		camera.update(dtime);
	}

	void updateGraphics(unsigned int dtime) override
	{
		cube_shader->bindViewMatrix(camera.getViewMatrix());

		render();
	}
};
