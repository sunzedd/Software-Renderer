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
#include "GUI/Widgets.h"
#include "Shaders/Shaders.h"
#include "../Core/Math/Vec2i.h"
#include "SceneObject.h"
#include "CoreAliases.h"

#define DEMOAPP_TITLE "Demo"

namespace cr = Core;

namespace Demo
{
	using ShaderLibrary = std::unordered_map<const char*, std::shared_ptr<Core::IShaderProgram>>;
	using TextureLibrary = std::unordered_map<const char*, std::shared_ptr<sf::Image>>;

	class EditorDemoApp final : public cr::App
	{
	public:
		EditorDemoApp();
		~EditorDemoApp();
	private:
		void updateScene(unsigned int dtime) override;
		void updateGraphics(unsigned int dtime) override;
		
		void processInput(unsigned int dtime);

		void loadAndInitWorld();
		void setupRendererSettings();
		void initGui();

	private:
		// world/scene objects
		cr::World worldInstance;
		cr::Camera camera;
		float cameraSpeed = 0.001;
		std::shared_ptr<cr::Entity> pointLightSource;
		std::vector<cr::LineV3> sphereNormalLines;

		// GUI
		std::vector<std::unique_ptr<Widget>> widgets;

		// Shaders
		struct
		{
			std::shared_ptr<MixedLightShader> mixedLight;
			std::shared_ptr<MixedLightTextureShader> mixedLightTexture;
			std::shared_ptr<DefaultSingleColorShader> singleColor;
		}
		shaders;

		ShaderLibrary shaderLib;
		TextureLibrary textureLib;

		static const int DEMOAPP_RESOLUTION_WIDTH = 1280;
		static const int DEMOAPP_RESOLUTION_HEIGHT = 800;
	};
}