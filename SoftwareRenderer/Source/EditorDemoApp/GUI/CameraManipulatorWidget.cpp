#include "CameraManipulatorWidget.h"

namespace Demo
{
	CameraManipulatorWidget::CameraManipulatorWidget(float& camSpeed)
		:
		m_camSpeed(camSpeed)
	{
		m_title = "Camera";
	}

	void CameraManipulatorWidget::render()
	{
		ImGui::Begin(m_title.c_str());
		ImGui::SliderFloat("speed", &m_camSpeed, DEMOAPP_CAM_MINSPEED, DEMOAPP_CAM_MAXSPEED);
		ImGui::End();
	}

	void CameraManipulatorWidget::update(unsigned int dtime)
	{
	}
}