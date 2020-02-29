#pragma once
#include "WidgetBase.h"
#include "../Scene/Scene.h"

namespace Demo
{
	class ObjectPickerWidgetBase : public WidgetBase
	{
	public:
		ObjectPickerWidgetBase(Scene& scene, const std::string& title);

		virtual void render() = 0;
		virtual void update(unsigned int dtime) = 0;

		const char* getSelectedItemName();

	protected:
		Scene& m_scene;
		std::vector<const char*> m_itemLabels;
		std::vector<std::string> m_itemLabelsStr;
		int m_selectedItemIndex = -1;
	};
}