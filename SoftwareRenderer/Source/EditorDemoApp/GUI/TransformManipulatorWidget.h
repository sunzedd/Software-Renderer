#pragma once
#include "Widget.h"

#define DEMOAPP_WORLD_MIN_X 0
#define DEMOAPP_WORLD_MAX_X 20
#define DEMOAPP_WORLD_MIN_Y 0
#define DEMOAPP_WORLD_MAX_Y 20
#define DEMOAPP_WORLD_MIN_Z 0
#define DEMOAPP_WORLD_MAX_Z 20

#if 0
namespace Demo
{
	struct Transform
	{
		Core::Vec3 position;
		Core::Vec3 rotation;
		float scale;
	};

	class TransformManipulatorWidget : public Widget
	{
	public:
		TransformManipulatorWidget(Core::World& world);

		void render() override;
		void update(unsigned int dtime) override;

		void addTransform();

	private:
		Core::World& m_world;
		std::vector<const char*> m_entityLabels;
		std::vector<Transform> m_entityTransforms;
		int m_selectedEntityIndex;
	};
}
#endif