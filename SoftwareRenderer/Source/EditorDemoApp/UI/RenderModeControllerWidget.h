#pragma once
#include "ObjectPickerWidgetBase.h"
#include "../AssetLibrary.h"
#include "../Shaders/Shaders.h"

namespace Demo
{
	class RenderModeControllerWidget : public ObjectPickerWidgetBase
	{
	private:
		enum RenderMode
		{
			Colored  = 0,
			Textured = 1
		};

		struct RenderSettingsState
		{
			int mode;		// For controll this variable by ImGui we need integer type for doing it without a cast.
			vec4 color;
			std::string textureName;
		};

	public:
		RenderModeControllerWidget(Scene& scene);

		void render() override;
		void update(unsigned int dtime) override { }

		const char* getSelectedTextureName();

		void fillTextureNamesLists();
		void fillRenderSettingsList();

	private:
		ShaderLibrary&			 m_shaderLib;
		TextureLibrary&			 m_textureLib;
	
		std::vector<const char*> m_textureLabels;
		std::vector<std::string> m_textureLabelsStr;
		int						 m_selectedTextureIndex = -1;

		std::vector<RenderSettingsState> m_renderSettingsStateList;

		const char* const m_renderModes[2] = { "Colored", "Textured" };

		static const std::string S_DEFAULT_TEXTURE_NAME;
	};
}