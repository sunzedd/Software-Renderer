#pragma once
#include "../../Core/App.h"
#include "Shader.h"

using namespace Core;

class DemoApp_New : public App
{
private:
	World world;
	Camera camera;

	Vec3 dirLight = { 0, 0, -1 };

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Entity> lightIndicator;

public:
	DemoApp_New()
	{
		m_pWindow->setSize(sf::Vector2u(1024, 768));
		initScene();
	}

private:
	void updateGraphics(unsigned int dtime) override
	{
		shader->bindProjectionMatrix(camera.getProjMatrix());
		shader->bindViewMatrix(camera.getViewMatrix());
		shader->pointLightSrcPosition = lightIndicator->getPosition();

		m_renderer.beginFrame();

		for (auto& e : world.getScene())
			e->render(m_renderer);

		lightIndicator->render(m_renderer);

		// GUI
		unsigned int fps = 1 / (static_cast<double>(dtime) / 1000);

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", resWidth.c_str(), resHeight.c_str());
		ImGui::Text("FPS: %s", std::to_string(fps).c_str());
		ImGui::End();
	}

	void updateScene(unsigned int dtime) override
	{
		float dMove = dtime * 0.003;
		float dRot = dtime * 0.035;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		world.getScene()[0]->rotate(cr::Vec3(0, dRot, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		world.getScene()[0]->rotate(cr::Vec3(0, -(dRot), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	world.getScene()[0]->rotate(cr::Vec3(dRot, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		world.getScene()[0]->rotate(cr::Vec3(-(dRot), 0, 0));
		
		// camera
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

		world.getScene()[0]->rotate(cr::Vec3(dRot, dRot, dRot));

		world.update(dtime);
		camera.update(dtime);
		lightIndicator->update(dtime);
	}

	void initScene()
	{
		auto cylinerMesh = Mesh::cube();
		shader = std::make_shared<Shader>();
		auto cylinderObject = std::make_shared<Entity>(cylinerMesh, shader);

		auto liShader = std::make_shared<DefaultShader>();
		lightIndicator = std::make_shared<Entity>(AssetsLoader::loadMesh("assets/sphere.obj"), liShader);
		lightIndicator->setPosition(Vec3(0, 1, -4));
		lightIndicator->setScale(Vec3(0.1, 0.1, 0.1));

		world.getScene().push_back(cylinderObject);
		camera.setPosition(Vec3(0, 0, 3));

		shader->lightDir = dirLight;
		shader->pointLightSrcPosition = lightIndicator->getPosition();
	}
};