#pragma once
#include "../../Core/Math/Vec3.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>

namespace Demo
{
	class Widget
	{
	public:
		virtual void render() = 0;
		virtual void update(unsigned int dtime) = 0;

	protected:
		std::string m_title;
	};
}