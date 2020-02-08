#include "World.h"

namespace Core
{
	World::World()
	{

	}

	void World::update(unsigned int dtime)
	{
		for (auto& e : m_scene)
			e->update(dtime);
	}
}