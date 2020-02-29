#include "EditorDemoApp.h"

namespace Demo
{
	EditorDemoApp::EditorDemoApp() 
		:
		App(DEMOAPP_RESOLUTION_WIDTH, DEMOAPP_RESOLUTION_HEIGHT, DEMOAPP_TITLE, false)
	{
		loadShaders();
		initScene();
		initRender();
		initGui();
	}

	void EditorDemoApp::update(unsigned int dtime)	
	{
		processInput(dtime);
		m_scene->update(dtime);

		for (auto& widget : m_widgets)
			widget->update(dtime);
	}

	void EditorDemoApp::render(unsigned int dtime)
	{
		m_renderer.beginFrame();

		m_scene->render(m_renderer);

		for (auto& widget : m_widgets) 
			widget->render();
	}


	void EditorDemoApp::processInput(unsigned int dtime)
	{
		float dRot = dtime * 0.035;
		float dMove = dtime * 0.003;
		float dCamMove = m_cameraSpeed * dtime;

		auto& camera = m_scene->getCamera();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.move(cr::Direction::Left, dCamMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.move(cr::Direction::Right, dCamMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.move(cr::Direction::Forward, dCamMove);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.move(cr::Direction::Backward, dCamMove);

		//mouse movement
		static bool isMouseRightBtnPressed = false;
		static vec2i lastMouseCursorPosition = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isMouseRightBtnPressed)
		{
			isMouseRightBtnPressed = true;
			lastMouseCursorPosition = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && isMouseRightBtnPressed)
		{
			isMouseRightBtnPressed = false;
		}

		if (isMouseRightBtnPressed)
		{
			vec2i currentMouseCursorPosition = {
				sf::Mouse::getPosition().x,
				sf::Mouse::getPosition().y
			};

			camera.rotate(cr::Vec2(
				lastMouseCursorPosition.x - currentMouseCursorPosition.x,
				lastMouseCursorPosition.y - currentMouseCursorPosition.y));

			// TODO: Block rotation around Z axis.

			lastMouseCursorPosition = currentMouseCursorPosition;
		}
	}


	void EditorDemoApp::loadShaders()
	{
		auto& slib = ShaderLibrary::instance();

		slib.add("Color with point light", std::make_shared<MixedLightShader>());
		slib.add("Texture with point light", std::make_shared<MixedLightTextureShader>());
		slib.add("Single color", std::make_shared<DefaultSingleColorShader>(vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	}

	void EditorDemoApp::initScene()
	{
		m_scene = std::make_unique<Scene>();

		auto camera = std::make_shared<Core::Camera>();
		camera->setup(45.0f, 0.001f, 100.0f,
			static_cast<float>(DEMOAPP_RESOLUTION_WIDTH) / static_cast<float>(DEMOAPP_RESOLUTION_HEIGHT));
		camera->setPosition(vec3(0.0f, 0.0f, 3));
		m_scene->setCamera(std::move(camera));

		auto& slib = ShaderLibrary::instance();
		auto lightScrShader = slib.get("Single color");
		auto lightSrcMesh = cr::AssetsLoader::loadMesh("Assets\\Meshes\\sphere.obj");
		auto lightSrc = std::make_shared<SceneObject>(lightSrcMesh, std::move(lightScrShader));
		lightSrc->setScale(vec3(0.1f, 0.1f, 0.1f));
		lightSrc->setPosition(vec3(0, 0, -5));

		m_scene->setLightSource("Light Source", lightSrc);
	}

	void EditorDemoApp::initRender()
	{
		m_renderer.backFaceCulling(true);
		m_renderer.wireframeRendering(false);
	}

	void EditorDemoApp::initGui()
	{
		m_widgets.push_back(std::make_unique<AppPropertiesWidget>(m_windowProps.width, m_windowProps.height));
	}
}