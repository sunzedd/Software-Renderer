#pragma once
#include "../../Core/World/Entity.h"
#include "../../Core/AssetLoader.h"
#include "../Shaders/SingleColorShader.h"
#include "../CoreAliases.h"
#include "../AssetLibrary.h"

namespace Demo 
{
	class PointLightSource : public Core::Entity
	{
	public:
		PointLightSource(const vec4& indicatorColor);

		void update(unsigned int dtime);
		void render(Core::RenderPipeline& renderer);
		void isVisible(bool visible) { m_isVisible = visible; }

	private:
		bool m_isVisible = true;
	};
}