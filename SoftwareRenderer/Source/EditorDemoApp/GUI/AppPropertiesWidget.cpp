#include "AppPropertiesWidget.h"

namespace Demo
{
	AppPropertiesWidget::AppPropertiesWidget(int resWidth, int resHeight)
		:
		m_resolutionWidth(std::to_string(resWidth)),
		m_resolutionHeight(std::to_string(resHeight))
	{
		m_title = "Properties";
	}

	void AppPropertiesWidget::render()
	{
		ImGui::Begin("Properties");
		ImGui::Text("Resolution: %s x %s", m_resolutionWidth.c_str(), m_resolutionHeight.c_str());
		ImGui::Text("FPS: %s", m_fpsString.c_str());
		ImGui::End();
	}

	void AppPropertiesWidget::update(unsigned int dtime)
	{
		m_fps = 1.0f / (static_cast<double>(dtime) / 1000);
		m_fpsString = std::to_string(m_fps);
	}
}