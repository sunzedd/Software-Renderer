#include "Entity.h"

namespace Core
{
	Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<IShaderProgram> shader)
		:
		m_pMesh(mesh),
		m_pShader(shader),
		m_isActive (true),
		m_isTransformed (true)
	{ }

	Entity::~Entity()
	{ }

	void Entity::render(RenderPipeline& renderer)
	{
		if (m_isActive)
		{
			if (m_isTransformed)
			{
				recalcModelMatrix();
			}

			renderer.bindShaderProgram(m_pShader);
			m_pShader->bindModelMatrix(m_modelMatrix);

			m_pMesh->render(renderer);
		}
	}

	void Entity::setActivity(bool enabled)
	{
		m_isActive = enabled;
	}


	void Entity::recalcModelMatrix()
	{
		m_modelMatrix = Mat4::scale(m_scale) * Mat4::rotationXYZ(m_rot) * Mat4::translation(m_pos);
		m_isTransformed = false;
	}
}