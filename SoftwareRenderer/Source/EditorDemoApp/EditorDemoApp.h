#pragma once

/*
	+---------------------------------------------------------------------------+
	|					Simple sandbox for engine testing						|
	|	Lighting: 																|
	|		Two light sources:													|
	|			1. Directional (no manipulation provided, always static)		|
	|			2. Point light (can be moved as a regular world object)			|
	|																			|
	|	Objects:																|
	|		Three entities (can be moved, rotated and scaled):					|
	|			1. Cube (can be textured)										|
	|			2. Susann (can't be textured yet)								|
	|			3. Sphere (can't be textured yet)								|
	|																			|
	|	Manipulation and user input:											|
	|		FPS-Style camera (mouse with presses right button and WASD keys).	|
	|		Two GUI widgets based on ImGui library.								|
	|																			|
	+---------------------------------------------------------------------------+
*/

#include "../Core/Engine.h"
#include "../Core/Math/Vec2i.h"
#include "Shaders/Shaders.h"
#include "Scene/Scene.h"
#include "Scene/SceneObjectBuilder.h"
#include "UI/UI.h"
#include "AssetLibrary.h"

#define DEMOAPP_TITLE				"Demo"
#define DEMOAPP_RESOLUTION_WIDTH	960
#define DEMOAPP_RESOLUTION_HEIGHT	540

namespace cr = Core;

namespace Demo 
{
	extern std::shared_ptr<sf::Image> g_defaultTexture;
	extern std::shared_ptr<Core::IShaderProgram> g_defaultShader;
}

namespace Demo
{
	class EditorDemoApp final : public cr::App
	{
	public:
		EditorDemoApp();
		~EditorDemoApp();
	private:
		void update(unsigned int dtime) override;
		void render(unsigned int dtime) override;
		
		void processInput(unsigned int dtime);

		void loadShaderLibrary();
		void loadTextureLibrary();

		void initScene();
		void initCamera();
		void initLighting();
		void initRender();
		void initGui();

	private:
		std::unique_ptr<Scene> m_scene;
		std::vector<WidgetBase*> m_ui;

		float m_cameraSpeed = 0.004;
	};
}