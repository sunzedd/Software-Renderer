#include "TestDemo1.h"

namespace Demo
{
	TestApp1::TestApp1()
		:
		App(1280, 720, "Demo", false)
	{
		init();
	}

	std::unique_ptr<TestApp1> TestApp1::Create()
	{
		auto app = std::make_unique<TestApp1>();
		return app;
	}

	void TestApp1::init()
	{
		// Sphere object
		auto sphereMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\sphere.obj");
		shaders.sphere = std::make_shared<Shader>();
		sphereMesh->fillColor(cr::Vec4(0.0f, 0.2f, 1.0f, 1.0f));
		auto sphereEntity = std::make_shared<cr::Entity>(std::move(sphereMesh), shaders.sphere);
		sphereEntity->rotate(cr::Vec3(0, 90, 0));

		// cube object
		auto cubeMesh = cr::Mesh::cube();
		cubeMesh->fillColor(cr::Vec4(0.4, 0.0, 0.1, 1.0f));
		shaders.cube = std::make_shared<Shader>();
		auto cubeEntity = std::make_shared<cr::Entity>(std::move(cubeMesh), shaders.cube);
		cubeEntity->setPosition(cr::Vec3(-3.0f, 0.0f, -1.0f));

		// susann object
		auto susannMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\susann.obj");
		shaders.susann = std::make_shared<Shader>();
		susannMesh->fillColor(cr::Vec4(0.1f, 0.9f, 0.4f, 1.0f));
		auto susannEntity = std::make_shared<cr::Entity>(std::move(susannMesh), shaders.susann);
		susannEntity->setPosition(cr::Vec3(3.0f, 0.0f, -1.0f));

		// floor
		auto floorMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\floor.obj");
		floorMesh->fillColor(cr::Vec4(0.1f, 0.0f, 0.2f, 0.0f));
		shaders.floor = std::make_shared<Shader>();
		auto floorEntity = std::make_shared<cr::Entity>(std::move(floorMesh), shaders.floor);
		floorEntity->setPosition(cr::Vec3(0.0f, -1.0f, 0.0f));
		floorEntity->setScale(cr::Vec3(0.25f, 0.25f, 0.25f));
		floorEntity->rotate(cr::Vec3(0, 180, 0));

		// Light source
		auto liMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\sphere.obj");
		liMesh->fillColor(cr::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		shaders.lightSource = std::make_shared<cr::DefaultShader>();
		auto lightSourceIndicator = std::make_shared<cr::Entity>(std::move(liMesh), shaders.lightSource);
		lightSourceIndicator->setScale(cr::Vec3(0.1, 0.1, 0.1));
		lightSourceIndicator->setPosition(cr::Vec3(2.0f, 3.0f, 0.0f));

		// add objects to the scene.
		lightSource = lightSourceIndicator;
		world.getScene().push_back(std::move(sphereEntity));
		world.getScene().push_back(std::move(lightSourceIndicator));
		world.getScene().push_back(std::move(cubeEntity));
		world.getScene().push_back(std::move(susannEntity));
		world.getScene().push_back(std::move(floorEntity));

		// setup camera
		camera.setPosition(cr::Vec3(0.0f, 0.0f, 3.0f));
		camera.setup(50.0f, 0.001f, 100.0f, 16.0f / 9.0f);

		// setup shaders.
		shaders.sphere->bindProjectionMatrix(camera.getProjMatrix());
		shaders.lightSource->bindProjectionMatrix(camera.getProjMatrix());
		shaders.cube->bindProjectionMatrix(camera.getProjMatrix());
		shaders.susann->bindProjectionMatrix(camera.getProjMatrix());
		shaders.floor->bindProjectionMatrix(camera.getProjMatrix());

		m_renderer.backFaceCulling(true);
		m_renderer.wireframeRendering(false);
	}

	void TestApp1::updateScene(unsigned int dtime)
	{
		static const float mouseSensFactor = 0.8;
		static const float dRot = dtime * 0.0035;
		static const float dMove = dtime * 0.0006;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	exit(0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		camera.move(cr::Direction::Left, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		camera.move(cr::Direction::Right, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		camera.move(cr::Direction::Forward, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		camera.move(cr::Direction::Backward, dMove);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		lightSource->move(cr::Vec3(0, dMove, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		lightSource->move(cr::Vec3(0, -(dMove), 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	lightSource->move(cr::Vec3(dMove, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		lightSource->move(cr::Vec3(-dMove, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))	lightSource->move(cr::Vec3(0, 0, -(dMove)));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))		lightSource->move(cr::Vec3(0, 0, (dMove)));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			static int lastMouseX = sf::Mouse::getPosition().x;
			static int lastMouseY = sf::Mouse::getPosition().y;

			int curMouseX = sf::Mouse::getPosition().x;
			int curMouseY = sf::Mouse::getPosition().y;

			camera.rotate(cr::Vec2((lastMouseX - curMouseX) * mouseSensFactor, (lastMouseY - curMouseY)) * mouseSensFactor);

			lastMouseX = curMouseX;
			lastMouseY = curMouseY;
		}

		world.update(dtime);
		camera.update(dtime);
	}

	void TestApp1::updateGraphics(unsigned int dtime)
	{
		shaders.sphere->bindLightPosition(lightSource->getPosition());
		shaders.sphere->bindViewMatrix(camera.getViewMatrix());
		shaders.cube->bindLightPosition(lightSource->getPosition());
		shaders.cube->bindViewMatrix(camera.getViewMatrix());
		shaders.susann->bindLightPosition(lightSource->getPosition());
		shaders.susann->bindViewMatrix(camera.getViewMatrix());
		shaders.floor->bindViewMatrix(camera.getViewMatrix());
		shaders.floor->bindLightPosition(lightSource->getPosition());
		shaders.lightSource->bindViewMatrix(camera.getViewMatrix());

		m_renderer.beginFrame();
		world.render(m_renderer);

		renderGui(dtime);
	}

	void TestApp1::renderGui(unsigned int dtime)
	{
		// GUI
		unsigned int fps = 1 / (static_cast<double>(dtime) / 1000);

		static const std::string resWidth = std::to_string(m_windowProps.width);
		static const std::string resHeight = std::to_string(m_windowProps.height);

		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", resWidth.c_str(), resHeight.c_str());
		ImGui::Text("FPS: %s", std::to_string(fps).c_str());
		ImGui::End();
	}
}