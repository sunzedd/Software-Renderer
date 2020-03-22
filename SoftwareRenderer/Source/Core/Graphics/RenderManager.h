#pragma once
#include "../Window.h"
#include "RenderPipeline.h"

namespace core
{

class RenderManager
{
	static std::unique_ptr<RenderManager> s_instance;
	static std::unique_ptr<RenderPipeline> s_pipeline;

public:
	static void initRenderSystem(Window& window);
	static RenderPipeline& pipeline();

private:
	RenderManager();
};

}