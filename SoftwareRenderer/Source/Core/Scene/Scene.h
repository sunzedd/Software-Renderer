#pragma once
#include <unordered_map>
#include <memory>

#include "GameObject.h"
#include "Camera.h"

namespace core
{

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void update(unsigned int deltaTime);
	virtual void render();

protected:
	std::unordered_map<const std::string, std::shared_ptr<GameObject>> m_objects;
	Camera m_camera;
	// lights...
};

}