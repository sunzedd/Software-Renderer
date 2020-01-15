#pragma once
#include <map>
#include "Entity.h"

namespace Core
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void add(const std::string& name, std::shared_ptr<Entity> entity);
		void remove(const std::string& name);

		void setActivity(const std::string& name, bool activated);

		virtual void render(RenderPipeline& renderer);
		virtual void update(unsigned int dtime);

	protected:
		std::map<std::string, std::shared_ptr<Entity>> m_container;
	};
}