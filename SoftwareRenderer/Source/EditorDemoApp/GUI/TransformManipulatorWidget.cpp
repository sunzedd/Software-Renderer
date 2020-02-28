#include "TransformManipulatorWidget.h"

namespace Demo
{
	TransformManipulatorWidget::TransformManipulatorWidget(Core::World& world)
		:
		m_world(world)
	{
		m_title = "Transform";

		// Build list of entity labels and transform structures.
		for (int i = 0; i < m_world.getScene().size(); i++)
		{
			const auto& entity = world.getScene()[i];
			
			Transform t;
			t.position = entity->getPosition();
			t.rotation = entity->getRotation();
			t.scale = entity->getScale().x;

			m_entityLabels.push_back(entity->getId().first.c_str());
			m_entityTransforms.push_back(t);
		}
	}

	void TransformManipulatorWidget::render()
	{
		ImGui::Begin(m_title.c_str());
		ImGui::ListBox("Object", &m_selectedEntityIndex, &m_entityLabels[0], m_entityLabels.size(), m_entityLabels.size());

		if (m_selectedEntityIndex > -1)
		{
			Transform& selectedEntityTransform = m_entityTransforms[m_selectedEntityIndex];

			ImGui::Begin("Transform");
			ImGui::Text("\t\tRotation:");
			ImGui::SliderAngle("Rx: ", &selectedEntityTransform.rotation.x, 0, 360);
			ImGui::SliderAngle("Ry: ", &selectedEntityTransform.rotation.y, 0, 360);
			ImGui::SliderAngle("Rz: ", &selectedEntityTransform.rotation.z, 0, 360);
			ImGui::NewLine();
			ImGui::DrawLine({ 0, 0 }, { 190, 0 }, { 255, 0, 0, 255 }, 2.0f);
			ImGui::NewLine();
			ImGui::Text("\t\tPosition:");
			ImGui::SliderFloat("Tx: ", &selectedEntityTransform.position.x, DEMOAPP_WORLD_MIN_X, DEMOAPP_WORLD_MAX_X);
			ImGui::SliderFloat("Ty: ", &selectedEntityTransform.position.y, DEMOAPP_WORLD_MIN_Y, DEMOAPP_WORLD_MAX_Y);
			ImGui::SliderFloat("Tz: ", &selectedEntityTransform.position.z, DEMOAPP_WORLD_MIN_Z, DEMOAPP_WORLD_MAX_Z);
			ImGui::NewLine();
			ImGui::DrawLine({ 0, 0 }, { 190, 0 }, { 255, 0, 0, 255 }, 2.0f);
			ImGui::NewLine();
			ImGui::SliderFloat("Scale: ", &selectedEntityTransform.scale, 0.1f, 3.0f);
			ImGui::End();

			Core::Vec3 rotDegrees = {
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.x),
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.y),
				Core::MathFunc::toDegrees(selectedEntityTransform.rotation.z)
			};

			auto& entity = m_world.getScene()[m_selectedEntityIndex];
			entity->setPosition(selectedEntityTransform.position);
			entity->setRotation(rotDegrees);
			entity->setScale(Core::Vec3(1, 1, 1) * selectedEntityTransform.scale);
		}
		ImGui::End();
	}

	void TransformManipulatorWidget::update(unsigned int dtime)
	{
	}

	void TransformManipulatorWidget::addTransform()
	{
		m_entityTransforms.push_back(Transform());
	}
}