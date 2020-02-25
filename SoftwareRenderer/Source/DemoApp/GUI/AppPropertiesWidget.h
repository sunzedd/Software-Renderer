#pragma once
#include "Widget.h"

namespace Demo
{
	class AppPropertiesWidget : public Widget
	{
	public:
		AppPropertiesWidget(int resWidth, int resHeight);

		void render() override;
		void update(unsigned int dtime) override;

	private:
		std::string m_resolutionWidth;
		std::string m_resolutionHeight;
		std::string m_fpsString;
		int m_fps;
	};
}