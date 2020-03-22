#include "Scene.h"

namespace core
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::update(unsigned int deltaTime)
{
	for (auto& object : m_objects)
		object.second->update(deltaTime);
}

void Scene::render()
{
	for (auto& object : m_objects)
		object.second->render();
}

}