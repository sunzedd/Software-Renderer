#pragma once
#include "Widget.h"
#include "../../Core/World/World.h"

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