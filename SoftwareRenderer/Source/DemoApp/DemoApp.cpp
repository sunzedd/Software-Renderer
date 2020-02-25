#include "DemoApp.h"

namespace Demo
{
	DemoApp::DemoApp() 
		:
		App(DEMOAPP_RESOLUTION_WIDTH,
			DEMOAPP_RESOLUTION_HEIGHT,
			DEMOAPP_TITLE, false)
	{
		loadAndInitWorld();
		setupGraphicsSettings();
		initGui();
	}

	DemoApp::~DemoApp()
	{ }

	void DemoApp::updateScene(unsigned int dtime)	
	{
		processInput(dtime);

		worldInstance.update(dtime);
		camera.update(dtime);

		for (auto& widget : widgets)
			widget->update(dtime);
	}

	void DemoApp::updateGraphics(unsigned int dtime)
	{
		// Update shader "uniforms".
		shaders.mixedLight->bindViewMatrix(camera.getViewMatrix());
		shaders.mixedLight->bindPointLightPosition(pointLightSource->getPosition());
		shaders.singleColor->bindViewMatrix(camera.getViewMatrix());

		m_renderer.beginFrame();

		worldInstance.render(m_renderer);
		for (auto& widget : widgets) 
			widget->render();
	}

	void DemoApp::processInput(unsigned int dtime)
	{
		float dRot = dtime * 0.035;
		float dMove = dtime * 0.003;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.move(cr::Direction::Left, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.move(cr::Direction::Right, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.move(cr::Direction::Forward, dMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.move(cr::Direction::Backward, dMove);

		//mouse movement
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
	}


	void DemoApp::loadAndInitWorld() 
	{
		// +-------------------- Creation and loading world objects.----------------------+
		// 1. Meshes:
		auto sphereMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\sphere.obj");
		auto lightIndicatorMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\sphere.obj");
		auto treeMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\tree.obj");
		auto susannMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\susann.obj");
		auto terrainMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\terrain_s.obj");

		sphereMesh->fillColor(vec4(0.3f, 0.3f, 0.9f, 1.0f));
		treeMesh->fillColor(vec4(0.8f, 0.2f, 0.1f, 1.0f));
		susannMesh->fillColor(vec4(0.2f, 0.9f, 0.2f, 1.0f));
		terrainMesh->fillColor(vec4(0.5f, 0.2f, 0.3f, 1.0f));

		// 2. Textures:
		// ----

		// 3. Shaders:
		shaders.mixedLight = std::make_shared<MixedLightShader>();
		shaders.singleColor = std::make_shared<DefaultSingleColorShader>(vec4(0.8f, 0.8f, 0.8f, 1.0f));

		// 4. Entities creation and filling the scene:
		auto sphereObject = std::make_shared<cr::Entity>("Sphere", sphereMesh, shaders.mixedLight);
		auto treeObject = std::make_shared<cr::Entity>("Cube", treeMesh, shaders.mixedLight);
		auto susannObject = std::make_shared<cr::Entity>("Susann", susannMesh, shaders.mixedLight);
		auto terrainObject = std::make_shared<cr::Entity>("Terrain", terrainMesh, shaders.mixedLight);
		auto lightSource = std::make_shared<cr::Entity>("Point light", lightIndicatorMesh, shaders.singleColor);

		sphereObject->setPosition(vec3(0.0f, 1.0f, -3.0f));
		treeObject->setPosition(vec3(-3.0f, 1.0f, -3.0f));
		susannObject->setPosition(vec3(3.0f, 1.0f, -3.0f));
		terrainObject->setPosition(vec3(0.0f, 0.0f, -3.0f));
		terrainObject->setScale(vec3(1.5f, 1.5f, 1.5f));

		lightSource->setPosition(vec3(0.0f, 2.5f, -3.0f));
		lightSource->setScale(vec3(0.2f, 0.2f, 0.2f));

		pointLightSource = lightSource;

		worldInstance.getScene().push_back(sphereObject);
		worldInstance.getScene().push_back(treeObject);
		worldInstance.getScene().push_back(susannObject);
		worldInstance.getScene().push_back(terrainObject);
		worldInstance.getScene().push_back(lightSource);
	}

	void DemoApp::setupGraphicsSettings()
	{
		camera.setPosition(vec3(0.0f, 0.0f, 5.0f));
		camera.setup(45.0f, 0.001f, 50.0f, 16.0f / 10.0f);

		shaders.mixedLight->bindProjectionMatrix(camera.getProjMatrix());
		shaders.singleColor->bindProjectionMatrix(camera.getProjMatrix());
	}

	void DemoApp::initGui()
	{
		widgets.push_back(std::make_unique<AppPropertiesWidget>(m_windowProps.width, m_windowProps.height));
		widgets.push_back(std::make_unique<TransformManipulatorWidget>(worldInstance));
	}
}