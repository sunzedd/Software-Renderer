#pragma once
#include "../CoreAliases.h"
#include "../../Core/World/Entity.h"
#include "SceneObject.h"

namespace Demo
{
	class Scene
	{
	public:
		class AlreadyInSceneException;
		class NotInSceneException;

		Scene() { }

		void add(const std::string& name, std::shared_ptr<SceneObject> object);
		void remove(const std::string& name);
		void setActivity(const std::string& name, bool activated);

		void render(Core::RenderPipeline& renderer);
		void update(unsigned int dtime);

	private:
		std::unordered_map<std::string, std::shared_ptr<SceneObject>> m_container;
		std::shared_ptr<SceneObject> m_lightSource;
	};

	// Exceptions
	class Scene::AlreadyInSceneException : public std::exception
	{
	public:
		AlreadyInSceneException(const std::string& msg)
			:
			exception(("Object with this name already in scene: " + msg).c_str())
		{ }
	};

	class Scene::NotInSceneException : public std::exception
	{
	public:
		NotInSceneException(const std::string& msg)
			:
			exception(("Object with this name is not exists: " + msg).c_str())
		{ }
	};
}