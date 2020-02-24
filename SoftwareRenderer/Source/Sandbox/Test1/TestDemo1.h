#pragma once
#include "../../Core/App.h"
#include "../../Core/AssetsLoader.h"
#include "../../Core/World/World.h"
#include "../../Core/World/Camera.h"
#include "Shader.h"

namespace cr = Core;

namespace Demo
{
	template<class T>
	using Unique = std::unique_ptr<T>;
	template<class T>
	using Ref = std::shared_ptr<T>;

	class TestApp1 : public Core::App
	{
	public:
		static std::unique_ptr<TestApp1> Create();
		TestApp1();

	private:

		void init();
		void renderGui(unsigned int dtime);

		void updateScene(unsigned int dtime) override;
		void updateGraphics(unsigned int dtime) override;

	private:
		cr::World world;
		cr::Camera camera;

		Ref<cr::Entity> lightSource;

		struct
		{
			Ref<Shader> sphere;
			Ref<Shader> cube;
			Ref<Shader> susann;
			Ref<Shader> floor;
			Ref<cr::DefaultShader> lightSource;
		} shaders;
	};
}