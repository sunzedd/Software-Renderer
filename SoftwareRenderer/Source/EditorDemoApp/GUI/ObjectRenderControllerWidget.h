#pragma once
#include "Widget.h"
#include "../CoreAliases.h"
#include "../../Core/World/World.h"

namespace Demo
{
	using ShaderLibrary = std::unordered_map<const char*, std::shared_ptr<Core::IShaderProgram>>;
	using TextureLibrary = std::unordered_map<const char*, std::shared_ptr<sf::Image>>;

	class ObjectRenderControllerWidget : public Widget
	{
	public:
		ObjectRenderControllerWidget(Core::World& world, ShaderLibrary& sLib, TextureLibrary& texLib);
		void render() override;
		void update(unsigned int dtime) override;

	private:
		Core::World& m_world;
		
		ShaderLibrary& m_shaderLib;
		TextureLibrary& m_textureLib;

		std::vector<const char*> m_entityLabels;
		std::vector<const char*> m_textureLabels;
		int m_selectedEntityIndex = -1;
		int m_selectedTextureIndex = -1;
	};
}