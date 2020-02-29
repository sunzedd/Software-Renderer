#include "EditorDemoApp.h"

namespace Demo {
	std::shared_ptr<sf::Image> g_defaultTexture = Core::AssetLoader::loadImage("Assets\\Textures\\floor.jpg");
}

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

		slib.add("PLC", std::make_shared<PointLightColorShader>());	// PLC = Point Light Colored
		slib.add("PLT", std::make_shared<PointLightTextureShader>(g_defaultTexture)); // PLT = Point Light Textured
		slib.add("SC", std::make_shared<SingleColorShader>(vec4(1.0f, 0.0f, 0.0f, 1.0f))); // SC = Single Color
	}

	void EditorDemoApp::initScene()
	{
		m_scene = std::make_unique<Scene>();
		auto& shaderLib = ShaderLibrary::instance();

		// Camera creation and setup
		auto camera = std::make_shared<Core::Camera>();
		camera->setup(45.0f, 0.001f, 100.0f,
			static_cast<float>(DEMOAPP_RESOLUTION_WIDTH) / static_cast<float>(DEMOAPP_RESOLUTION_HEIGHT));
		camera->setPosition(vec3(0.0f, 0.0f, 3));

		// Light source creation and setup
		vec4 lightSourceIndicatorColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		auto lightSource = std::make_shared<PointLightSource>(lightSourceIndicatorColor);
		lightSource->setPosition(vec3(0.0f, 0.0f, -2.0f));
		lightSource->setScale(vec3(0.2f, 0.2f, 0.2f));

		m_scene->setCamera(std::move(camera));
		m_scene->setLightSource(lightSource);
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