#pragma once
#include "WidgetBase.h"

namespace Demo
{
	class PerformanceViewerWidget : public WidgetBase
	{
	public:
		PerformanceViewerWidget(const vec2i& resolution)
			:
			WidgetBase("Performance")
		{
			setResolution(resolution);
		}

		inline void render() override
		{
			ImGui::Begin(m_title);
			ImGui::Text("Resolution: %s x %s", m_resolutionWidthStr.c_str(), m_resolutionHeightStr.c_str());
			ImGui::Text("FPS: %s", m_fpsStr.c_str());
			ImGui::End();
		}
		
		void update(unsigned int dtime) override
		{
			int fps = 1.0f / (static_cast<double>(dtime) / 1000);
			m_fpsStr = std::to_string(fps);
		}

		void setResolution(const vec2i& resolution)
		{
			m_resolution = resolution;
			m_resolutionWidthStr = std::to_string(m_resolution.x);
			m_resolutionHeightStr = std::to_string(m_resolution.y);
		}

	protected:
		vec2i m_resolution;
		std::string m_resolutionWidthStr;
		std::string m_resolutionHeightStr;
		std::string m_fpsStr;
	};
}