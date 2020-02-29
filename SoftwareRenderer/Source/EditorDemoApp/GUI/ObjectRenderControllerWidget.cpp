#include "ObjectRenderControllerWidget.h"

#if 0
namespace Demo
{
	ObjectRenderControllerWidget::ObjectRenderControllerWidget(Core::World& world, 
		ShaderLibrary& sLib, TextureLibrary& texLib)
		: 
		m_world(world),
		m_shaderLib(sLib),
		m_textureLib(texLib)
	{
		m_title = "Texturing";

		for (int i = 0; i < m_world.getScene().size(); i++)
		{
			const auto& entity = world.getScene()[i];
			//m_entityLabels.push_back(entity->getId().first.c_str());
		}

		m_textureLabels.push_back("No Texture");
		for (auto e = m_textureLib.cbegin(); e != m_textureLib.cend(); e++)
		{
			m_textureLabels.push_back(e->first);
		}
	}

	void ObjectRenderControllerWidget::render()
	{
		ImGui::Begin(m_title.c_str());
		ImGui::Combo("Object", &m_selectedEntityIndex, &m_entityLabels[0], m_entityLabels.size(), m_entityLabels.size());
		ImGui::Combo("Texture", &m_selectedTextureIndex, &m_textureLabels[0], m_textureLabels.size(), m_textureLabels.size());

		if (m_selectedEntityIndex > -1)
		{
			if (m_selectedTextureIndex > -1)
			{

			}
		}

		ImGui::End();
	}

	void ObjectRenderControllerWidget::update(unsigned int dtime)
	{
	}
}
#endif