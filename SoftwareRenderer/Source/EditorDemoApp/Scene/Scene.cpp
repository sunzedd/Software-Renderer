#include "Scene.h"

namespace Demo
{
	void Scene::add(const std::string& name, std::shared_ptr<Core::Entity> object)
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

	void Scene::setCamera(std::shared_ptr<Core::Camera> camera)
	{
		m_camera = camera;
	}

	void Scene::setLightSource(std::shared_ptr<PointLightSource> lsrc)
	{
		m_lightSource = lsrc;
	}

	void Scene::render(Core::RenderPipeline& renderer)
	{
		for (auto& object : m_container)
		{
			object.second->getShader().bindProjectionMatrix(m_camera->getProjMatrix());
			object.second->getShader().bindViewMatrix(m_camera->getViewMatrix());
			object.second->render(renderer);
		}

		m_lightSource->getShader().bindProjectionMatrix(m_camera->getProjMatrix());
		m_lightSource->getShader().bindViewMatrix(m_camera->getViewMatrix());
		m_lightSource->render(renderer);
	}

	void Scene::update(unsigned int dtime)
	{
		for (auto& object : m_container)
			object.second->update(dtime);

		m_lightSource->update(dtime);
		m_camera->update(dtime);
	}
}