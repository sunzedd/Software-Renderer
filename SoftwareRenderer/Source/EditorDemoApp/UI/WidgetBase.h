#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>
#include "../../Core/Math/Vec3.h"
#include "../CoreAliases.h"

#define DEMOAPP_WIDGET_MAXTITLE 32

namespace Demo
{
	class WidgetBase
	{
	public:
		WidgetBase(const std::string& title) 
		{
			std::strcpy(m_title, title.c_str());
		}

		virtual void render() = 0;
		virtual void update(unsigned int dtime) = 0;

	protected:
		char m_title[DEMOAPP_WIDGET_MAXTITLE];
	};
}