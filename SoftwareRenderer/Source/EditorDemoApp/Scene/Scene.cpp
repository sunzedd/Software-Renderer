#include "Scene.h"

namespace Demo
{
	void Scene::add(const std::string& name, std::shared_ptr<SceneObject> object)
	{
		const auto found = m_container.find(name);
		if (found == m_container.cend())
		{
			m_container.insert(std::make_pair(name, object));
		}
		else
		{
			throw AlreadyInSceneException(name);
		}
	}

	void Scene::remove(const std::string& name)
	{
		m_container.erase(name);
	}

	void Scene::setActivity(const std::string& name, bool activated)
	{
		const auto found = m_container.find(name);
		if (found == m_container.end())
		{
			throw NotInSceneException(name);
		}
		else
		{
			found->second->setActivity(activated);
		}
	}

	void Scene::setCamera(std::shared_ptr<Core::Camera> camera)
	{
		m_camera = camera;
	}

	void Scene::setLightSource(const std::string& name, std::shared_ptr<SceneObject> lsrc)
	{
		const auto found = m_container.find(name);
		if (found == m_container.cend())
		{
			m_container.insert(std::make_pair(name, lsrc));
			m_lightSource = lsrc;
		}
		else
		{
			throw AlreadyInSceneException(name);
		}
	}

	void Scene::render(Core::RenderPipeline& renderer)
	{
		for (auto& object : m_container)
		{
			object.second->getShader().bindProjectionMatrix(m_camera->getProjMatrix());
			object.second->getShader().bindViewMatrix(m_camera->getViewMatrix());
			object.second->render(renderer);
		}
	}

	void Scene::update(unsigned int dtime)
	{
		for (auto& object : m_container)
			object.second->update(dtime);

		//m_lightSource->update(dtime);
		m_camera->update(dtime);
	}
}