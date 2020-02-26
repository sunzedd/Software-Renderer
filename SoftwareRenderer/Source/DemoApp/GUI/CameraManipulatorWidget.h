#pragma once
#include "Widget.h"
#include "../../Core/World/Camera.h"

#define DEMOAPP_CAM_MINSPEED 0.001
#define DEMOAPP_CAM_MAXSPEED 0.01

namespace Demo
{
	class CameraManipulatorWidget : public Widget
	{
	public:
		CameraManipulatorWidget(float& camSpeed);

		void render() override;
		void update(unsigned int dtime) override;

	private:
		float& m_camSpeed;
	};
}