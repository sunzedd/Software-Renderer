#pragma once
#include <vector>
#include "Entity.h"

namespace Core
{
	class World
	{
	public:
		World();

		std::vector<std::shared_ptr<Entity>>& getScene() { return m_scene; }

		virtual void update(unsigned int dtime);

	protected:
		std::vector<std::shared_ptr<Entity>> m_scene;
	};
}