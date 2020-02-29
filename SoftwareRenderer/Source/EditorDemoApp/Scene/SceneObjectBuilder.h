#pragma once
#include "../CoreAliases.h"
#include "../../Core/World/Entity.h"
#include "../../Core/AssetLoader.h"

namespace Demo
{
	extern std::shared_ptr<Core::IShaderProgram> g_defaultShader;
}

namespace Demo
{
	class SceneObjectBuilder
	{
	public:
		SceneObjectBuilder() { }

		void createObject();
		std::shared_ptr<Core::Entity> getBuildedObject();

		void setPosition(const vec3& pos);
		void setScale(const vec3& scale);
		void setRotation(const vec3& rot);
		void setMesh(std::shared_ptr<Core::Mesh> mesh);
		void setShader(std::shared_ptr<Core::IShaderProgram> shader);

	private:
		std::shared_ptr<Core::Entity> m_buildedObject;
	};
}