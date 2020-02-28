#include "Entity.h"

namespace Core
{
	Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<IShaderProgram> shader)
		:
		WorldObject(),
		m_pMesh(mesh),
		m_pShader(shader),
		m_scale(Vec3(1, 1, 1)),
		m_isActive(true)
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


	void Entity::setRotation(const Vec3& rot)
	{
		m_rot = rot;
		m_isTransformed = true;
	}

	void Entity::setScale(const Vec3& scale)
	{
		m_scale = scale;
		m_isTransformed = true;
	}

	void Entity::rotate(const Vec3& delta)
	{
		m_rot += delta;
		m_isTransformed = true;
	}

	void Entity::scale(const Vec3& scaleFactor)
	{
		m_scale.x *= scaleFactor.x;
		m_scale.y *= scaleFactor.y;
		m_scale.z *= scaleFactor.z;
		m_isTransformed = true;
	}

	void Entity::update(unsigned int dtime)
	{
	}

	void Entity::recalcModelMatrix()
	{
		m_modelMatrix = Mat4::scale(m_scale) * Mat4::rotationXYZ(m_rot) * Mat4::translation(m_pos);
		m_isTransformed = false;
	}
}