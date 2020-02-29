#include "ObjectPickerWidgetBase.h"

namespace Demo
{
	ObjectPickerWidgetBase::ObjectPickerWidgetBase(Scene& scene, const std::string& title)
		:
		WidgetBase(title),
		m_scene(scene)
	{
		m_scene.buildObjectNamesList(m_itemLabelsStr);

		for (const auto& itemName : m_itemLabelsStr)
		{
			m_itemLabels.push_back(itemName.c_str());
		}
	}

	const char* ObjectPickerWidgetBase::getSelectedItemName()
	{
		return m_itemLabels[m_selectedItemIndex];
	}
}