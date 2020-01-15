#include "Entity.h"

namespace Core
{
	Entity::Entity(std::shared_ptr<Mesh> mesh, const Vec3& pos /* = Vec3() */)
		:
		m_mesh(mesh),
		m_position(pos),
		m_isActivated(true),
		m_isTransformed(true)
	{ }

	Entity::~Entity()
	{ }

	void Entity::rotate(const Vec3& angles)
	{
		m_rotation += angles;
		m_isTransformed = true;
	}

	void Entity::move(const Vec3& delta)
	{
		m_position += delta;
		m_isTransformed = true;
	}

	void Entity::setPosition(const Vec3& position)
	{
		m_position = position;
		m_isTransformed = true;
	}

	void Entity::setRotation(const Vec3& rotation)
	{
		m_rotation = rotation;
		m_isTransformed = true;
	}

	void Entity::setScale(const Vec3& scale)
	{
		m_scale = scale;
		m_isTransformed = true;
	}

	void Entity::attachShader(std::shared_ptr<IShaderProgram> shader)
	{
		m_shader = shader;
	}

	void Entity::setActivity(bool activated)
	{
		m_isActivated = activated;
	}

	void Entity::update(unsigned int dtime)
	{
	}

	void Entity::render(RenderPipeline& renderer)
	{
		if (m_isTransformed) 
			recalcModelMatrix();

		m_shader->bindModelMatrix(m_modelMatrix);
		renderer.bindShaderProgram(m_shader);
		m_mesh->render(renderer);
	}

	void Entity::recalcModelMatrix()
	{
		Mat4 s = Mat4::scale(m_scale);

		Mat4 rX = Mat4::rotationX(m_rotation.x);
		Mat4 rY = Mat4::rotationY(m_rotation.y);
		Mat4 rZ = Mat4::rotationZ(m_rotation.z);
		Mat4 r = rX * rY * rZ;

		Mat4 t = Mat4::translation(m_position);

		m_modelMatrix = s * r * t;

		m_isTransformed = false;
	}
}