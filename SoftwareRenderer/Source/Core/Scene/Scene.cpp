#include "Scene.h"

namespace Core
{
	Scene::Scene()
	{ }

	Scene::~Scene()
	{ }

	void Scene::add(const std::string& name, std::shared_ptr<Entity> entity) 
	{
		m_container.insert( std::pair<std::string,std::shared_ptr<Entity>>( name, entity ) );
	}
	void Scene::remove(const std::string& name)
	{
		m_container.erase(name);
	}

	void Scene::setActivity(const std::string& name, bool activated)
	{
		auto& entity = m_container.at(name);
		entity->setActivity(activated);
	}

	void Scene::render(RenderPipeline& renderer)
	{
		for (auto iter = m_container.begin(); iter != m_container.end(); ++iter)
		{
			if (iter->second->isActivated())
				iter->second->render(renderer);
		}
	}

	void Scene::update(unsigned int dtime)
	{
		for (auto& entity : m_container)
		{
			entity.second->update(dtime);
		}
	}
}