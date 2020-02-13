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
	std::shared_ptr<cr::DefaultShader> li_shader;

	std::shared_ptr<cr::Entity> li;

public:
	DemoApp_Camera()
		:
		App(1024, 768, "Demo", false)
	{
		initScene();

		m_renderer.backFaceCulling(true);
		m_renderer.wireframeRendering(false);
	}

	void render()
	{
		m_renderer.beginFrame();

		for (auto& e : level.getScene())
			e->render(m_renderer);

		li->render(m_renderer);
	}

	void updateScene(unsigned int dtime) override
	{
		float dRot = dtime * 0.035;
		float dMove = dtime * 0.003;

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		level.getScene()[0]->rotate(cr::Vec3(0, dRot, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		level.getScene()[0]->rotate(cr::Vec3(0, -(dRot), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	level.getScene()[0]->rotate(cr::Vec3(dRot, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		level.getScene()[0]->rotate(cr::Vec3(-(dRot), 0, 0));
		*/

		// li
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		li->move(cr::Vec3(0, dMove, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		li->move(cr::Vec3(0, -(dMove), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	li->move(cr::Vec3(dMove, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		li->move(cr::Vec3(-dMove, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))	li->move(cr::Vec3(0, 0, -(dMove)));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))		li->move(cr::Vec3(0, 0, (dMove)));

		// camera
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		camera.move(cr::Direction::Left, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		camera.move(cr::Direction::Right, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		camera.move(cr::Direction::Forward, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		camera.move(cr::Direction::Backward, dMove);


		// rotate sphere
		level.getScene()[2]->rotate(cr::Vec3(dMove * 3, dMove * 3, dMove * 3));

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
		color_shader->bindLightPosition(li->getPosition());
		tex_shader->bindLightPosition(li->getPosition());

		color_shader->bindViewMatrix(camera.getViewMatrix());
		tex_shader->bindViewMatrix(camera.getViewMatrix());
		li_shader->bindViewMatrix(camera.getViewMatrix());

		render();

		// GUI
		unsigned int fps = 1 / (static_cast<double>(dtime) / 1000);

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", resWidth.c_str(), resHeight.c_str());
		ImGui::Text("FPS: %s", std::to_string(fps).c_str());
		ImGui::End();
	}

	void initScene()
	{
		// camera
		camera.setPosition(cr::Vec3(0, 0, 3));

		// meshes
		auto cube_mesh = cr::Mesh::cube();
		auto sphere_mesh = cr::AssetsLoader::loadMesh("assets/sphere.obj");
		sphere_mesh->fillColor(cr::Vec4(1.0f, 0.0f, 0.2f, 1.0f));

		// textures
		auto cube_texture = cr::AssetsLoader::loadImage("assets/box.jpg");
		
		// shaders
		tex_shader = std::make_shared<cr::PointLightTextureShader>();
		color_shader = std::make_shared<cr::PointLightShader>();
		li_shader = std::make_shared<cr::DefaultShader>();

		tex_shader->bindTexture(cube_texture);
		tex_shader->bindProjectionMatrix(camera.getProjMatrix());
		color_shader->bindProjectionMatrix(camera.getProjMatrix());
		li_shader->bindProjectionMatrix(camera.getProjMatrix());

		// entities
		auto cube1 = std::make_shared<cr::Entity>(cube_mesh, tex_shader);
		auto cube2 = std::make_shared<cr::Entity>(cube_mesh, color_shader);
		auto sphere = std::make_shared<cr::Entity>(sphere_mesh, color_shader);
		li = std::make_shared<cr::Entity>(sphere_mesh, li_shader);
		li->setScale(cr::Vec3(0.2, 0.2, 0.2));

		cube1->setPosition(cr::Vec3(2, 0, -7));
		cube2->setPosition(cr::Vec3(-1, 0, -5));
		sphere->setPosition(cr::Vec3(0, 0, -7));
		
		// light
		li->setPosition(cr::Vec3(2, 1, -5));
		//color_shader->bindLightPosition(cr::Vec3(2, -1, -5.5));
		//tex_shader->bindLightPosition(cr::Vec3(2, -1, -5.5));

		level.getScene().push_back(cube1);
		level.getScene().push_back(cube2);
		level.getScene().push_back(sphere);
	}
};
