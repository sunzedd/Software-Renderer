#pragma once
#include "ObjectPickerWidgetBase.h"
#include "../Scene/Scene.h"

namespace Demo
{
	class TransformControllerWidget : public ObjectPickerWidgetBase
	{
		struct Transform;

	public:
		TransformControllerWidget(Scene& scene);

		void render() override;
		void update(unsigned int dtime) override;

		void setSceneSizeX(const vec2& size) { m_sceneSizeX = size; }
		void setSceneSizeY(const vec2& size) { m_sceneSizeY = size; }
		void setSceneSizeZ(const vec2& size) { m_sceneSizeZ = size; }

	private:
		void fillObjectTransforms();
		Transform& getSelectedObjectTransform();

	private:
		std::vector<Transform> m_objectTransforms;
		vec3 m_lightSourcePosition;

		// Min,max values for object movement
		vec2 m_sceneSizeX = { -10.0f, 10.0f };
		vec2 m_sceneSizeY = { -10.0f, 10.0f };
		vec2 m_sceneSizeZ = { -10.0f, 10.0f };

		struct Transform
		{
			vec3 position;
			vec3 rotation;
			float scale;
		};
	};
}