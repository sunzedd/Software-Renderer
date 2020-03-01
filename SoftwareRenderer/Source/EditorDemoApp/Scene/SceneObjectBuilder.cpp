#include "SceneObjectBuilder.h"

namespace Demo
{
	void SceneObjectBuilder::createObject()
	{
		auto defaultObjectMesh = Core::AssetLoader::loadMesh("Assets\\Meshes\\cube.obj");
		auto defaultObjectShader = g_defaultShader;

		m_builtObject = std::make_shared<Core::Entity>(std::move(defaultObjectMesh), std::move(defaultObjectShader));
	}

	std::shared_ptr<Core::Entity> SceneObjectBuilder::getBuiltObject()
	{
		return std::move(m_builtObject);
	}

	void SceneObjectBuilder::setPosition(const vec3& pos)
	{
		m_builtObject->setPosition(pos);
	}

	void SceneObjectBuilder::setScale(const vec3& scale)
	{
		m_builtObject->setScale(scale);
	}

	void SceneObjectBuilder::setRotation(const vec3& rot)
	{
		m_builtObject->setRotation(rot);
	}

	void SceneObjectBuilder::setMesh(std::shared_ptr<Core::Mesh> mesh)
	{
		m_builtObject->setMesh(mesh);
	}

	void SceneObjectBuilder::setShader(std::shared_ptr<Core::IShaderProgram> shader)
	{
		m_builtObject->setShader(shader);
	}
}