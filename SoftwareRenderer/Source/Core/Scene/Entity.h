#pragma once
#include "../Graphics/Mesh.h"

namespace Core
{
	class Entity
	{
	public:
		Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<IShaderProgram> shader);
		virtual ~Entity();

		virtual void render(RenderPipeline& renderer);

		const Vec3& getPosition() const { return m_pos; }
		const Vec3& getRotation() const { return m_rot; }
		const Vec3& getScale() const { return m_scale; }

		void setActivity(bool enabled);
		void setPosition(const Vec3& pos);
		void setRotation(const Vec3& rot);
		void setScale(const Vec3& scale);

		void move(const Vec3& delta);
		void rotate(const Vec3& delta);
		void scale(const Vec3& scaleFactor);

	protected:
		void recalcModelMatrix();

	protected:
		std::shared_ptr<Mesh> m_pMesh;
		std::shared_ptr<IShaderProgram> m_pShader;

		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		Mat4 m_modelMatrix;

		bool m_isTransformed;
		bool m_isActive;
	};
}