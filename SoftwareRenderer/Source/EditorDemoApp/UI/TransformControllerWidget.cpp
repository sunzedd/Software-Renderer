#include "TransformControllerWidget.h"

namespace Demo
{
	TransformControllerWidget::TransformControllerWidget(Scene& scene)
		:
		ObjectPickerWidgetBase(scene, "Transformations")
	{
		fillObjectTransforms();
		m_lightSourcePosition = scene.getLightSource().getPosition();
	}

	void TransformControllerWidget::render()
	{
		ImGui::Begin(m_title);
		ImGui::Combo("Object", &m_selectedItemIndex, &m_itemLabels[0], m_itemLabels.size(), m_itemLabels.size());

		// Objects transforms
		if (m_selectedItemIndex > -1)
		{
			Transform& selectedEntityTransform = getSelectedObjectTransform();

			ImGui::Text("\t\tRotation:");
			ImGui::SliderAngle("Rx", &selectedEntityTransform.rotation.x, 0, 360);
			ImGui::SliderAngle("Ry", &selectedEntityTransform.rotation.y, 0, 360);
			ImGui::SliderAngle("Rz", &selectedEntityTransform.rotation.z, 0, 360);
			ImGui::NewLine();
			ImGui::DrawLine({ 0, 0 }, { 190, 0 }, { 255, 0, 0, 255 }, 2.0f);
			ImGui::NewLine();
			ImGui::Text("\t\tPosition:");
			ImGui::SliderFloat("Px", &selectedEntityTransform.position.x, m_sceneSizeX.x, m_sceneSizeX.y);
			ImGui::SliderFloat("Py", &selectedEntityTransform.position.y, m_sceneSizeY.x, m_sceneSizeY.y);
			ImGui::SliderFloat("Pz", &selectedEntityTransform.position.z, m_sceneSizeZ.x, m_sceneSizeZ.y);
			ImGui::NewLine();
			ImGui::DrawLine({ 0, 0 }, { 190, 0 }, { 255, 0, 0, 255 }, 2.0f);
			ImGui::NewLine();
			ImGui::SliderFloat("Scale", &selectedEntityTransform.scale, 0.1f, 3.0f);

			Core::Vec3 rotDegrees = {
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.x),
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.y),
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.z)
			};

			const char* selectedEntityName = getSelectedItemName();
			auto& entity = m_scene.getObject(selectedEntityName);
		
			entity.setPosition(selectedEntityTransform.position);
			entity.setRotation(rotDegrees);
			entity.setScale(vec3(1,1,1) * selectedEntityTransform.scale);
		}

		// Light source translation
		ImGui::NewLine();
		ImGui::DrawLine({ 0, 0 }, { 190, 0 }, { 255, 0, 0, 255 }, 2.0f);
		ImGui::NewLine();
		ImGui::Text("Light source position");
		ImGui::SliderFloat("x", &m_lightSourcePosition.x, m_sceneSizeX.x, m_sceneSizeX.y);
		ImGui::SliderFloat("y", &m_lightSourcePosition.y, m_sceneSizeY.x, m_sceneSizeY.y);
		ImGui::SliderFloat("z", &m_lightSourcePosition.z, m_sceneSizeZ.x, m_sceneSizeZ.y);

		m_scene.getLightSource().setPosition(m_lightSourcePosition);

		ImGui::End();
	}

	void TransformControllerWidget::update(unsigned int dtime)
	{ }

	void TransformControllerWidget::fillObjectTransforms()
	{
		for (const auto& objectName : m_itemLabels)
		{
			const auto& object = m_scene.getObject(objectName);

			Transform t =
			{
				object.getPosition(),
				object.getRotation(),
				object.getScale().x
			};

			m_objectTransforms.push_back(t);
		}
	}

	TransformControllerWidget::Transform& TransformControllerWidget::getSelectedObjectTransform()
	{
		return m_objectTransforms[m_selectedItemIndex];
	}
}