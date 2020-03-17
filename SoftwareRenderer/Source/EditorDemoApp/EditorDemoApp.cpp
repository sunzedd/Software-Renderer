#include "EditorDemoApp.h"

namespace Demo 
{
	std::shared_ptr<sf::Image> g_defaultTexture = Core::AssetLoader::loadImage("Assets\\Textures\\floor.jpg");
	std::shared_ptr<Core::IShaderProgram> g_defaultShader = std::make_shared<SingleColorShader>();
}

namespace Demo
{
	EditorDemoApp::EditorDemoApp() 
		:
		App(DEMOAPP_RESOLUTION_WIDTH, DEMOAPP_RESOLUTION_HEIGHT, DEMOAPP_TITLE, false)
	{
		loadShaderLibrary();
		loadTextureLibrary();
		initScene();
		initRender();
		initGui();
	}

	EditorDemoApp::~EditorDemoApp()
	{
		for (WidgetBase* w : m_ui) 
			delete w;
	}

	void EditorDemoApp::update(unsigned int dtime)	
	{
		processInput(dtime);
		m_scene->update(dtime);
		for (auto w : m_ui) w->update(dtime);
	}

	void EditorDemoApp::render(unsigned int dtime)
	{
		m_renderer.beginFrame();
		m_scene->render(m_renderer);
		//for (auto w : m_ui) w->render();
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


	void EditorDemoApp::loadTextureLibrary()
	{
		auto& tlib = TextureLibrary::instance();

		tlib.add("Box", Core::AssetLoader::loadImage("Assets\\Textures\\box.jpg"));
		tlib.add("Metal", Core::AssetLoader::loadImage("Assets\\Textures\\metal.jpg"));
		tlib.add("Quads", Core::AssetLoader::loadImage("Assets\\Textures\\quads.jpg"));
		tlib.add("Stone", Core::AssetLoader::loadImage("Assets\\Textures\\stone.jpg"));
		tlib.add("Wood", Core::AssetLoader::loadImage("Assets\\Textures\\wood.jpg"));
		tlib.add("Earth", Core::AssetLoader::loadImage("Assets\\Textures\\earth.jpg"));
		tlib.add("Grass", Core::AssetLoader::loadImage("Assets\\Textures\\grass_real.jpg"));
	}

	void EditorDemoApp::loadShaderLibrary()
	{
		auto& slib = ShaderLibrary::instance();

		slib.add("PLC", std::make_shared<PointLightColorShader>());	// PLC = Point Light Colored
		slib.add("PLT", std::make_shared<PointLightTextureShader>(g_defaultTexture)); // PLT = Point Light Textured
		slib.add("SC", std::make_shared<SingleColorShader>(vec4(1.0f, 0.0f, 0.0f, 1.0f))); // SC = Single Color
	}

	void EditorDemoApp::initScene()
	{
		m_scene = std::make_unique<Scene>();

		initCamera();
		initLighting();

		// Fill the scene with objects
		SceneObjectBuilder objBuilder;

		// Terrain
		objBuilder.createObject();
		objBuilder.setMesh(Core::AssetLoader::loadMesh("Assets\\Meshes\\floor.obj"));
		objBuilder.setPosition(vec3(0.0f, 0.0f, 0.0f));
		objBuilder.setShader(ShaderLibrary::instance().get("PLC"));
		m_scene->add("Terrain", objBuilder.getBuiltObject());

		// Cube (Builder creates cube by default)
		objBuilder.createObject();
		objBuilder.setShader(ShaderLibrary::instance().get("PLC"));
		objBuilder.setPosition(vec3(-3.0f, 1.0f, -2.0f));
		objBuilder.setScale(vec3(0.5f, 0.5f, 0.5f));
		m_scene->add("Cube", objBuilder.getBuiltObject());

		// Sphere
		objBuilder.createObject();
		objBuilder.setMesh(Core::AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj"));
		objBuilder.setPosition(vec3(0.0f, 1.0f, -1.0f));
		objBuilder.setShader(ShaderLibrary::instance().get("PLC"));
		m_scene->add("Sphere", objBuilder.getBuiltObject());

		// Tree1
		objBuilder.createObject();
		objBuilder.setMesh(Core::AssetLoader::loadMesh("Assets\\Meshes\\tree_01.obj"));
		objBuilder.setPosition(vec3(5.0f, 0.0f, -6.0f));
		objBuilder.setShader(ShaderLibrary::instance().get("PLC"));
		m_scene->add("Tree1", objBuilder.getBuiltObject());

		// Tree2
		objBuilder.createObject();
		objBuilder.setMesh(Core::AssetLoader::loadMesh("Assets\\Meshes\\tree_02.obj"));
		objBuilder.setPosition(vec3(2.0f, 0.0f, -4.0f));
		objBuilder.setShader(ShaderLibrary::instance().get("PLC"));
		m_scene->add("Tree2", objBuilder.getBuiltObject());
	}


	void EditorDemoApp::initCamera()
	{
		auto camera = std::make_shared<Core::Camera>();
		camera->setup(45.0f, 0.001f, 100.0f,
			static_cast<float>(DEMOAPP_RESOLUTION_WIDTH) / static_cast<float>(DEMOAPP_RESOLUTION_HEIGHT));
		camera->setPosition(vec3(0.0f, 1.0f, 10));

		m_scene->setCamera(std::move(camera));
	}

	void EditorDemoApp::initLighting()
	{
		vec4 lightSourceIndicatorColor = { 1.0f, 1.0f, 0.5f, 1.0f };
		auto lightSource = std::make_shared<PointLightSource>(lightSourceIndicatorColor);
		lightSource->setPosition(vec3(0.0f, 5.0f, -2.0f));
		lightSource->setScale(vec3(0.2f, 0.2f, 0.2f));

		m_scene->setLightSource(lightSource);
	}

	void EditorDemoApp::initRender()
	{
		m_renderer.backFaceCulling(true);
		m_renderer.wireframeRendering(false);
	}

	void EditorDemoApp::initGui()
	{
		m_ui.push_back(new PerformanceViewerWidget(vec2i(800, 600)));
		m_ui.push_back(new TransformControllerWidget(*m_scene));
		m_ui.push_back(new RenderModeControllerWidget(*m_scene));
	}
}