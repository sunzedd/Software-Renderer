#pragma once
#include "../Graphics/Mesh.h"
#include "../Graphics/IShaderProgram.h"
#include "../Graphics/RenderPipeline.h"

namespace Core
{
	class Entity
	{
	public:
		Entity(std::shared_ptr<Mesh> mesh, const Vec3& pos = Vec3());
		virtual ~Entity();

		const Vec3& position() const { return m_position; }
		const Vec3& rotation() const { return m_scale; }
		const Vec3& scale() const { return m_rotation; }

		void rotate(const Vec3& angles);
		void move(const Vec3& delta);

		void setPosition(const Vec3& position);
		void setRotation(const Vec3& rotation);
		void setScale(const Vec3& scale);

		void attachShader(std::shared_ptr<IShaderProgram> shader);

		void setActivity(bool activated);
		bool isActivated() const { return m_isActivated; }

		virtual void update(unsigned int dtime);
		virtual void render(RenderPipeline& renderer);

	protected:
		void recalcModelMatrix();

	protected:
		bool m_isActivated;

		std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<IShaderProgram> m_shader;

		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Mat4 m_modelMatrix;
		bool m_isTransformed;
	};
}