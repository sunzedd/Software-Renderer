#include "RenderModeControllerWidget.h"

namespace Demo
{
	const std::string RenderModeControllerWidget::S_DEFAULT_TEXTURE_NAME = std::string("Quads");

	RenderModeControllerWidget::RenderModeControllerWidget(Scene& scene)
		:
		ObjectPickerWidgetBase(scene, "Texturing"),
		m_shaderLib(ShaderLibrary::instance()),
		m_textureLib(TextureLibrary::instance())
	{
		fillTextureNamesLists();
		fillRenderSettingsList();
	}

	void RenderModeControllerWidget::render()
	{
		ImGui::Begin(m_title);
		ImGui::Combo("Object", &m_selectedItemIndex, &m_itemLabels[0], m_itemLabels.size(), m_itemLabels.size());

		
		if (m_selectedItemIndex > -1)
		{
			static int previousSelectedItemIndex = m_selectedItemIndex;

			auto& selectedObjRenderState = m_renderSettingsStateList[m_selectedItemIndex];
			static RenderSettingsState modifiedSelectedObjRenderState =
			{
				selectedObjRenderState.mode,
				selectedObjRenderState.color
			};

			// Change modifObjectState if user picked another object.
			if (previousSelectedItemIndex != m_selectedItemIndex)
			{
				previousSelectedItemIndex = m_selectedItemIndex;
				modifiedSelectedObjRenderState =
				{
					selectedObjRenderState.mode,
					selectedObjRenderState.color
				};
			}
		
			ImGui::ListBox("Mode", &(modifiedSelectedObjRenderState.mode), m_renderModes, 2, 2);

			if (modifiedSelectedObjRenderState.mode == RenderMode::Colored)
			{
				ImGui::ColorPicker4("Color", modifiedSelectedObjRenderState.color.data);
			}
			else // mode == RenderMode::Textured
			{
				// Texture picker
				ImGui::Combo("Texture", &m_selectedTextureIndex, &m_textureLabels[0],
					m_textureLabels.size(), m_textureLabels.size());

				if (m_selectedTextureIndex > -1)
					modifiedSelectedObjRenderState.textureName = getSelectedTextureName();
			}

			if (ImGui::Button("Apply", { 50, 25 }))
			{
				if (modifiedSelectedObjRenderState.mode == RenderMode::Colored)
				{
					auto& object = m_scene.getObject(getSelectedItemName());
					auto shader = std::dynamic_pointer_cast<PointLightColorShader>(m_shaderLib.get("PLC"));

					//+-------------------------------------------------------------------------+
					//| TODO: Rewrite!!!!!!!!!!!!												|
					//| Bad architecture design cause this Kostil' :(							|
					auto shaderCopy = std::make_shared<PointLightColorShader>(*shader);
					//+-------------------------------------------------------------------------+

					shaderCopy->setColor(modifiedSelectedObjRenderState.color);
					object.setShader(shaderCopy);
				}
				else // mode == RenderMode::Textured
				{
					auto& object = m_scene.getObject(getSelectedItemName());
					auto shader = std::dynamic_pointer_cast<PointLightTextureShader>(m_shaderLib.get("PLT"));
					auto texture = m_textureLib.get(modifiedSelectedObjRenderState.textureName);

					//+-------------------------------------------------------------------------+
					//| TODO: Rewrite!!!!!!!!!!!!												|
					//| Bad architecture design cause this Kostil' :(							|
					auto shaderCopy = std::make_shared<PointLightTextureShader>(*shader);
					//+-------------------------------------------------------------------------+
					shaderCopy->setTexture(texture);
					object.setShader(shaderCopy);
				}
			}
		}

		ImGui::End();
	}

	const char* RenderModeControllerWidget::getSelectedTextureName()
	{
		return m_textureLabels[m_selectedTextureIndex];
	}

	void RenderModeControllerWidget::fillTextureNamesLists()
	{
		m_textureLib.buildNamesList(m_textureLabelsStr);
		m_textureLabels.reserve(m_textureLabelsStr.size());
		for (const auto& textureName : m_textureLabelsStr)
			m_textureLabels.emplace_back(textureName.c_str());
	}

	void RenderModeControllerWidget::fillRenderSettingsList()
	{
		m_renderSettingsStateList.reserve(m_itemLabelsStr.size());
		for (int i = 0; i < m_itemLabelsStr.size(); i++)
		{
			RenderSettingsState state;
			state.color = vec4(0.3f, 0.5f, 0.8f, 1.0f);
			state.mode = static_cast<int>(RenderMode::Colored);
			state.textureName = S_DEFAULT_TEXTURE_NAME;

			m_renderSettingsStateList.emplace_back(state);
		}
	}
}