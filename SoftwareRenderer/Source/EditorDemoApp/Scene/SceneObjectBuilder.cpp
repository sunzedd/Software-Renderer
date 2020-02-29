#include "SceneObjectBuilder.h"

namespace Demo
{
	void SceneObjectBuilder::createObject()
	{
		auto defaultObjectMesh = Core::AssetLoader::loadMesh("Assets\\Meshes\\cube.obj");
		auto defaultObjectShader = g_defaultShader;

		m_buildedObject = std::make_shared<Core::Entity>(std::move(defaultObjectMesh), std::move(defaultObjectShader));
	}

	std::shared_ptr<Core::Entity> SceneObjectBuilder::getBuildedObject()
	{
		return std::move(m_buildedObject);
	}

	void SceneObjectBuilder::setPosition(const vec3& pos)
	{
		m_buildedObject->setPosition(pos);
	}

	void SceneObjectBuilder::setScale(const vec3& scale)
	{
		m_buildedObject->setScale(scale);
	}

	void SceneObjectBuilder::setRotation(const vec3& rot)
	{
		m_buildedObject->setRotation(rot);
	}

	void SceneObjectBuilder::setMesh(std::shared_ptr<Core::Mesh> mesh)
	{
		m_buildedObject->setMesh(mesh);
	}

	void SceneObjectBuilder::setShader(std::shared_ptr<Core::IShaderProgram> shader)
	{
		m_buildedObject->setShader(shader);
	}
}