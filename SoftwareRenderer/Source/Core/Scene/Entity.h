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

		void setActivity(bool enabled);

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