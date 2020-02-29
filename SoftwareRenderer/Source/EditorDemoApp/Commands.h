#pragma once
#include "Scene/Scene.h"
#include "CoreAliases.h"

namespace Demo
{
	class ICommand
	{
	public:
		virtual void exec() = 0;
	};

	class ObjectCommand : public ICommand
	{
	public:
		ObjectCommand(Core::Entity& obj) : m_object(obj) { }
		virtual void exec() = 0;
	protected:
		Core::Entity& m_object;
	};

	class SceneCommand : public ICommand
	{
	public:
		SceneCommand(Scene& scene) : m_scene(scene) { }
		virtual void exec() = 0;
	protected:
		Scene& m_scene;
	};



	// -----------------------------------------------------------------------------
	class TransformObjectCommand final : public ObjectCommand
	{
	public:
		TransformObjectCommand(Core::Entity& obj) : ObjectCommand(obj) 
		{
			m_position = m_object.getPosition();
			m_rotation = m_object.getRotation();
			m_scale = m_object.getScale().x;
		}

		void setTransform(const vec3& pos, const vec3& rot, float scale)
		{
			m_position = pos;
			m_rotation = rot;
			m_scale = scale;
		}

		void setPosition(const vec3& pos) { m_position = pos; }
		void setRotation(const vec3& rot) { m_rotation = rot; }
		void setScale(float scale) { m_scale = scale; }

		void exec() override
		{
			m_object.setPosition(m_position);
			m_object.setRotation(m_rotation);
			m_object.setScale(vec3(1,1,1) * m_scale);
		}

	private:
		vec3 m_position;
		vec3 m_rotation;
		float m_scale;
	};
}
