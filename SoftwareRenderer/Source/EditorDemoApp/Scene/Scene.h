
#pragma once
#include <unordered_map>
#include "../CoreAliases.h"
#include "../../Core/World/Entity.h"
#include "../../Core/World/Camera.h"
#include "../Shaders/PointLightShaderBase.h"
#include "PointLightSource.h"
#include "../../Core/World/CameraLookAt.h"

namespace Demo
{
	class Scene
	{
	public:
		class AlreadyInSceneException;
		class NotInSceneException;

		Scene() { }

		void add(const std::string& name, std::shared_ptr<Core::Entity> object);
		void remove(const std::string& name);
		void setCamera(std::shared_ptr<Core::CameraLookAt> camera);
		void setLightSource(std::shared_ptr<PointLightSource> lsrc);

		Core::Entity& getObject(const std::string& name);
		Core::CameraLookAt& getCamera() { return *m_camera; }
		PointLightSource& getLightSource() { return *m_lightSource; }

		const Core::Entity& getObject(const std::string& name) const;
		const Core::CameraLookAt& getCamera() const { return *m_camera; }
		const PointLightSource& getLightSource() const { return *m_lightSource; }

		void buildObjectNamesList(std::vector<std::string>& outList, bool includeLightSource = false);
		void buildObjectTransormsList(std::vector< std::tuple<vec3,vec3,float> >& outList, bool includeLightSource = false);

		void render(Core::RenderPipeline& renderer);
		void update(unsigned int dtime);

	private:
		std::unordered_map<std::string, std::shared_ptr<Core::Entity>> m_container;
		std::shared_ptr<PointLightSource> m_lightSource;
		std::shared_ptr<Core::CameraLookAt> m_camera;
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