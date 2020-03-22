#include "RenderManager.h"

namespace core
{

static std::unique_ptr<RenderManager> s_instance = nullptr;

void RenderManager::initRenderSystem(Window& window)
{
	s_instance = std::make_unique<RenderManager>();

	s_pipeline = std::make_unique<RenderPipeline>(window.getFrameBuffer());
}

RenderPipeline& RenderManager::pipeline()
{
	if (!s_instance) throw RenderSystemNotInitializedException();
	return *(s_instance->s_pipeline);
}

RenderManager::RenderManager()
{
}

}