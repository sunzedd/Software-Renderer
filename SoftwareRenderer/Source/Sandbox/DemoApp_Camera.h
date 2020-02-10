#pragma once
#include "../Core/App.h"
#include "../Core/Graphics/Shaders/GouraudTextureShader.h"
#include "../Core/Graphics/Shaders/PointLightShader.h"
#include "../Core/Graphics/Shaders/PointLightTextureShader.h"
#include "../Core/AssetsLoader.h"
#include "../Core/World/World.h"
#include "../Core/World/Camera.h"

namespace cr = Core;

class DemoApp_Camera : public cr::App
{
private:
	cr::World level;
	cr::Camera camera;

	std::shared_ptr<cr::PointLightTextureShader> tex_shader;
	std::shared_ptr<cr::PointLightShader> color_shader;

public:
	DemoApp_Camera()
	{
		m_pWindow->setSize(sf::Vector2u(1024, 768));
		initScene();

		m_renderer.backFaceCulling(true);
		m_renderer.wireframeRendering(false);
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
		
		color_shader->bindLightPosition(camera.getPosition());
		tex_shader->bindLightPosition(camera.getPosition());
	}

	void updateGraphics(unsigned int dtime) override
	{
		color_shader->bindLightPosition(camera.getPosition());
		tex_shader->bindLightPosition(camera.getPosition());

		color_shader->bindViewMatrix(camera.getViewMatrix());
		tex_shader->bindViewMatrix(camera.getViewMatrix());

		render();
	}

	void initScene()
	{
		// camera
		camera.setPosition(cr::Vec3(0, 0, 3));

		// meshes
		auto cube_mesh = cr::Mesh::cube();
		auto sphere_mesh = cr::AssetsLoader::loadMesh("assets/sphere.obj");

		// textures
		auto cube_texture = cr::AssetsLoader::loadImage("assets/box.jpg");
		
		// shaders
		tex_shader = std::make_shared<cr::PointLightTextureShader>();
		color_shader = std::make_shared<cr::PointLightShader>();

		tex_shader->bindTexture(cube_texture);
		tex_shader->bindProjectionMatrix(camera.getProjMatrix());
		color_shader->bindProjectionMatrix(camera.getProjMatrix());

		// entities
		auto cube1 = std::make_shared<cr::Entity>(cube_mesh, tex_shader);
		auto cube2 = std::make_shared<cr::Entity>(cube_mesh, color_shader);
		auto sphere = std::make_shared<cr::Entity>(sphere_mesh, color_shader);

		cube1->setPosition(cr::Vec3(2, 0, -7));
		cube2->setPosition(cr::Vec3(-2, 0, -7));
		sphere->setPosition(cr::Vec3(0, 0, -5));
		
		// light
		color_shader->bindLightPosition(camera.getPosition());
		tex_shader->bindLightPosition(camera.getPosition());

		level.getScene().push_back(cube1);
		level.getScene().push_back(cube2);
		level.getScene().push_back(sphere);
	}
};
