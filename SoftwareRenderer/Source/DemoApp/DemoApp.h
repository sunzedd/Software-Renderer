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

namespace cr = Core;
#define DEMOAPP_TITLE "Demo"

namespace Demo
{
	const int   DEMOAPP_RESOLUTION_WIDTH = 1280;
	const int   DEMOAPP_RESOLUTION_HEIGHT =  800;

	class DemoApp final : public cr::App
	{
	public:
		DemoApp();
		~DemoApp();

	private:
		void updateScene(unsigned int dtime) override;
		void updateGraphics(unsigned int dtime) override;
		
		void processInput(unsigned int dtime);

		void loadAndInitWorld();
		void setupGraphicsSettings();
		void initGui();

	private:
		// world/scene objects
		cr::World worldInstance;
		cr::Camera camera;
		std::shared_ptr<cr::Entity> pointLightSource;

		// GUI
		std::vector<std::unique_ptr<Widget>> widgets;

		// Shaders
		struct
		{
			std::shared_ptr<MixedLightShader> mixedLight;
			std::shared_ptr<DefaultSingleColorShader> singleColor;
		}
		shaders;
	};
}