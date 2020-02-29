#pragma once
#include "../CoreAliases.h"
#include "../../Core/World/Entity.h"
#include "../../Core/World/Camera.h"
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
		void setCamera(std::shared_ptr<Core::Camera> camera);
		void setLightSource(const std::string& name,std::shared_ptr<SceneObject> lsrc);

		Core::Camera& getCamera() { return *m_camera; }
		const Core::Camera& getCamera() const { return *m_camera; }
		SceneObject& getLightSource() { return *m_lightSource; }
		const SceneObject& getLightSource() const { return *m_lightSource; }

		void render(Core::RenderPipeline& renderer);
		void update(unsigned int dtime);

	private:
		std::unordered_map<std::string, std::shared_ptr<SceneObject>> m_container;
		std::shared_ptr<SceneObject> m_lightSource;
		std::shared_ptr<Core::Camera> m_camera;
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